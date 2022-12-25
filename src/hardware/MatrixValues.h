#ifndef MatrixValues_h
#define MatrixValues_h

#include <inttypes.h>
#include "../hwconfig.h"


class MatrixValues {
    public:
        MatrixValues();

        void setMatrixValue(uint8_t x, uint8_t y, float value);
        void setMatrixState(uint8_t x, uint8_t y, bool state);
        float getMatrixValue(uint8_t x, uint8_t y);
        bool getMatrixState(uint8_t x, uint8_t y);
        
    private:
        bool state[MATRIX_ROWS][MATRIX_COLS];
        float value[MATRIX_ROWS][MATRIX_COLS];
};

#endif
