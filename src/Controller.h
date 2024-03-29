#ifndef Controller_h
#define Controller_h

#include <eurorack.h>
#include "Hardware.h"

class Controller : public AbstractController {
    public:
        Controller() : AbstractController() {}
        virtual void init(float sampleRate) { this->sampleRate = sampleRate; }
        virtual void init() {};
        virtual void update() = 0;
        virtual void process() = 0;
        float getSampleRate() { return sampleRate; }
    
    protected: 
        float sampleRate = 0;
};


template<int N>
class ParameterizedController : public virtual Controller, public AbstractParameterizedController<N> {
    public:
        void load() { AbstractParameterizedController<N>::load(); }
        void save() { AbstractParameterizedController<N>::save(); }
};

#endif
