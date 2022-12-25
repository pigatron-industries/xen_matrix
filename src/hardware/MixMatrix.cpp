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

bool MixMatrix::update() {
    bool updated = keypad.getKeys();
    if(updated) {
        Key key = keypad.key[0];
        if(key.stateChanged) {
            keyState = MatrixKeyState(key.kchar, key.kstate);
            return true;
        }
    }
    return false;
}

MatrixKeyState& MixMatrix::getKeyState() {
    return keyState;
}

void MixMatrix::setMatrixValue(uint8_t x, uint8_t y, float value) {
    matrixValues->setMatrixValue(x, y, value);
    if(matrixValues->getMatrixState(x, y)) {
        updateOutput(x, y, true, value);
    }
}

void MixMatrix::setMatrixState(uint8_t x, uint8_t y, bool state) {
    matrixValues->setMatrixState(x, y, state);
    float value = matrixValues->getMatrixValue(x, y);
    updateOutput(x, y, state, value);
}

void MixMatrix::updateOutput(uint8_t x, uint8_t y, bool state, float value) {
    if(state) {
        Hardware::hw.matrixLeds[x][y]->analogWrite(value*MAX_BRIGHTNESS);
        Hardware::hw.matrixPots[x][y]->analogWrite(value);
    } else {
        Hardware::hw.matrixLeds[x][y]->analogWrite(0);
        Hardware::hw.matrixPots[x][y]->analogWrite(0);
    }
}