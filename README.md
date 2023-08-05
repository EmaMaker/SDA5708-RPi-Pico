The SDA5708 is 8 digit 7x5 led matrix display, the font used by the display is defined in
software.

This is a C library and example to control the display using a Raspberry Pi Pico communicating with the display using SPI.

Hardware reference: [https://www.sbprojects.net/knowledge/footprints/sda5708/index.php](!https://www.sbprojects.net/knowledge/footprints/sda5708/index.php).

You can copy the files `sda5708.h` `sda5708.c` `sda5708_fonts.h` for use in another Pico
project (remember to add `sda5708.c` in the CMakeLists.txt). It requires SPI library in the
project.
