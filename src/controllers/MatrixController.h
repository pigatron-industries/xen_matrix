#ifndef FrequencyController_h
#define FrequencyController_h

#include "Controller.h"
#include "../hardware/MixMatrix.h"
#include <eurorack_dsp.h>

using namespace eurorack;

#define SAMPLERATE_DIVIDER 8

class MatrixController : public ParameterizedController<2> {
    public:
        enum Parameter {
            BANK_SELECT = 0,
            MATRIX_MODE
        };

        MatrixController() : ParameterizedController() {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual int cycleParameter(int amount);
        virtual void cycleValue(int amount);

        virtual void update();
        virtual void process();

    protected:

        LinearInput<AnalogInputPinT> ampCvInput = LinearInput<AnalogInputPinT>(Hardware::hw.cv1Input, -5, 5, 0, 5);
        LinearInput<AnalogInputPinT> waveCvInput = LinearInput<AnalogInputPinT>(Hardware::hw.cv2Input, -5, 5, 0, 5);

        MatrixValues matrixValues;

        MixMatrix mixMatrix = MixMatrix(&matrixValues);

        void toggleMatrixValue(uint8_t x, uint8_t y);
};

#endif
