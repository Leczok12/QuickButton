#ifndef QUICK_BUTTON
#define QUICK_BUTTON

#include <Arduino.h>

enum EVENT
{
    NONE,
    CLICK,
    MULTIPLE_CLICK
};

typedef void (*durationClickCallback)(unsigned long);
typedef void (*multipleClickCallback)(int);
typedef void (*mixedClickCallback)(unsigned long, int);

class QuickButton
{
public:
    QuickButton(int pin, bool callbacks_auto_reset = true);
    ~QuickButton();

    void loop();
    void reset();
    bool isPressed();

    EVENT getEvent();
    int getClickCount();
    unsigned long getClickDuration();

    void setEvent(EVENT event);
    void setClickCount(int count);
    unsigned long setClickDuration(unsigned int duration);

    void onClick(durationClickCallback callback);
    void onClick(multipleClickCallback callback);
    void onClick(mixedClickCallback callback);

private:
    const int _pin;
    const bool _callbacksAutoReset;

    durationClickCallback _durationClickCallback;
    multipleClickCallback _multipleClickCallback;
    mixedClickCallback _mixedClickCallback;

    EVENT _event;

    unsigned long _duration;
    unsigned long _deltaTime;
    unsigned long _pressEndTime;
    bool _pressed;
    int _count;
};

#endif