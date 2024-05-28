# OpenRCS
Open Remote Communication System

# Description
This project began life as a bushfire detection system, however due to some shipping issues and failing parts has turned into a more general LoRa based communication network. (I'm looking at you, BOTH the temperature sensors >:( Yes, they both died.)

There are 2 operating modes for the nodes on this system. The first mode is the network node, which is responsible for rebroadcasting messages locally (with a timeout to prevent flooding the network) and monitoring the smoke sensor to generate alerts, and the second mode is responsible for receiving pages and alerts from the network.
This network is primarily a repeating and alerting network, meaning that every node will receive all messages and no encryption is available.

# Network Nodes
Network nodes comprise of:
*ESP32 (onboard the TTGO LoRa Module)
*LoRa module (onboard the TTGO LoRa Module)
*OLED display (onboard the TTGO LoRa Module)
*GPS receiver
*MQ135 air quality monitor
*Manual test button

The network nodes constanly monitor the LoRa based network listening for any messages to be received. When a message is received, it is then processed by the ESP32 to determine what kind of message it is, and how to handle it. Control messages are currently ignored by the network, but all other messages are retransmitted (unless received within 10 seconds of the last transmittion, in which case the packet is dropped to prevent network flooding).
The network nodes also continuously checking for air quality alerts from the MQ135 sensor to detect hazardous conditions such as smoke, and will create an alert whenever the digital output of the MQ135 goes high, indicating smoke detection (or detection of other hazardous gases). These alerts are only transmitted when the status changes, and at a maximum interval of 10 seconds to again maintain the network integrity.
The OLED is used to display both the nodes' alert status and the last received message. These pages can be scrolled through using the onboard button.

# Personal Nodes
Personal nodes comprise of:
*ESP32 (onboard the TTGO LoRa Module)
*LoRa module (onboard the TTGO LoRa Module)
*OLED display (onboard the TTGO LoRa Module)
*GPS receiver
*Action button

Personal nodes will NOT rebroadcast any messages, and instead passively wait for alerts and notify the user via the action button LED. When an alert is received, the action button LED lights up, whereas a message (referred to as a "page") will have no action.

# Usage
When uploading to a device, simply set define either `MODE_NETWORK` or `MODE_PERSONAL` in config.h to whichever node mode is needed for the device, and upload. The network information can be modified in the secrets.h file, where the frequecy for the network and the network and access codes can be changed.

The GPS modules do not work well indoors, so the time may not sync when testing indoors.

# Requirements
The project is set up using VS Code and PlatformIO, using the following libraries:
*Arduino.h (included in PlatformIO)
*LoRa by Sandeep Mistry (Available in PlatformIO)
*TinyGPSPlus (included in lib/)
*ThingPulse OLED SSD1306 (included in lib/)

# Damage Done
This project has seen me have horrendous luck when it comes to parts. Some parts never showed up, some parts gave up (BOTH temperature sensors no longer function after being driven by 3.3v, the same as when driven by the Nano 33 IoT...), and some parts simply would not cooperate with the ESP32 (mainly the buzzer).
The parts order containing the GPS receivers and air quality sensors arrived only a few days ago, making the prototyping stage more of a rapid prototying frenzy instead of a light jog through the park at night.