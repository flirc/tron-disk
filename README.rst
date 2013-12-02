TRON
====

Awesome tron disk.

Schematics will follow.

Here is a video of the final firmware and disk: 
https://vimeo.com/80750093

One More Video in lab:
http://vimeo.com/63198794

This is a modification of an off the shelf tron disk to enhance the visual
effects. This firmware is open source and the hardware will be documented
on the flirc blog.

CLI
---

This tool is used to send upgrades to the firmware. The commandline directory
contains a readme file.

FW
--

The firmware uses a basic scheduler to do pwm on multiple pins. The firmware
runs the LUFA USB stack so we can do upgrades with minimal effort, and is
written for the teensy 2.0

Schematic
---------

Check the schematic directory for more information regarding the parts used.
