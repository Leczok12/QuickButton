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

void loop()
{
    button.loop();
}