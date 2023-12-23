#include <Arduino.h>
#include <QuickButton.h>

constexpr int PIN = 7;

QuickButton button(PIN);

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    button.loop();
    if (button.getEvent() != QB_events::NONE)
    {
        Serial.print("Click");
        Serial.print(" | duration -> ");
        Serial.print(button.getClickDuration());
        Serial.print(" | count -> ");
        Serial.print(button.getClickCount());
        Serial.print("\n");

        button.reset();
    }
}