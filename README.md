# MeshCoreCanned

A custom fork of [MeshCore](https://github.com/ripplebiz/MeshCore) designed to add **rotary encoder support** and **canned message functionality** for compact communication devices.

## 🚧 Work in Progress

This fork introduces a rotary encoder interface that allows users to:
- Scroll through a list of predefined ("canned") messages
- Press the encoder to send a selected message

These messages are intended to be sent over the MeshCore protocol, typically to a group or a parent node (e.g. a repeater or a base station). The goal is to create a user-friendly interface suitable for low-interaction, glove-friendly, or child-safe devices.

## 🔧 What's New

- `RotaryInput` class handles rotary encoder interaction
- Rotary encoder GPIOs default to:
  - `CLK` – GPIO 18
  - `DT` – GPIO 17
  - `SW` – GPIO 16
- Simple message list UI expected on screen (future)
- Message sending wired into `Mesh::loop()`
- Persistence and remote configuration coming soon

## 🤝 How to Help

This is very much a **work-in-progress**, and help is appreciated. You can contribute by:

- 🧠 Reviewing or improving the `RotaryInput` abstraction
- ⚙️ Ensuring compatibility with upstream MeshCore changes
- 🪛 Suggesting a better mechanism for message sending (e.g. `sendGroupMessage`, `sendRawMessage`, etc.)
- 💾 Implementing message persistence (NVS or filesystem)
- 🧪 Testing on different ESP32 boards (e.g. Heltec V3, T-Echo)

## 🔌 Setup

Make sure your `platformio.ini` uses the correct environment (e.g. `Heltec_v3_companion_radio_ble`) and has the `RotaryInput.*` files included in your build path. Example:

```ini
build_src_filter = 
  +<*.cpp>
  +<helpers/*.cpp>
```

### 📻 📣 [Vulcan] 917.375 🥝 
