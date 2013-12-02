Schematic
=========

The schematics in this directory are for demonstration. There were several
modules put together to make the disk, this shows the more important connections

Parts Used
----------

### Teensy

The heart of the project was a [teensy microcontroller]
(https://www.pjrc.com/store/teensy.html)

The port wirings are shown in the schematic as well as the required circuits
needed to drive the LED's. The FETs act as a simple switch to turn on and off
the LEDs. Outputing a high to the gate of the mosfet turns them on, and hence,
turns on the LEDs.

### LEDS

LED strips were somethig like the [following]
(http://www.superbrightleds.com/moreinfo/top-emitting/high-power-led-flexible-light-strip--nfls-x600-wht/1487/)

The strip can be cut into 3 segments and needs 12 volts per segment.

The inner ring of the microcontroller had 8 cut strips while the outer circle
had 12.

The inner circle is hooked up to PORTB, while the outer 12 groups were hooked
up to D and F.

### Button

The button on the tron disk was already there and we re-wired it to port C6 of
the microcontroller. We activated the internal pullup of the pin, so we didn't
need any external circuitry. Debouncing was done in software.

### Lithium ION Batteries

We used two of these guys stacked in parallel. [link]
(https://www.sparkfun.com/products/341)

Not quite positive those were the exact ones.

### Boost converter

Because we wanted this battery powered, we needed 12Volts to power the LEDs.
We used [this boost converter](http://www.pololu.com/product/2117) to get us
from 3.7 to 12V

### Battery Charger

We needed a way to charge the batteries, so we stuffed one of these guys in
there: [link](https://www.sparkfun.com/products/10217)

### Linear Regulator

We added a small linear regulator off of 12V to output 5 for the micro. This is
generally to big of a voltage drop, however, the amount of current needed to
power the micro is so small, it's fine.

We used a small sot-23 package linear regulator, and used
[these breakout boards](https://www.sparkfun.com/products/717)
