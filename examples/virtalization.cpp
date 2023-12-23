#include <Arduino.h>
#include <QuickButton.h>

constexpr int PIN = 7;

QuickButton button(PIN);

void setup()
{
    Serial.begin(9600);
    button.onClick([](unsigned long duration, int count)
                   {
                    Serial.print("Click");
                    Serial.print(" | duration -> ");
                    Serial.print(duration);
                    Serial.print(" | count -> ");
                    Serial.print(count);
                    Serial.print("\n"); });
}

unsigned long oldTime = 0;

void loop()
{
    if (oldTime + 2000 < millis())
    {
        oldTime = millis();

        constexpr QB_events event = QB_events::SINGLE_CLICK;
        constexpr unsigned long duration = 100;
        constexpr int count = 1;

        button.virtualizeClick(event, duration, count);
    }

    button.loop();
}