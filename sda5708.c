#include "sda5708.h"

/* Display has 8 levels of brightness. We encode that as level:
0 (lowest): needs 0b111 (7) to be sent to the display
7 (highest): needs 0b000 (0) to be sent to the display
The order of the bits needs to be reversed
*/
uint8_t brightness_lookup[] = {
    0b11100000,
    0b01100000,
    0b10100000,
    0b00100000,
    0b11000000,
    0b01000000,
    0b10000000,
    0b00000000
};

// The digits need to be reversed too
uint8_t digit_lookup[] = {
    0b00000000,
    0b10000000,
    0b01000000,
    0b11000000,
    0b00100000,
    0b10100000,
    0b01100000,
    0b11100000
};

uint8_t BRIGHTNESS_LEVEL = 0b000;
bool PEAK_CURRENT = 0b0;

void sda5708_init(spi_inst_t *spi, int SPI_DATA_PIN, int SPI_CLOCK_PIN, int SPI_LOAD_PIN){
    // Enable SPI 0 at 1 MHz and connect to GPIOs
    spi_init(spi_default, 1000*1000);

    gpio_set_function(SPI_DATA_PIN, GPIO_FUNC_SPI);
    gpio_set_function(SPI_CLOCK_PIN, GPIO_FUNC_SPI);
    gpio_set_function(SPI_LOAD_PIN, GPIO_FUNC_SPI);

    // Make the SPI pins available to picotool
    bi_decl(bi_4pins_with_func(PICO_DEFAULT_SPI_RX_PIN, PICO_DEFAULT_SPI_TX_PIN, PICO_DEFAULT_SPI_SCK_PIN, PICO_DEFAULT_SPI_CSN_PIN, GPIO_FUNC_SPI));
}

// Clear the screen
void sda5708_clear(spi_inst_t *spi){
    // This whole sharade of bitwise operations is needed because the hardware reads the bits in the
    // bytes in reverse order (considers MSB the LSB)
    uint8_t out[] ={
	BRIGHTNESS_LEVEL | (PEAK_CURRENT << 5) | 0b00000011, //clear
	BRIGHTNESS_LEVEL | (PEAK_CURRENT << 5) | 0b00000111 //return to normal
    };

    spi_write_blocking(spi, out, 2);
}

// The display only has 8 level of brightness [0, 7].
void sda5708_set_brightness(spi_inst_t* spi, uint8_t brightness){
    if(brightness > 7) brightness = 7;
    BRIGHTNESS_LEVEL = brightness_lookup[brightness];
    uint8_t b = BRIGHTNESS_LEVEL | (PEAK_CURRENT << 5) | 0b00000111; //return to normal

    spi_write_blocking(spi, &b, 1);
}

void sda5708_set_max_current(spi_inst_t* spi, bool current){
    PEAK_CURRENT = current;
}

// The display only has 8 digits
void sda5708_select_digit(spi_inst_t* spi, uint8_t digit){
    if(digit > 7) digit = 7;
    uint8_t b = digit_lookup[digit] | 0b00000101;

    spi_write_blocking(spi, &b, 1);
}

//Writs a character to the select digit
void sda5708_write_character(spi_inst_t* spi, uint8_t* letter){
    spi_write_blocking(spi, letter, 7);
}

