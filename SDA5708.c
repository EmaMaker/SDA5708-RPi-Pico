#include <stdio.h>

#include "pico/stdlib.h"

#include "sda5708.h"
#include "sda5708_fonts.h"

#define BUF_LEN 27

int main() {
#if !defined(spi_default) || !defined(PICO_DEFAULT_SPI_SCK_PIN) || !defined(PICO_DEFAULT_SPI_TX_PIN) || !defined(PICO_DEFAULT_SPI_RX_PIN) || !defined(PICO_DEFAULT_SPI_CSN_PIN)
#warning spi/spi_master example requires a board with SPI pins
    puts("Default SPI pins were not defined");
#else

    printf("SPI master example\n");

    sda5708_init(spi_default, PICO_DEFAULT_SPI_TX_PIN, PICO_DEFAULT_SPI_SCK_PIN, PICO_DEFAULT_SPI_CSN_PIN);
    sda5708_clear(spi_default);

    sda5708_set_brightness(spi_default, 3);
    sda5708_set_max_current(spi_default, 0);

    /*int i = 0, a = 1; 
    while(1){
	sda5708_clear(spi_default);
	sda5708_select_digit(spi_default, i);
	sda5708_write_character(spi_default, letter_O);
	i += a;
	if( i >= 7 || i <= 0) a = -a;

	sleep_ms(500);
    }*/

    uint8_t* buf[BUF_LEN] = {
	letter_A,
	letter_B,
	letter_C,
	letter_D,
	letter_E,
	letter_F,
	letter_G,
	letter_H,
	letter_I,
	letter_J,
	letter_K,
	letter_L,
	letter_M,
	letter_N,
	letter_O,
	letter_P,
	letter_Q,
	letter_R,
	letter_S,
	letter_T,
	letter_U,
	letter_V,
	letter_W,
	letter_X,
	letter_Y,
	letter_Z,
	character_empty
    };

    int off = 0;
    while(1){
	sda5708_clear(spi_default);
	for(int i = 0; i < 8; i++){
	    sda5708_select_digit(spi_default, i);
	    sda5708_write_character(spi_default, buf [(off+i) % BUF_LEN]);
	}
	    off = (off+1) % BUF_LEN;
	sleep_ms(350);
    }
    

#endif
}
