#include "Mesh.h"
#include <Arduino.h>

#define ROTARY_CLK 18 // outB
#define ROTARY_DT  17 // outA
#define ROTARY_SW  16

const char* cannedMessages[] = {
  "I'm home", "Leaving now", "Help!", "Call me back"
};
const int NUM_MESSAGES = sizeof(cannedMessages) / sizeof(cannedMessages[0]);

int currentMessageIndex = 0;
int lastClkState = HIGH;
unsigned long lastButtonPress = 0;

namespace mesh {

void Mesh::begin() {
  pinMode(ROTARY_CLK, INPUT_PULLUP);
  pinMode(ROTARY_DT, INPUT_PULLUP);
  pinMode(ROTARY_SW, INPUT_PULLUP);
  lastClkState = digitalRead(ROTARY_CLK);

  Dispatcher::begin();
}

void Mesh::loop() {
  Dispatcher::loop();

  int currentClkState = digitalRead(ROTARY_CLK);
  if (currentClkState != lastClkState && currentClkState == LOW) {
    int dtState = digitalRead(ROTARY_DT);
    if (dtState != currentClkState) {
      currentMessageIndex = (currentMessageIndex + 1) % NUM_MESSAGES;
    } else {
      currentMessageIndex = (currentMessageIndex - 1 + NUM_MESSAGES) % NUM_MESSAGES;
    }
    Serial.printf("Selected: %s\n", cannedMessages[currentMessageIndex]);
  }
  lastClkState = currentClkState;

  if (digitalRead(ROTARY_SW) == LOW && millis() - lastButtonPress > 500) {
    lastButtonPress = millis();
    const char* message = cannedMessages[currentMessageIndex];

    Serial.printf("Sending: %s\n", message);

    // TODO: Replace with your MeshCore message send logic
    // Example (pseudo-code):
    // sendTextMessage("!abcdef", message);
  }
}

bool Mesh::allowPacketForward(const mesh::Packet* packet) {
  return false;  // by default, Transport NOT enabled
}

uint32_t Mesh::getRetransmitDelay(const mesh::Packet* packet) {
  uint32_t t = (_radio->getEstAirtimeFor(packet->getRawLength()) * 52 / 50) / 2;
  return _rng->nextInt(0, 5) * t;
}

uint32_t Mesh::getDirectRetransmitDelay(const Packet* packet) {
  return 0;  // by default, no delay
}

uint32_t Mesh::getCADFailRetryDelay() const {
  return _rng->nextInt(1, 4) * 120;
}

int Mesh::searchPeersByHash(const uint8_t* hash) {
  return 0;  // not found
}

int Mesh::searchChannelsByHash(const uint8_t* hash, GroupChannel channels[], int max_matches) {
  return 0;  // not found
}

} // namespace mesh