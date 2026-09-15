#include <gpio.h>
#include <i2c.h>
#include <printk.h>
#include <uart_polling.h>
#include <unistd.h>
#include <lcd_driver.h>
#include <keypad_driver.h>


int kernel_main() {
  uart_polling_init(USART_DIV);
  uart_polling_put_byte(67);
  uart_polling_get_byte();

  while(1);

  return 0;
}
