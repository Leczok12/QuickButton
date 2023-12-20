#include "QuickButton.h"

QuickButton::QuickButton(int pin, bool callbacks_auto_reset)
    : _pin(pin),
      _callbacksAutoReset(callbacks_auto_reset),
      _durationClickCallback(nullptr),
      _multipleClickCallback(nullptr),
      _mixedClickCallback(nullptr),
      _event(EVENT::NONE),
      _duration(0),
      _deltaTime(0),
      _pressEndTime(0),
      _pressed(false),
      _count(0)
{
    pinMode(_pin, INPUT_PULLUP);
};

QuickButton::~QuickButton(){};

void QuickButton::loop()
{
    if (_event != EVENT::NONE && (_durationClickCallback != nullptr || _multipleClickCallback != nullptr || _mixedClickCallback != nullptr))
    {
        if (_durationClickCallback != nullptr)
            _durationClickCallback(_duration);
        else if (_multipleClickCallback != nullptr)
            _multipleClickCallback(_count);
        else if (_mixedClickCallback != nullptr)
            _mixedClickCallback(_duration, _count);

        if (_callbacksAutoReset)
            reset();
        return;
    }

    if (digitalRead(_pin) == LOW && !_pressed)
    {
        _deltaTime = millis();
        _pressed = true;
    }
    else if (digitalRead(_pin) == HIGH && _pressed)
    {
        _deltaTime = millis() - _deltaTime;
        _pressEndTime = millis();
        _pressed = false;

        if (_deltaTime > 50)
        {
            _duration = _deltaTime;
            _count++;
        }
    }

    if (_pressed)
        return;

    if (_count == 1 && _pressEndTime + 200 < millis())
    {
        _event = EVENT::CLICK;
        loop();
    }
    else if (_count > 1 && _pressEndTime + 200 < millis())
    {
        _event = EVENT::MULTIPLE_CLICK;
        loop();
    }
}

void QuickButton::reset()
{
    _event = EVENT::NONE;
    _duration = 0;
    _deltaTime = 0;
    _pressEndTime = 0;
    _pressed = false;
    _count = 0;
}

bool QuickButton::isPressed()
{
    return _pressed;
}

EVENT QuickButton::getEvent()
{
    return _event;
}
int QuickButton::getClickCount()
{
    return _count;
}
unsigned long QuickButton::getClickDuration()
{
    return _duration;
}

void QuickButton::setEvent(EVENT event)
{
    _event = event;
}
void QuickButton::setClickCount(int count)
{
    _count = count;
}
unsigned long QuickButton::setClickDuration(unsigned int duration)
{
    _duration = duration;
}

void QuickButton::onClick(durationClickCallback callback)
{
    _durationClickCallback = callback;
    _multipleClickCallback = nullptr;
    _mixedClickCallback = nullptr;
}
void QuickButton::onClick(multipleClickCallback callback)
{
    _durationClickCallback = nullptr;
    _multipleClickCallback = callback;
    _mixedClickCallback = nullptr;
}
void QuickButton::onClick(mixedClickCallback callback)
{
    _durationClickCallback = nullptr;
    _multipleClickCallback = nullptr;
    _mixedClickCallback = callback;
}
