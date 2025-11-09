# ESP32_DMXRepeaterToArtnet
A small DMX repeater and Artnet over Wifi transmitter

![Image showing the finished device](https://raw.githubusercontent.com/Dakkaron/ESP32_DMXRepeaterToArtnet/refs/heads/main/gfx/assembled.jpeg)


Disclaimer: This is not a polished project. This is a quick-and-dirty project that I made for my own needs. Feel free to replicate it, but your milage may vary.

# BOM
- Wemos D1 Mini ESP32 development board
- 2x Max485 breakout boards. I used [these ones here](https://de.aliexpress.com/item/1005007383346753.html). Others would likely work too, but different dimensions could make mounting them more difficult. If you choose an alternative one, make sure it has
  - Three pins for DMX (GND, D- and D+). Many don't have the GND pin, you should have it
  - 3.3V support so it can run on the same voltage as the ESP32
  - Mine only has RX and TX pins as output. If yours has pins like DE or OE, you need to adjust the schematic/code for that
- 3D printed base plate
- 3D printed Din Rail mounting tab (only necessary for DIN Rail mounting)
- Optional: L78S05CV power regulator to allow this to be powered with 7-35V input

# How to wire it up

## L78S05CV

- Use shrinkwrap around the legs that you solder to to avoid any shorts
- Vin to external power supply VCC
- GND to external power supply GND, and to any GND pin on the ESP32
- Vout to VCC pin on the ESP32

## Left Max485 breakout board

- Solder all these connections from the **bottom** of the breakout board
- Vin to 3.3V pin on the ESP32
- GND to any GND pin on the ESP32
- RX to ESP32 pin 16, and to TX of right Max485 breakout board
- Optionally: TX to ESP32 pin 17, and to RX of right Max485 breakout board. This could be used for RDM, but I haven't tested this and I cannot guarantee for anything.

## Right Max485 breakout board

- Solder all these connections from the **bottom** of the breakout board
- Vin to 3.3V pin on the ESP32
- GND to any GND pin on the ESP32
- connect RX and TX as described above

## ESP32

- Solder all these connections from the **top** of the development board
- Connect all connections as described above

# How to assemble it

- Put the L78S05CV into the hole at the top of the assembly. Route the two cables that go to the external power supply through the provided hole at the top. Screw the L78S05CV into the back plate
- Slide the ESP32 into the slot at the bottom from the side. If the tolerances are too tight, you might need to use a file to make the slot a little bigger.
- Sort in all the wires into the space below where the Max485 boards go, and screw the two boards in so that they cover all the wries in behind.
