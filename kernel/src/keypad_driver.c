#include <unistd.h>

#include <gpio.h>
#include <keypad_driver.h>

/** @brief Keypad pins for 3 columns and 4 rows */
#define KEYPAD_COL1_PORT GPIO_B
#define KEYPAD_COL1_PIN 0

#define KEYPAD_COL2_PORT GPIO_C
#define KEYPAD_COL2_PIN 0

#define KEYPAD_COL3_PORT GPIO_A
#define KEYPAD_COL3_PIN  1

#define KEYPAD_ROW1_PORT GPIO_C
#define KEYPAD_ROW1_PIN  1

#define KEYPAD_ROW2_PORT GPIO_A
#define KEYPAD_ROW2_PIN  10

#define KEYPAD_ROW3_PORT GPIO_A
#define KEYPAD_ROW3_PIN  0

#define KEYPAD_ROW4_PORT GPIO_A
#define KEYPAD_ROW4_PIN 4

void keypad_init() {
    // Column 1
    gpio_port gpio_portCOL1 = KEYPAD_COL1_PORT;
    unsigned int numCOL1     = KEYPAD_COL1_PIN;
    unsigned int modeCOL1    = MODE_GP_OUTPUT;
    unsigned int otypeCOL1   = OUTPUT_PUSH_PULL;
    unsigned int speedCOL1   = OUTPUT_SPEED_LOW;
    unsigned int pupdCOL1    = PUPD_NONE;
    unsigned int altCOL1     = 0;
    gpio_init(gpio_portCOL1, numCOL1, modeCOL1, otypeCOL1, speedCOL1, pupdCOL1, altCOL1);

    // Column 2
    gpio_port gpio_portCOL2 = KEYPAD_COL2_PORT;
    unsigned int numCOL2     = KEYPAD_COL2_PIN;
    unsigned int modeCOL2    = MODE_GP_OUTPUT;
    unsigned int otypeCOL2   = OUTPUT_PUSH_PULL;
    unsigned int speedCOL2   = OUTPUT_SPEED_LOW;
    unsigned int pupdCOL2    = PUPD_NONE;
    unsigned int altCOL2     = 0;
    gpio_init(gpio_portCOL2, numCOL2, modeCOL2, otypeCOL2, speedCOL2, pupdCOL2, altCOL2);

    // Column 3
    gpio_port gpio_portCOL3 = KEYPAD_COL3_PORT;
    unsigned int numCOL3     = KEYPAD_COL3_PIN;
    unsigned int modeCOL3    = MODE_GP_OUTPUT;
    unsigned int otypeCOL3   = OUTPUT_PUSH_PULL;
    unsigned int speedCOL3   = OUTPUT_SPEED_LOW;
    unsigned int pupdCOL3    = PUPD_NONE;
    unsigned int altCOL3     = 0;
    gpio_init(gpio_portCOL3, numCOL3, modeCOL3, otypeCOL3, speedCOL3, pupdCOL3, altCOL3);

    // Row 1
    gpio_port gpio_portROW1 = KEYPAD_ROW1_PORT;
    unsigned int numROW1     = KEYPAD_ROW1_PIN;
    unsigned int modeROW1    = MODE_INPUT;
    unsigned int otypeROW1   = OUTPUT_PUSH_PULL;
    unsigned int speedROW1   = OUTPUT_SPEED_LOW;
    unsigned int pupdROW1    = PUPD_PULL_DOWN;
    unsigned int altROW1     = 0;
    gpio_init(gpio_portROW1, numROW1, modeROW1, otypeROW1, speedROW1, pupdROW1, altROW1);

    // Row 2
    gpio_port gpio_portROW2 = KEYPAD_ROW2_PORT;
    unsigned int numROW2     = KEYPAD_ROW2_PIN;
    unsigned int modeROW2    = MODE_INPUT;
    unsigned int otypeROW2   = OUTPUT_PUSH_PULL;
    unsigned int speedROW2   = OUTPUT_SPEED_LOW;
    unsigned int pupdROW2    = PUPD_PULL_DOWN;
    unsigned int altROW2     = 0;
    gpio_init(gpio_portROW2, numROW2, modeROW2, otypeROW2, speedROW2, pupdROW2, altROW2);

    // Row 3
    gpio_port gpio_portROW3 = KEYPAD_ROW3_PORT;
    unsigned int numROW3     = KEYPAD_ROW3_PIN;
    unsigned int modeROW3    = MODE_INPUT;
    unsigned int otypeROW3   = OUTPUT_PUSH_PULL;
    unsigned int speedROW3   = OUTPUT_SPEED_LOW;
    unsigned int pupdROW3    = PUPD_PULL_DOWN;
    unsigned int altROW3     = 0;
    gpio_init(gpio_portROW3, numROW3, modeROW3, otypeROW3, speedROW3, pupdROW3, altROW3);

    // Row 4
    gpio_port gpio_portROW4 = KEYPAD_ROW4_PORT;
    unsigned int numROW4     = KEYPAD_ROW4_PIN;
    unsigned int modeROW4    = MODE_INPUT;
    unsigned int otypeROW4   = OUTPUT_PUSH_PULL;
    unsigned int speedROW4   = OUTPUT_SPEED_LOW;
    unsigned int pupdROW4    = PUPD_PULL_DOWN;
    unsigned int altROW4     = 0;
    gpio_init(gpio_portROW4, numROW4, modeROW4, otypeROW4, speedROW4, pupdROW4, altROW4);

    return;
}

