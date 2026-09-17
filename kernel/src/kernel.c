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
  keypad_init();

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

  //char c;
  char old_key = '\0';

  while(1) {
    // int button1_pressed = gpio_read(gpio_portButton1, numButton1) == 0;
    // printk("Button 1: %d \n", button1_pressed);
    // int button2_pressed = gpio_read(gpio_portButton2, numButton2) == 0;
    // printk("Button 2: %d \n", button2_pressed);
    

    char key_read = keypad_read();
    if (key_read != old_key){
      printk("%c", key_read);
      old_key = key_read;
    }
    old_key = key_read;
    
    // c = uart_polling_get_byte();
    // uart_polling_put_byte(c);
  }

  return 0;
}
