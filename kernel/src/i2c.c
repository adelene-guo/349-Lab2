/**
 * @file i2c.c
 *
 * @brief
 * This file contains the implementation of the I2C driver for the STM32F4 microcontroller.
 * It provides functions to initialize the I2C and communicate with slave devices.
 * @date 10/3/2026
 *
 * @author Alexis and Adie
 */

#include <unistd.h>
#include <gpio.h>
#include <i2c.h>
#include <rcc.h>

/** @brief Enable bit for I2C Clock */
#define RCC_EN (1 << 21)

/** @brief Base address for I2C1 */
#define I2C1_BASE  (struct i2c_reg_map *) 0x40005400

/** @brief I2C Peripheral Enable bit */
#define I2C_PE 1

/** @brief I2C Busy bit */
#define I2C_BUSY (1 << 1)

/** @brief Peripheral Clock Frequency - 16MHz */
#define I2C_FREQ 16

/** @brief Bit 14 of I2C_OAR1 must always be set to 1 */
#define I2C_OAR1_SET (1 << 14)

/** @brief  */
/** T_rise = (max/T_PCLK1) 
           = 1000ns / (1/16Mhz) + 
           = 17 = 0x11*/
#define I2C_TRISE_VAL 0x11 



/** @brief I2C START bit */
#define I2C_START (1 << 8)

/** @brief I2C STOP bit */
#define I2C_STOP (1 << 9)

/** @brief I2C ACK bit */
#define I2C_ACK (1 << 10)

/** @brief I2C SB bit */
#define I2C_SB (1 << 0)

/** @brief I2C TxE bit */
#define I2C_TxE (1 << 7)

/** @brief I2C BTF bit */
#define I2C_BTF (1 << 2)

/** @brief I2C WRITE bit */
#define I2C_WRITE_BIT 0

/** @brief I2C ADDR bit */
#define I2C_ADDR (1 << 1)


/** @brief The I2C register map. */
struct i2c_reg_map {
    volatile uint32_t I2C_CR1;   /**<  Control register 1 */
    volatile uint32_t I2C_CR2;   /**<  Control register 2 */
    volatile uint32_t I2C_OAR1;  /**<  Own address register 1 */
    volatile uint32_t I2C_OAR2;  /**<  Own address register 2 */
    volatile uint32_t I2C_DR;    /**<  Data register */
    volatile uint32_t I2C_SR1;   /**<  Status register 1 */
    volatile uint32_t I2C_SR2;   /**<  Status register 2 */
    volatile uint32_t I2C_CCR;   /**<  Clock control register */
    volatile uint32_t I2C_TRISE; /**<  TRISE register */
    volatile uint32_t I2C_FLTR;  /**<  FLTR register */
};

/** @brief Initialize the I2C master */
void i2c_master_init(uint16_t clk){

    gpio_port gpio_portSCL = GPIO_B;
    unsigned int numSCL    = 8;
    unsigned int modeSCL   = MODE_ALT;
    unsigned int otypeSCL  = OUTPUT_OPEN_DRAIN;
    unsigned int speedSCL  = OUTPUT_SPEED_LOW;
    unsigned int pupdSCL   = PUPD_NONE;
    unsigned int altSCL    = ALT4;
    gpio_init(gpio_portSCL, numSCL, modeSCL, otypeSCL, speedSCL, pupdSCL, altSCL);

    gpio_port gpio_portSDA = GPIO_B;
    unsigned int numSDA    = 9;
    unsigned int modeSDA   = MODE_ALT;
    unsigned int otypeSDA  = OUTPUT_OPEN_DRAIN;
    unsigned int speedSDA  = OUTPUT_SPEED_LOW;
    unsigned int pupdSDA   = PUPD_NONE;
    unsigned int altSDA    = ALT4;
    gpio_init(gpio_portSDA, numSDA, modeSDA, otypeSDA, speedSDA, pupdSDA, altSDA);

    struct rcc_reg_map *rcc = RCC_BASE;
    rcc->apb1_enr |= RCC_EN;
    
    struct i2c_reg_map *i2c = I2C1_BASE;
    i2c->I2C_CR2 |= I2C_FREQ;
    i2c->I2C_CCR |= clk; 
    i2c->I2C_TRISE = I2C_TRISE_VAL;
    i2c->I2C_CR1 |= I2C_PE; // enables peripheral
    i2c->I2C_CR1 |= I2C_ACK;

    return;
}

/** @brief Start the I2C master */
void i2c_master_start() {
    struct i2c_reg_map *i2c = I2C1_BASE;
    while (i2c->I2C_SR2 & I2C_BUSY); // Wait while I2C bus is busy
    i2c->I2C_CR1 |= I2C_START;
    while (!(i2c->I2C_SR1 & I2C_SB)); // EV5 wait while SB is not asserted
    return;
}

/** @brief Stop the I2C master */
void i2c_master_stop() {
    struct i2c_reg_map *i2c = I2C1_BASE;
    while (!(i2c->I2C_SR1 & I2C_TxE)); // EV8_2
    while (!(i2c->I2C_SR1 & I2C_BTF)); // EV8_2
    i2c->I2C_CR1 |= I2C_STOP;

    return;
}

/** @brief Write data to an I2C slave device, uses I2C master start and stop */
int i2c_master_write(uint8_t *buf, uint16_t len, uint8_t slave_addr){
    i2c_master_start();
    struct i2c_reg_map *i2c = I2C1_BASE;
    uint8_t addr_byte = (slave_addr << 1) | I2C_WRITE_BIT;
    i2c->I2C_DR = addr_byte;

    while (!(i2c->I2C_SR1 & I2C_ADDR)); // EV6
    // clear ADDR
    (void) i2c->I2C_SR1;
    (void) i2c->I2C_SR2;

    while (!(i2c->I2C_SR1 & I2C_TxE)); // EV8_1

    for (uint16_t i=0; i<len; i++) {
        while (!(i2c->I2C_SR1 & I2C_TxE)); // EV8
        i2c->I2C_DR = buf[i];
    }

    i2c_master_stop();
    return 0;
}

int i2c_master_read(uint8_t *buf, uint16_t len, uint8_t slave_addr){
    (void) buf;
    (void) len;
    (void) slave_addr;

    return 0;
}
