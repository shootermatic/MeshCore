#include "RotaryInput.h"

void RotaryInput::begin() {
    pinMode(clkPin, INPUT_PULLUP);
    pinMode(dtPin, INPUT_PULLUP);
    pinMode(swPin, INPUT_PULLUP);
    lastClk = digitalRead(clkPin);
}

void RotaryInput::setMessages(const std::vector<const char*>& msgs) {
    messages = msgs;
    currentMessageIndex = 0;
}

void RotaryInput::loop(std::function<void(const char*)> onButtonPress) {
    int currentClk = digitalRead(clkPin);
    if (currentClk != lastClk && currentClk == LOW) {
        if (digitalRead(dtPin) != currentClk) {
            currentMessageIndex++;
        } else {
            currentMessageIndex--;
        }

        if (currentMessageIndex < 0) currentMessageIndex = messages.size() - 1;
        if (currentMessageIndex >= (int)messages.size()) currentMessageIndex = 0;

        Serial.printf("[Rotary] Selected: %s\n", messages[currentMessageIndex]);
    }
    lastClk = currentClk;

    if (digitalRead(swPin) == LOW && millis() - lastButtonPress > 500) {
        lastButtonPress = millis();
        if (!messages.empty()) {
            onButtonPress(messages[currentMessageIndex]);
        }
    }
}