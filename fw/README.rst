=======
TRON FW
=======

Tron firmware. Schematics to follow.

This is a modification of an off the shelf tron disk to enhance the visual
effects. This firmware is open source.

-----------
Buildsystem
-----------

Just type make to make the firmware. This firmware runs on the teensy++.

The firmware supports upgrades on the teensy. Use the tron commandline
application: `tron dfu`

That will send a command down to the device that causes the device to jump to
the bootloader section for upgrades.

More information about the loader can be found here: www.pjrc.com

Once the device is in the bootloader, you can use the teensy loader to load the
firmware. A GUI for this loader and commandline application can be found here:
http://www.pjrc.com/teensy/loader.html

For an integrated approach, install both the tron commandline application and
teensy commandline loader into your path. Then typing `make upgrade` will
automatically make your firmware, and upgrade it for you in one easy step.

This build system was based on prjstart
