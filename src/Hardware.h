#ifndef Hardware_h
#define Hardware_h

#include <Arduino.h>
#include <eurorack.h>
#include <eurorack_is32fl3738.h>
// #include "display/OLEDDisplay.h"
// #include "Colour.h"
#include "hwconfig.h"

#define MEMPOOL_SIZE 48*1024

class Hardware {
    public:
        static Hardware hw;
        void init();

        void clearOutputLeds();
        void updateOutputLeds();

        // Memory pool
        static float memPoolBuffer[MEMPOOL_SIZE];
        MemPool<float> memPool = MemPool<float>(Hardware::memPoolBuffer, MEMPOOL_SIZE);

        // Direct connections
        RotaryEncoderButton encoder = RotaryEncoderButton(ENCODER_PIN1, ENCODER_PIN2, ENCODER_BTN_PIN);

        #define AnalogInputPinT AnalogInputPin<NativeDevice>

        AnalogInput(cv1Pin, A10)
        AnalogInput(cv2Pin, A11)
        AnalogInputPin<> cv1Input = AnalogInputPin<>(cv1Pin);
        AnalogInputPin<> cv2Input = AnalogInputPin<>(cv2Pin);

        // TODO Pot outputs

        IS32FL3738Device is32fl3738 = IS32FL3738Device(Wire, SDB_PIN);
        AnalogOutputPin<IS32FL3738Device>* matrixLeds[6][6] = {
            { &is32fl3738.pins[0], &is32fl3738.pins[1], &is32fl3738.pins[2], &is32fl3738.pins[3], &is32fl3738.pins[4], &is32fl3738.pins[5]},
            { &is32fl3738.pins[0], &is32fl3738.pins[1], &is32fl3738.pins[2], &is32fl3738.pins[3], &is32fl3738.pins[4], &is32fl3738.pins[5]},
            { &is32fl3738.pins[0], &is32fl3738.pins[1], &is32fl3738.pins[2], &is32fl3738.pins[3], &is32fl3738.pins[4], &is32fl3738.pins[5]},
            { &is32fl3738.pins[0], &is32fl3738.pins[1], &is32fl3738.pins[2], &is32fl3738.pins[3], &is32fl3738.pins[4], &is32fl3738.pins[5]},
            { &is32fl3738.pins[0], &is32fl3738.pins[1], &is32fl3738.pins[2], &is32fl3738.pins[3], &is32fl3738.pins[4], &is32fl3738.pins[5]},
            { &is32fl3738.pins[0], &is32fl3738.pins[1], &is32fl3738.pins[2], &is32fl3738.pins[3], &is32fl3738.pins[4], &is32fl3738.pins[5]}
        };

        // OLEDDisplay display;

};

#endif