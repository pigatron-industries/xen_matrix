#include "MatrixDisplay.h"

void MatrixDisplay::init() {
    page.addComponent(&title);
    page.addComponent(&bankField);
    page.addComponent(&matrixModeField);
    page.setContext(&Hardware::hw.display);
    page.layout();
}

void MatrixDisplay::render() {
    Hardware::hw.display.clear();
    page.render();
    Hardware::hw.display.update();
}

void MatrixDisplay::focusBank() {
    focusManager.setFocus(&bankField);
}

void MatrixDisplay::focusMatrixMode() {
    focusManager.setFocus(&matrixModeField);
}

void MatrixDisplay::setBank(uint8_t bank) {
    bankField.setValue(bank);
    Hardware::hw.display.update();
}

void MatrixDisplay::setMatrixMode(MixMatrix::Mode matrixMode) {
    matrixModeField.setValue(matrixMode == MixMatrix::Mode::ROUTER ? "ROUTER" : "MIXER");
    Hardware::hw.display.update();
}
