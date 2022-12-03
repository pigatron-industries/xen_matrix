#ifndef FrequencyController_h
#define FrequencyController_h

#include "Controller.h"
#include <eurorack_dsp.h>

using namespace eurorack;

#define SAMPLERATE_DIVIDER 8

class MatrixController : public Controller {
    public:
        enum Mode {
            MATRIX
        };

        MatrixController() : Controller(Mode::MATRIX) {}
        virtual void init(float sampleRate);
        virtual void init();
        virtual void update();
        virtual void process();

    protected:

        LinearInput<AnalogInputPinT> ampCvInput = LinearInput<AnalogInputPinT>(Hardware::hw.cv1Input, -5, 5, 0, 5);
        LinearInput<AnalogInputPinT> waveCvInput = LinearInput<AnalogInputPinT>(Hardware::hw.cv2Input, -5, 5, 0, 5);
};

#endif
