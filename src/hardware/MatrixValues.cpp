#include "MatrixValues.h"

MatrixValues::MatrixValues() {
    for(int x = 0; x < MATRIX_COLS; x++) {
        for(int y = 0; y < MATRIX_ROWS; y++) {
            state[x][y] = false;
            value[x][y] = 1.0;
        }
    }
}

void MatrixValues::setMatrixValue(uint8_t x, uint8_t y, float value) {
    this->value[x][y] = value;
}

void MatrixValues::setMatrixState(uint8_t x, uint8_t y, bool state) {
    this->state[x][y] = state;
}

float MatrixValues::getMatrixValue(uint8_t x, uint8_t y) {
    return this->value[x][y];
}

bool MatrixValues::getMatrixState(uint8_t x, uint8_t y) {
    return this->state[x][y];
}
