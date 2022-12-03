#include "MainController.h"
#include "hwconfig.h"
#include "Hardware.h"

#include <Arduino.h>
#include <math.h>


#define TRANSMIT_TIME 10000

MainController* MainController::mainController = nullptr;

MainController::MainController(float sampleRate) : AbstractMainController(Hardware::hw.encoder) {
    MainController::mainController = this;
    this->sampleRate = sampleRate;
}

void MainController::init() {
    Hardware::hw.init();
    AbstractMainController::init();

    this->shortPress = &MainController::incrementMode;
    this->clockWise = &MainController::incrementValue;
    this->antiClockWise = &MainController::decrementValue;
    this->initOnModeSelect = false;
}

void MainController::controllerInit() {
    interruptTimer.end();
    saveMode();

    Hardware::hw.clearOutputLeds();
    // Hardware::hw.display.clear();

    if(controllers.getSelected()->getSampleRate() > 0) {
        controllers.getSelected()->init();
    } else {
        controllers.getSelected()->init(sampleRate);
    }

    int intervalMicros = 1000000/sampleRate;
    interruptTimer.begin(MainController::interruptHandler, intervalMicros);
}

void MainController::interruptHandler() {
    mainController->process();
}

void MainController::update() {
    RotaryEncoderButton::EncoderEvent event = encoder.getEncoderEvent();
    doEncoderEvent(event);
    controllers.getSelected()->update();

    //Hardware::hw.display.update();

    PROFILE_PRINT
}

void MainController::process() {
    PROFILE_START
    controllers.getSelected()->process();
    // TODO update pot values
    PROFILE_END
}
