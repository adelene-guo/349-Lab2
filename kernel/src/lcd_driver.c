#include <unistd.h>

#include <i2c.h>
#include <lcd_driver.h>

/** @brief Write address for PCF8574 */
#define LCD_ADDR 78 >> 1

/** @brief CCR value for a 100 kHz SCL frequency */
#define SCL_FREQ 80

void lcd_driver_init() {
    i2c_master_init(SCL_FREQ);
    uint8_t i2c_init_buf[16];

    //Upper half with E = 1
    i2c_init_buf[0] = 0b0011 << 4 | 0b1100;
    //Upper half with E = 0
    i2c_init_buf[1] = 0b0011 << 4 | 0b1000;
    //Lower half with E = 1
    i2c_init_buf[2] = 0b0000 << 4 | 0b1100;
    //Lower half with E = 0
    i2c_init_buf[3] = 0b0000 << 4 | 0b1000;

    //Upper half with E = 1
    i2c_init_buf[4] = 0b0011 << 4 | 0b1100;
    //Upper half with E = 0
    i2c_init_buf[5] = 0b0011 << 4 | 0b1000;
    //Lower half with E = 1
    i2c_init_buf[6] = 0b0000 << 4 | 0b1100;
    //Lower half with E = 0
    i2c_init_buf[7] = 0b0000 << 4 | 0b1000;

    //Upper half with E = 1
    i2c_init_buf[8] = 0b0011 << 4 | 0b1100;
    //Upper half with E = 0
    i2c_init_buf[9] = 0b0011 << 4 | 0b1000;
    //Lower half with E = 1
    i2c_init_buf[10] = 0b0000 << 4 | 0b1100;
    //Lower half with E = 0
    i2c_init_buf[11] = 0b0000 << 4 | 0b1000;

    //Upper half with E = 1
    i2c_init_buf[12] = 0b0010 << 4 | 0b1100;
    //Upper half with E = 0
    i2c_init_buf[13] = 0b0010 << 4 | 0b1000;
    //Lower half with E = 1
    i2c_init_buf[14] = 0b0000 << 4 | 0b1100;
    //Lower half with E = 0
    i2c_init_buf[15] = 0b0000 << 4 | 0b1000;

    i2c_master_write(i2c_init_buf, 16, LCD_ADDR);
	return;
}

void lcd_print(char *input){
    uint8_t i2c_write_buf[4];
    int i = 0;
    while (input[i] != '\0'){
        //Upper half with E = 1
        i2c_write_buf[0] = (input[i] >> 4) << 4 | 0b1101;
        //Upper half with E = 0
        i2c_write_buf[1] = (input[i] >> 4) << 4 | 0b1001;
        //Lower half with E = 1
        i2c_write_buf[2] = (input[i] & 0x0F) << 4 | 0b1101;
        //Lower half with E = 0
        i2c_write_buf[3] = (input[i] & 0x0F) << 4 | 0b1001;

        i2c_master_write(i2c_write_buf, 4, LCD_ADDR);
        i += 1;
    }
    return;
}

void lcd_set_cursor(uint8_t row, uint8_t col){
    (void) row;
    (void) col;
    uint8_t ddram_addr = row * 64 + col + 128;
    uint8_t i2c_cursor_buf[4];

    //Upper half with E = 1
    i2c_cursor_buf[0] = (ddram_addr & 0xF0) | 0b1100;
    //Upper half with E = 0
    i2c_cursor_buf[1] = (ddram_addr & 0xF0)| 0b1000;
    //Lower half with E = 1
    i2c_cursor_buf[2] = (ddram_addr & 0x0F) << 4 | 0b1100;
    //Lower half with E = 0
    i2c_cursor_buf[3] = (ddram_addr & 0x0F) << 4 | 0b1000;

    i2c_master_write(i2c_cursor_buf, 4, LCD_ADDR);

    return;
}

void lcd_clear() {
    uint8_t clear_buf[4];

    //Upper half with E = 1
    clear_buf[0] = 0b0000 << 4 | 0b1100;
    //Upper half with E = 0
    clear_buf[1] = 0b0000 << 4 | 0b1000;
    //Lower half with E = 1
    clear_buf[2] = 0b0001 << 4 | 0b1100;
    //Lower half with E = 0
    clear_buf[3] = 0b0001 << 4 | 0b1000;

    i2c_master_write(clear_buf, 4, LCD_ADDR);

    return;
}
