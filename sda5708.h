#ifndef SDA5708_H
#define SDA5707_H

#include <stdbool.h>

#include "hardware/spi.h"
#include "pico/stdlib.h"
#include "pico/binary_info.h"

/* Hardware reference: https://www.sbprojects.net/knowledge/footprints/sda5708/index.php
   The article is actually wrong, has each byte needs to be sent in reverse (MSB in place of LSB)
   The display receives commands in SPI, but names the pins differently

   SPI_DATA_PIN -> SPI TX (MOSI)
   SPI_LOAD_PIN -> SPI CS (Chip Select)
   SPI_CLOCK_PIN -> SPI SCLK

   Since the display does not send information back, there is no need to setup a RX (MISO) pin
*/

// Init SPI communication with the display
void sda5708_init(spi_inst_t *spi, int SPI_DATA_PIN, int SPI_CLOCK_PIN, int SPI_LOAD_PIN);
// Clear the screen
void sda5708_clear(spi_inst_t *spi);
// The display only has 8 level of brightness [0, 7].
void sda5708_set_brightness(spi_inst_t* spi, uint8_t brightness);
// The display has two modes: max current (0), 12.5% max current(1);
void sda5708_set_max_current(spi_inst_t* spi, bool current);
// The display only has 8 digits
void sda5708_select_digit(spi_inst_t* spi, uint8_t digit);
//Writs a character to the select digit
void sda5708_write_character(spi_inst_t*, uint8_t* letter);

#endif
