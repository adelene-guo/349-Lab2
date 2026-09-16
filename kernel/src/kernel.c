#include <gpio.h>
#include <i2c.h>
#include <printk.h>
#include <uart_polling.h>
#include <unistd.h>
#include <lcd_driver.h>
#include <keypad_driver.h>

/** @brief USARTDIV value */
#define USART_DIV 0x8B

int kernel_main() {
  uart_polling_init(USART_DIV);
  printk("Hello World");

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

  char c;

  while(1) {
    c = uart_polling_get_byte();
    uart_polling_put_byte(c);
  }

  return 0;
}
