/**
 * @file adc.c
 *
 * @brief
 *
 * @date
 *
 * @author
 */

#include <gpio.h>
#include <stdint.h>
#include <rcc.h>
#include <unistd.h>
#include <adc.h>

/** @brief The ADC register map. */
struct adc_reg_map {
    volatile uint32_t SR;   /**< Status Register */
    volatile uint32_t CR1;   /**<  Control Register 1 */
    volatile uint32_t CR2;  /**<  Control Register 2 */
    volatile uint32_t SMPR1;  /**<  Sample Time Register 1 */
    volatile uint32_t SMPR2;  /**<  Sample Time Register 2 */
    volatile uint32_t JOFR1;  /**<  Injected Channel Data Offset Register 1*/
    volatile uint32_t JOFR2; /**<  Injected Channel Data Offset Register 2*/
	volatile uint32_t JOFR3;  /**<  Injected Channel Data Offset Register 3*/
    volatile uint32_t JOFR4; /**<  Injected Channel Data Offset Register 4*/
	volatile uint32_t HTR; /**<  Watchdog Higher Threshold Register*/
	volatile uint32_t LTR; /**<  Watchdog Lower Threshold Register*/
	volatile uint32_t SQR1; /**<  Regular Sequence Register 1*/
	volatile uint32_t SQR2; /**<  Regular Sequence Regiser 2*/
	volatile uint32_t SQR3; /**<  Regular Sequence Register 3*/
	volatile uint32_t JSQR; /**<  Injected Sequence Register*/
	volatile uint32_t JDR1; /**<  Injected Data Register 1*/
	volatile uint32_t JDR2; /**<  Injected Data Register 2*/
	volatile uint32_t JDR3; /**<  Injected Data Register 3*/
	volatile uint32_t JDR4; /**<  Injected Data Register 4*/
	volatile uint32_t DR; /**<  Regular Data Register */
	volatile uint32_t CCR; /**<   Common Control Register */
};

/** @brief Base address for ADC */
#define ADC_BASE  (struct adc_reg_map *) 0x40012000

/** @brief Resolution bits (bits 25:24) of CR1, 01 for 10 bit*/
#define RES (0b01 << 24)

/** @brief Analog watchdog enable of CR1 */
#define AWDEN (1 << 23)

/** @brief Start conversion bit of CR2 */
#define SWSTART (1 << 30)

/** @brief Enable ADON bit (bit 0) of CR2 */
#define ADON (1 << 0)

/** @brief Regular channel end of conversion bit of SR*/
#define EOC (1 << 1)

/** @brief Enable bit for ADC Clock */
#define RCC_EN (1 << 8)

/** @brief Channel selection*/
#define CHANNEL_SEL 0x1F

/** @brief Data mask for DR */
#define DATA 0b1111111111111111

void adc_init() {

	struct rcc_reg_map *rcc = RCC_BASE;
    rcc->apb2_enr |= RCC_EN;

	struct adc_reg_map *adc = ADC_BASE;
    adc->CR2 |= ADON;
    adc->CR1 |= RES;


	gpio_port gpio_portLS = GPIO_A;
    unsigned int numLS     = 5;
    unsigned int modeLS    = MODE_ANALOG_INPUT;
    unsigned int otypeLS   = OUTPUT_PUSH_PULL;
    unsigned int speedLS   = OUTPUT_SPEED_LOW;
    unsigned int pupdLS    = PUPD_NONE;
    unsigned int altLS     = 0;
    gpio_init(gpio_portLS, numLS, modeLS, otypeLS, speedLS, pupdLS, altLS);
	return;
}

uint16_t adc_read_chan(uint8_t chan){
    (void)chan;
	struct adc_reg_map *adc = ADC_BASE;
	adc->SQR3 &= (~CHANNEL_SEL);
	adc->SQR3 |= (chan & CHANNEL_SEL); //First conversion in regular sequence 

	adc->CR2 |= SWSTART;

	while ((adc->SR & EOC) == 0);
	return (uint16_t)adc->DR & DATA;
}
