#include "MatrixController.h"

void MatrixController::init(float sampleRate) {
    Controller::init(sampleRate);
    init();
}

void MatrixController::init() {
    Serial.println("Matrix");
    // Hardware::hw.display.textLine("MATRIX");
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
