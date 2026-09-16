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

  char c = 10;

  while(1) {
    uart_polling_put_byte(c);
    c = uart_polling_get_byte();
  }

  return 0;
}
