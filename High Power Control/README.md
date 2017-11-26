# Lab 6: "High Power" Control
#### Nick Squared
While there is nothing that is really "high power", the amount of power used is more than enough to damage a microcontroller. To use this amount of power, a different approach must be used. Instead of driving the circuit directly, the micrprocessor must be used strictly as a controller, prefferebaly one that is isolated from the dangerous areas.  For this purpose, 12V will be used as power and a power resistor with an LED will be used to test the controller.

## Relays
For very high power, especially AC, solidstate relays are perfect for the job. The relay used here can handle 120V AC, but only 14V DV, this is okay for the purposes here. Relays operate with a mechanical switch, which is operated by a coil. The switch is always passing the power through, but the coil can change which side it outputs to. This coil requires 1A, or 6V with its internal resistance, to change the switch. The microproccessor cannot power that either, so a MOSFET is used to drive the coil. The MOSFET is sourced by ground, with the micrprocessor acting as the gate, this causes extremely low current to be sourced by the microprocessor itself. When turned on, the power on the other end of the coil gets a path to ground, powering the coil and changing the switch. The microprocessor is set to change on a timed interval, as the gif below shows.

<img src="https://github.com/RU09342/lab-6taking-control-over-your-embedded-life-nick-squared/blob/master/Assets/Relay%20switch.gif" width="500"/>

## MOSFET Switching
If a MOSFET is driving the coil, then driving the whole circuit is not large step. The LED is connected to 12V on one end, and a power resistor on the other. The power resistor is the drain of the MOSFET, and the source is connected to ground. The gate is still the microprocessor with the same timing, so there is still barely any current sourced by the microprocessor. Since it is a MOSFET, it could only switch 1 LED. A gif of the circuit can be found below.

<img src="https://github.com/RU09342/lab-6taking-control-over-your-embedded-life-nick-squared/blob/master/Assets/MOS%20switch.gif" width="500"/>


## Current
The main reason to use relays and MOSFETs is not voltage, but current. The microprocessor can only source a few miliamps of current.  To drop 12V over the LED and resistor, it would require 120 mA, much more than the microprocessors can handle. Instead of 120 mA, the current needed to switch the MOSFET is a few microamps.  The MOSFET is what allows the high amounts of current and voltage to be used, despite the microprocessor not being able to source anything.

