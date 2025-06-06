#include "Mesh.h"
#include <Arduino.h>
#include "helpers/RotaryInput.h"
static RotaryInput rotary;

namespace mesh {

void Mesh::begin() {
    // Rotary initialization
    rotary.setMessages({
        "I'm home",
        "I've left",
        "Help!",
        "Where are you?",
        "Call me"
    });
    rotary.begin();

    // Mesh setup continues here (if needed)
}

void Mesh::loop() {
    rotary.loop([](const char* selectedMessage) {
        Serial.printf("[Rotary] Sending message: %s\n", selectedMessage);
        // TODO: Replace with actual message sending method
        // Example: sendGroupMessage(channelId, selectedMessage);
    });

    Dispatcher::loop(); // Existing MeshCore dispatch loop
}

bool Mesh::allowPacketForward(const mesh::Packet* packet) {
    return false;
}

uint32_t Mesh::getRetransmitDelay(const mesh::Packet* packet) {
    uint32_t t = (_radio->getEstAirtimeFor(packet->getRawLength()) * 52 / 50) / 2;
    return _rng->nextInt(0, 5) * t;
}

uint32_t Mesh::getDirectRetransmitDelay(const Packet* packet) {
    return 0;
}

uint32_t Mesh::getCADFailRetryDelay() const {
    return _rng->nextInt(1, 4) * 120;
}

int Mesh::searchPeersByHash(const uint8_t* hash) {
    return 0;
}

int Mesh::searchChannelsByHash(const uint8_t* hash, GroupChannel channels[], int max_matches) {
    return 0;
}

} // namespace mesh