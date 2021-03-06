#include "Arduino.h"
#include "composition.h"
#include "handlers/defaultHandler.h"
#include "handlers/scoreHandler.h"
#include "modules/debugger.h"
#include "modules/display.h"
#include "modules/joystick.h"
#include "modules/motor.h"
#include "modules/ballsensor.h"
#include "modules/digits.h"
#include "modules/range.h"

void Composition::Compose()
{
    // Create modules
    this->_debugger = new Debugger();
    this->_motor = new Motor();
    this->_ballSensor = new BallSensor();
    this->_display = new Display();
    this->_digits = new Digits();
    this->_range = new Range();
    this->_joystick = new Joystick();

    // Create handlers
    this->_defaultHandler = new DefaultHandler();
    this->_scoreHandler = new ScoreHandler();

    // Associate handlers with states
    this->handlers[idle] = _defaultHandler;
    this->handlers[moveUp] = _defaultHandler;
    this->handlers[moveDown] = _defaultHandler;
    this->handlers[scored] = _scoreHandler;
    this->handlers[lost] = _scoreHandler;
    this->handlers[errorInvalidInput] = _defaultHandler;
}

void Composition::Setup()
{
    // Setup modules
    this->_debugger->Setup();
    this->_display->Setup();
    this->_motor->Setup();
    this->_ballSensor->Setup();
    this->_digits->Setup();
    this->_range->Setup();
    this->_joystick->Setup();

    // Setup handlers
    this->_defaultHandler->Setup(this);
    this->_scoreHandler->Setup(this);
}

void Composition::Input()
{
    this->_ballSensor->Input();
    this->_range->Input();
    this->_joystick->Input();
}

void Composition::Output(int tick)
{
    this->_debugger->Output(tick);
    this->_display->Output(tick);
    this->_motor->Output(tick);
    this->_digits->Output(tick);
}

Handler* Composition::GetHandler(State state)
{
    return this->handlers[state];
}

Debugger* Composition::GetDebugger()
{
    return this->_debugger;
}

Display* Composition::GetDisplay()
{
    return this->_display;
}

Motor* Composition::GetMotor()
{
    return this->_motor;
}

BallSensor* Composition::GetBallSensor()
{
    return this->_ballSensor;
}

Digits* Composition::GetDigits()
{
    return this->_digits;
}

Range* Composition::GetRange()
{
    return this->_range;
}

Joystick* Composition::GetJoystick()
{
    return this->_joystick;
}