int read_row() {
    gpio_port gpio_portROW1 = KEYPAD_ROW1_PORT;
    unsigned int numROW1     = KEYPAD_ROW1_PIN;

    gpio_port gpio_portROW2 = KEYPAD_ROW2_PORT;
    unsigned int numROW2     = KEYPAD_ROW2_PIN;

    gpio_port gpio_portROW3 = KEYPAD_ROW3_PORT;
    unsigned int numROW3     = KEYPAD_ROW3_PIN;

    gpio_port gpio_portROW4 = KEYPAD_ROW4_PORT;
    unsigned int numROW4     = KEYPAD_ROW4_PIN;

    int row_pressed;

    if (gpio_read(gpio_portROW1, numROW1)){
        for (int i=0; i < 15000; i++);
        row_pressed = 1;
    } else if (gpio_read(gpio_portROW2, numROW2)){
        for (int i=0; i < 15000; i++);
        row_pressed = 2;
    } else if (gpio_read(gpio_portROW3, numROW3)){
        for (int i=0; i < 15000; i++);
        row_pressed = 3;
    } else if (gpio_read(gpio_portROW4, numROW4)){
        for (int i=0; i < 15000; i++);
        row_pressed = 4;
    } else {
        row_pressed = 0;
    }

    return row_pressed;
}

char keypad_read( ){
    gpio_port gpio_portCOL1 = KEYPAD_COL1_PORT;
    unsigned int numCOL1     = KEYPAD_COL1_PIN;

    gpio_port gpio_portCOL2 = KEYPAD_COL2_PORT;
    unsigned int numCOL2     = KEYPAD_COL2_PIN;

    gpio_port gpio_portCOL3 = KEYPAD_COL3_PORT;
    unsigned int numCOL3     = KEYPAD_COL3_PIN;
    
    gpio_set(gpio_portCOL1, numCOL1);
    gpio_clr(gpio_portCOL2, numCOL2);
    gpio_clr(gpio_portCOL3, numCOL3);
    int row_pressed = read_row();

    for (int i=0; i < 30000; i++);

    int row_pressed_1;
    int row_pressed_2;

    char key_pressed = '\0';

    if (row_pressed == 0){
        gpio_clr(gpio_portCOL1, numCOL1);
        gpio_set(gpio_portCOL2, numCOL2);
        gpio_clr(gpio_portCOL3, numCOL3);
        row_pressed_1 = read_row();
    } else {
        if (row_pressed == 1){
          key_pressed = '1';
       } else if (row_pressed == 2){
          key_pressed = '4';
       } else if (row_pressed == 3){
          key_pressed = '7';
       } else if (row_pressed == 4){
          key_pressed = '*';
       }
    }

    for (int i=0; i < 30000; i++);

    if (row_pressed_1 == 0){
        gpio_clr(gpio_portCOL1, numCOL1);
        gpio_clr(gpio_portCOL2, numCOL2);
        gpio_set(gpio_portCOL3, numCOL3);
        row_pressed_2 = read_row();
    } else{
        if (row_pressed_1 == 1){
          key_pressed = '2';
       } else if (row_pressed_1 == 2){
          key_pressed = '5';
       } else if (row_pressed_1 == 3){
          key_pressed = '8';
       } else if (row_pressed_1 == 4){
          key_pressed = '0';
       }
    }

    for (int i=0; i < 30000; i++);
    
    if (row_pressed_2 == 0){
        gpio_clr(gpio_portCOL1, numCOL1);
        gpio_clr(gpio_portCOL2, numCOL2);
        gpio_clr(gpio_portCOL3, numCOL3);
        key_pressed = '\0';
    } else{
        if (row_pressed_2 == 1){
          key_pressed = '3';
       } else if (row_pressed_2 == 2){
          key_pressed = '6';
       } else if (row_pressed_2 == 3){
          key_pressed = '9';
       } else if (row_pressed_2 == 4){
          key_pressed = '#';
       }
    }

    for (int i=0; i < 30000; i++);
    return key_pressed;
}