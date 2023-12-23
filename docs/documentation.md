# _Documentation_

## Connection

| Button pin | connected to |
| :--------: | :----------: |
|     1      |   GPIO pin   |
|     2      |     GND      |

## Declaration

```c++
#include <QuickButton.h>

constexpr int GPIO_PIN = 7;
constexpr bool CALLBACKS_AUTO_RESET = true;

QuickButton button(GPIO_PIN, CALLBACKS_AUTO_RESET);
```

|                      |                               |
| :------------------: | :---------------------------: |
|       GPIO_PIN       | pin where button is connected |
| CALLBACKS_AUTO_RESET |  reset button after callback  |

## Usage

### Basic

```c++
...

void loop()
{
    button.loop();
    if (button.getEvent() != QB_events::NONE)
    {
        switch (button.getClickCount())
        {
        case 1:
            if (button.getClickDuration() < 500)
            // Short click
            else
            // Long click
            break;
        case 2:
            // double click
            break;
        }
        button.reset();
    }
}
```

### Callbacks

#### Click duartion callback

```c++
...

void setup()
{
      button.onClick([](int count)
                     {
                       // count
                     });
}
```

#### Click count callback

```c++
...

void setup()
{
      button.onClick([](unsigned long duration)
                     {
                       // duration
                     });
}
```

#### Mixed callback

```c++
...

void setup()
{
      button.onClick([](unsigned long duration, int count)
                     {
                       // duration & count
                     });
}
```

If you set another callback, previous callback will be ersed.

## Virtualization

```c++
constexpr QB_events event = QB_events::SINGLE_CLICK;
constexpr unsigned long duration = 100;
constexpr int count = 1;

button.virtualizeClick(event,duration,count);
```

---

[<-](../README.md)
