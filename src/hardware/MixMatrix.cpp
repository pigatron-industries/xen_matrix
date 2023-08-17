#include "MixMatrix.h"

#include "../Hardware.h"

#define MAX_BRIGHTNESS 0.25

uint8_t rowPins[MATRIX_ROWS] = KEY_ROW_PINS;
uint8_t colPins[MATRIX_COLS] = KEY_COL_PINS;
char keys[MATRIX_ROWS][MATRIX_COLS] = {
    {1,  2,  3,  4,  5,  6},
    {7,  8,  9,  10, 11, 12},
    {13, 14, 15, 16, 17, 18},
    {19, 20, 21, 22, 23, 24},
    {25, 26, 27, 28, 29, 30},
    {31, 32, 33, 34, 35, 36}
}; 

Keypad MixMatrix::keypad = Keypad(makeKeymap(keys), rowPins, colPins, MATRIX_ROWS, MATRIX_COLS);

MixMatrix::MixMatrix(MatrixValues* matrixValues) {
    this->matrixValues = matrixValues;
}

void MixMatrix::setMatrixValues(MatrixValues* matrixValues) {
    this->matrixValues = matrixValues;
    for(uint8_t x = 0; x < MATRIX_COLS; x++) {
        for(uint8_t y = 0; y < MATRIX_ROWS; y++) {
            updateOutput(x, y);
        }
    }
}

void MixMatrix::setMode(MixMatrix::Mode mode) { 
    this->mode = mode; 
}

bool MixMatrix::update() {
    bool updated = keypad.getKeys();
    if(updated) {
        for(int i = 0; i < LIST_MAX; i++) {
            Key key = keypad.key[i];
            if(key.stateChanged) {
                updateKeyState(key.kchar, key.kstate);
                return true;
            }
        }
    }
    return false;
}

void MixMatrix::updateKeyState(uint8_t keycode, KeyState keystate) {
    for (int i = 0; i < keyStates.size(); i++){
        if(keyStates[i].keycode == keycode) {
            keyStates.remove(i);
            break;
        }
    }

    if(keystate != IDLE) {
        keyStates.add(MatrixKeyState(keycode, keystate));
    }
}

void MixMatrix::setMatrixValue(uint8_t x, uint8_t y, float value) {
    matrixValues->setMatrixValue(x, y, value);
    updateOutput(x, y);
}

void MixMatrix::setMatrixState(uint8_t x, uint8_t y, bool state) {
    matrixValues->setMatrixState(x, y, state);
    updateOutput(x, y);

    if(state && mode == ROUTER) {
        // turn off all other matrix values in the same column
        for(uint8_t i=0; i<MATRIX_COLS; i++) {
            if(i != x) {
                matrixValues->setMatrixState(i, y, false);
                updateOutput(i, y);
            }
        }
    }
}

void MixMatrix::updateOutput(uint8_t x, uint8_t y) {
    bool state = matrixValues->getMatrixState(x, y);
    if(state) {
        float value = matrixValues->getMatrixValue(x, y);
        Hardware::hw.matrixLeds[x][y]->analogWrite(value*MAX_BRIGHTNESS);
        Hardware::hw.matrixPots[x][y]->analogWrite(value);
    } else {
        Hardware::hw.matrixLeds[x][y]->analogWrite(0);
        Hardware::hw.matrixPots[x][y]->analogWrite(0);
    }
}