#include "MatrixController.h"

void MatrixController::init(float sampleRate) {
    Controller::init(sampleRate);
    configParam(Parameter::BANK_SELECT, 0, 15);
    configParam(Parameter::MATRIX_MODE, 0, 1);
    init();
}

void MatrixController::init() {
    Serial.println("Matrix");
    Hardware::hw.display.textLine("MATRIX");
}

int MatrixController::cycleParameter(int amount) {
    parameters.cycle(amount);
    Serial.print("Cycle parameter ");
    Serial.println(parameters.getSelectedIndex());
    return parameters.getSelectedIndex(); 
}

void MatrixController::cycleValue(int amount) {
    uint8_t value = parameters.getSelected().cycle(amount);
    Serial.print("Cycle value ");
    Serial.println(value);
    switch(parameters.getSelectedIndex()) {
        case Parameter::BANK_SELECT:
            mixMatrix.setMatrixValues(&matrixValues[value]);
            break;
        case Parameter::MATRIX_MODE:
            mixMatrix.setMode(static_cast<MixMatrix::Mode>(value));
            break;
    }

    AbstractParameterizedController::save();
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
    bool state = mixMatrix.getMatrixState(x, y);
    mixMatrix.setMatrixState(x, y, !state);
}

void MatrixController::process() {
    
}
