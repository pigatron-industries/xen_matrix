#include "MatrixController.h"

void MatrixController::init(float sampleRate) {
    Controller::init(sampleRate);
    init();
}

void MatrixController::init() {
    Serial.println("Matrix");
    Hardware::hw.display.textLine("MATRIX");
}

int MatrixController::cycleMode(int amount) { 
    mode.cycle(amount);

    switch(mode.value) {
        case Mode::MIXER:
            mixMatrix.setMode(MixMatrix::MIXER);
            break;
        case Mode::ROUTER:
            mixMatrix.setMode(MixMatrix::ROUTER);
            break;
    }

    Serial.println(mode.value);
    return mode.value; 
}

void MatrixController::update() {
    if(mixMatrix.update()) {
        MatrixKeyState& key = mixMatrix.getKeyState();
        if(key.keystate == PRESSED) {
            toggleMatrixValue(key.x, key.y);
        }
    }
}

void MatrixController::toggleMatrixValue(uint8_t  x, uint8_t y) {
    bool state = matrixValues.getMatrixState(x, y);
    mixMatrix.setMatrixState(x, y, !state);
}

void MatrixController::process() {
    
}
