#include "MatrixController.h"

void MatrixController::init(float sampleRate) {
    Controller::init(sampleRate);
    configParam(Parameter::BANK_SELECT, 0, 15);
    configParam(Parameter::MATRIX_MODE, 0, 1);
    mixMatrix.setMatrixValues(&matrixValues[parameters[BANK_SELECT].value]);
    mixMatrix.setMode(static_cast<MixMatrix::Mode>(parameters[MATRIX_MODE].value));
    display.init();
    display.setBank(parameters[BANK_SELECT].value);
    display.setMatrixMode(static_cast<MixMatrix::Mode>(parameters[MATRIX_MODE].value));
    display.focusBank();
    init();
}

void MatrixController::init() {
    Serial.println("Matrix");
    display.render();
}

int MatrixController::cycleParameter(int amount) {
    parameters.cycle(amount);
    Serial.print("Cycle parameter ");
    Serial.println(parameters.getSelectedIndex());
    switch(parameters.getSelectedIndex()) {
        case Parameter::BANK_SELECT:
            display.focusBank();
            break;
        case Parameter::MATRIX_MODE:
            display.focusMatrixMode();
            break;
    }
    return parameters.getSelectedIndex(); 
}

void MatrixController::cycleValue(int amount) {
    uint8_t value = parameters.getSelected().cycle(amount);
    Serial.print("Cycle value ");
    Serial.println(value);
    switch(parameters.getSelectedIndex()) {
        case Parameter::BANK_SELECT:
            mixMatrix.setMatrixValues(&matrixValues[value]);
            display.setBank(value);
            break;
        case Parameter::MATRIX_MODE:
            mixMatrix.setMode(static_cast<MixMatrix::Mode>(value));
            display.setMatrixMode(static_cast<MixMatrix::Mode>(value));
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
