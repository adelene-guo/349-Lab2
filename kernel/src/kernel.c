/**
 * @file kernel.c
 *
 * @brief
 * This file contains the main kernel code that initializes UART, the keypad, 
 * ADC, I2C, LCD on the connected arudino STM32. Creates an interactive system 
 * that takes input from the keypad and displays it on the LCD screen and 
 * outputs the values from the light sensor into minicom.
 * @date 10/3/2026
 *
 * @author Alexis and Adie
 */


#include <gpio.h>
#include <adc.h>
#include <i2c.h>
#include <printk.h>
#include <uart_polling.h>
#include <unistd.h>
#include <lcd_driver.h>
#include <keypad_driver.h>

/** @brief USARTDIV value */
#define USART_DIV 0x8B

/** @brief CCR value for a 100 kHz SCL frequency */
#define SCL_FREQ 80

/** @brief Main body of kernel code that initializes systems and implements
    keypad and minicom displays */
int kernel_main() {
  uart_polling_init(USART_DIV);
  keypad_init();
  adc_init();
  i2c_master_init(SCL_FREQ);
  lcd_driver_init();
  
  lcd_clear();
  for (int i=0; i<100; i++){} // wait after clear
  uint8_t lcd_row = 0;
  uint8_t lcd_col = 0;

  char old_key = '\0';
  while (1) {
    // read light sensor value
    uint16_t light_sensor = adc_read_chan(5);
    printk("Light Sensor Value: %d \n", light_sensor);

    // echo keypad presses to the LCD
    char key_read = keypad_read();

    if (key_read != old_key) {
      if (key_read == '*') {
        lcd_row = (lcd_row+1) % 2;
        lcd_set_cursor(lcd_row, lcd_col);
      }
      else if (key_read == '#') {
        lcd_clear();
        for (int i=0; i<100; i++){} // wait after clear
        lcd_row = 0;
        lcd_col = 0;
        lcd_set_cursor(lcd_row, lcd_col);
      }
      else {
        char key_print[2] = {key_read, '\0'};
        lcd_print(key_print);
      }
    old_key = key_read;
    }
  }

  //Initialize and set green and red LED gpio pins
  gpio_port gpio_portGreen = GPIO_A;
  unsigned int numGreen    = 8;
  unsigned int modeGreen   = MODE_GP_OUTPUT;
  unsigned int otypeGreen  = OUTPUT_PUSH_PULL;
  unsigned int speedGreen  = OUTPUT_SPEED_LOW;
  unsigned int pupdGreen   = PUPD_NONE;
  unsigned int altGreen    = ALT0;  
  gpio_init(gpio_portGreen, numGreen, modeGreen, otypeGreen, speedGreen, pupdGreen, altGreen);
  gpio_set(gpio_portGreen, numGreen);

  gpio_port gpio_portRed = GPIO_B;
  unsigned int numRed    = 10;
  unsigned int modeRed   = MODE_GP_OUTPUT;
  unsigned int otypeRed  = OUTPUT_PUSH_PULL;
  unsigned int speedRed  = OUTPUT_SPEED_LOW;
  unsigned int pupdRed   = PUPD_NONE;
  unsigned int altRed    = ALT0;  
  gpio_init(gpio_portRed, numRed, modeRed, otypeRed, speedRed, pupdRed, altRed);
  gpio_set(gpio_portRed, numRed);


  //Initialize button gpio pins, internal pull-up since it's connected to ground
  gpio_port gpio_portButton1 = GPIO_A;
  unsigned int numButton1    = 9;
  unsigned int modeButton1   = MODE_INPUT;
  unsigned int otypeButton1  = OUTPUT_PUSH_PULL;
  unsigned int speedButton1  = OUTPUT_SPEED_LOW;
  unsigned int pupdButton1   = PUPD_PULL_UP;
  unsigned int altButton1    = ALT0;  
  gpio_init(gpio_portButton1, numButton1, modeButton1, otypeButton1, speedButton1, pupdButton1, altButton1);
  
  gpio_port gpio_portButton2 = GPIO_C;
  unsigned int numButton2    = 7;
  unsigned int modeButton2   = MODE_INPUT;
  unsigned int otypeButton2  = OUTPUT_PUSH_PULL;
  unsigned int speedButton2  = OUTPUT_SPEED_LOW;
  unsigned int pupdButton2   = PUPD_PULL_UP;
  unsigned int altButton2    = ALT0;  
  gpio_init(gpio_portButton2, numButton2, modeButton2, otypeButton2, speedButton2, pupdButton2, altButton2);

  return 0;
}
