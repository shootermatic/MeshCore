#pragma once
#include <Arduino.h>
#include <vector>
#include <functional>

class RotaryInput {
public:
    void begin();
    void setMessages(const std::vector<const char*>& msgs);
    void loop(std::function<void(const char*)> onButtonPress);

private:
    int clkPin = 18;  // GPIO18
    int dtPin  = 17;  // GPIO17
    int swPin  = 16;  // GPIO16

    int lastClk = HIGH;
    unsigned long lastButtonPress = 0;

    std::vector<const char*> messages;
    int currentMessageIndex = 0;
};