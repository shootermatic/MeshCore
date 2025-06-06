#include "RotaryInput.h"
#include <Arduino.h>

RotaryInput::RotaryInput(int clkPin, int dtPin, int swPin)
    : clkPin(clkPin), dtPin(dtPin), swPin(swPin), lastClkState(HIGH), currentMessageIndex(0), lastButtonPress(0) {}

void RotaryInput::begin() {
    pinMode(clkPin, INPUT_PULLUP);
    pinMode(dtPin, INPUT_PULLUP);
    pinMode(swPin, INPUT_PULLUP);
    lastClkState = digitalRead(clkPin);
}

void RotaryInput::loop(std::function<void(const char*)> onSelect) {
    int currentClkState = digitalRead(clkPin);
    if (currentClkState != lastClkState && currentClkState == LOW) {
        if (digitalRead(dtPin) != currentClkState) {
            currentMessageIndex++;
        } else {
            currentMessageIndex--;
        }
        if (currentMessageIndex < 0) currentMessageIndex = messageList.size() - 1;
        if (currentMessageIndex >= messageList.size()) currentMessageIndex = 0;
        Serial.printf("Selected: %s\n", messageList[currentMessageIndex].c_str());
    }
    lastClkState = currentClkState;

    if (digitalRead(swPin) == LOW && millis() - lastButtonPress > 500) {
        lastButtonPress = millis();
        const char* message = messageList[currentMessageIndex].c_str();
        Serial.printf("Sending: %s\n", message);
        onSelect(message);
    }
}

void RotaryInput::setMessages(const std::vector<String>& messages) {
    messageList = messages;
    currentMessageIndex = 0;
}
