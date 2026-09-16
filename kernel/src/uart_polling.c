#include <unistd.h>

#include <gpio.h>
#include <rcc.h>
#include <uart_polling.h>

/** @brief The UART register map. */
struct uart_reg_map {
    volatile uint32_t SR;   /**< Status Register */
    volatile uint32_t DR;   /**<  Data Register */
    volatile uint32_t BRR;  /**<  Baud Rate Register */
    volatile uint32_t CR1;  /**<  Control Register 1 */
    volatile uint32_t CR2;  /**<  Control Register 2 */
    volatile uint32_t CR3;  /**<  Control Register 3 */
    volatile uint32_t GTPR; /**<  Guard Time and Prescaler Register */
};

/** @brief Base address for UART2 */
#define UART2_BASE  (struct uart_reg_map *) 0x40004400

/** @brief Enable bit for UART Config register */
#define UART_EN (1 << 13)

/** @brief Enable bit for UART Clock */
#define RCC_EN (1 << 17)

/** @brief Transmitter enable */
#define TRANSMITTER_EN (1 << 2)

/** @brief Receiver enable */
#define RECEIVER_EN (1 << 3)

/** @brief Transmit data register empty bit of CR */
#define UART_SR_TXE (1 << 7)

/** @brief Read data register not empty bit of CR */
#define UART_SR_RXNE (1 << 5)

/**
 * @brief initializes UART to given baud rate with 8-bit word length, 1 stop bit, 0 parity bits
 *
 * @param baud Baud rate
 */
void uart_polling_init (int baud){
    (void) baud; /* This line is simply here to suppress the Unused Variable Error. */
                 /* You should remove this line in your final implementation */
    struct rcc_reg_map *rcc = RCC_BASE;
    rcc->apb1_enr |= RCC_EN;
    
    
    struct uart_reg_map *uart = UART2_BASE;
    uart->CR1 |= UART_EN;
    uart->CR1 |= TRANSMITTER_EN;
    uart->CR1 |= RECEIVER_EN;
    uart->BRR |= baud;

    gpio_port gpio_portTX = GPIO_A;
    unsigned int numTX    = 2;
    unsigned int modeTX   = MODE_ALT;
    unsigned int otypeTX  = OUTPUT_PUSH_PULL;
    unsigned int speedTX  = OUTPUT_SPEED_LOW;
    unsigned int pupdTX   = PUPD_NONE;
    unsigned int altTX    = ALT7;  
    gpio_init(gpio_portTX, numTX, modeTX, otypeTX, speedTX, pupdTX, altTX);

    gpio_port gpio_portRX = GPIO_A;
    unsigned int numRX    = 3;
    unsigned int modeRX   = MODE_ALT;
    unsigned int otypeRX  = OUTPUT_OPEN_DRAIN;
    unsigned int speedRX  = OUTPUT_SPEED_LOW;
    unsigned int pupdRX   = PUPD_NONE;
    unsigned int altRX    = ALT7;
    gpio_init(gpio_portRX, numRX, modeRX, otypeRX, speedRX, pupdRX, altRX);

    return;
}

/**
 * @brief transmits a byte over UART
 *
 * @param c character to be sent
 */
void uart_polling_put_byte (char c){
    (void) c;

    struct uart_reg_map *uart = UART2_BASE;
    while ((uart->SR & UART_SR_TXE) == 0);
    uart->DR = c;
    return;
}

/**
 * @brief receives a byte over UART
 */
char uart_polling_get_byte () {
    struct uart_reg_map *uart = UART2_BASE;
    while ((uart->SR & UART_SR_RXNE) == 0);
    return uart->DR;
}
