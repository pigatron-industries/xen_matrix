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

}

void MatrixController::process() {

}
