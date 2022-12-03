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

        AnalogInput(cv1Pin, CV1_PIN)
        AnalogInput(cv2Pin, CV2_PIN)
        AnalogInputPin<> cv1Input = AnalogInputPin<>(cv1Pin);
        AnalogInputPin<> cv2Input = AnalogInputPin<>(cv2Pin);

        // TODO Pot outputs

        IS32FL3738Device is32fl3738 = IS32FL3738Device(Wire, SDB_PIN);
        AnalogOutputPin<IS32FL3738Device>* matrixLeds[6][6] = {
            { &is32fl3738.pins[0], &is32fl3738.pins[1], &is32fl3738.pins[2], &is32fl3738.pins[3], &is32fl3738.pins[4], &is32fl3738.pins[5]},
            { &is32fl3738.pins[6], &is32fl3738.pins[7], &is32fl3738.pins[8], &is32fl3738.pins[9], &is32fl3738.pins[10], &is32fl3738.pins[11]},
            { &is32fl3738.pins[12], &is32fl3738.pins[13], &is32fl3738.pins[14], &is32fl3738.pins[15], &is32fl3738.pins[16], &is32fl3738.pins[17]},
            { &is32fl3738.pins[18], &is32fl3738.pins[19], &is32fl3738.pins[20], &is32fl3738.pins[21], &is32fl3738.pins[22], &is32fl3738.pins[23]},
            { &is32fl3738.pins[24], &is32fl3738.pins[25], &is32fl3738.pins[26], &is32fl3738.pins[27], &is32fl3738.pins[28], &is32fl3738.pins[29]},
            { &is32fl3738.pins[30], &is32fl3738.pins[31], &is32fl3738.pins[32], &is32fl3738.pins[33], &is32fl3738.pins[34], &is32fl3738.pins[35]}
        };

        // OLEDDisplay display;

};

#endif