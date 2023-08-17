#ifndef MixMatrix_h
#define MixMatrix_h

#include <Keypad.h>
#include <eurorack.h>
#include "../hwconfig.h"
#include "MatrixValues.h"


#define MAX_KEYS_PRESSED 2

class MatrixKeyState {
    public:
        MatrixKeyState() {}
        MatrixKeyState(uint8_t keycode, KeyState keystate) : 
            keycode(keycode), 
            keystate(keystate) {
                x = (keycode-1)/6;
                y = (keycode-1)%6;
        }
        uint8_t keycode;
        uint8_t x;
        uint8_t y;
        KeyState keystate;
};

class MixMatrix {
    public:
        enum Mode {
            ROUTER = 0,
            MIXER
        };

        MixMatrix(MatrixValues* matrixValues);
        
        MatrixValues* getMatrixValues() { return matrixValues; }
        bool getMatrixState(uint8_t x, uint8_t y) { return matrixValues->getMatrixState(x, y); }

        void setMatrixValues(MatrixValues* matrixValues);
        void setMode(MixMatrix::Mode mode);

        bool update();
        Array<MatrixKeyState, MAX_KEYS_PRESSED>& getKeyStates() { return keyStates; }
        void setMatrixValue(uint8_t x, uint8_t y, float value);
        void setMatrixState(uint8_t x, uint8_t y, bool state);
        
    private:
        MatrixValues* matrixValues;

        MixMatrix::Mode mode = MIXER;
        static Keypad keypad;

        Array<MatrixKeyState, MAX_KEYS_PRESSED> keyStates;

        void updateKeyState(uint8_t keycode, KeyState keystate);
        void updateOutput(uint8_t x, uint8_t y);
};

#endif
