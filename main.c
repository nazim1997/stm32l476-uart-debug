#include <stdint.h>
#include <stdbool.h>

#define RCC_AHB1_BASE 0x40021000
#define RCC_AHB2_ENR (RCC_AHB1_BASE + 0x4C)
#define RCC_APB1ENR1 (RCC_AHB1_BASE + 0x58)

#define AHB2_GPIOA 0x48000000
#define GPIOA_MODER (AHB2_GPIOA)
#define GPIOA_ODR (AHB2_GPIOA + 0x14)
#define GPIOA_AFRL (AHB2_GPIOA + 0x20)

#define APB1_USART2 0x40004400 
#define USART_CR1 (APB1_USART2)
#define USART_BRR (APB1_USART2 + 0x0C)
#define USART_ISR (APB1_USART2 + 0x1C)
#define USART_TDR (APB1_USART2 + 0x28)


void gpio_init() {
    // Enable clock of GPIOA
    *(volatile uint32_t*) RCC_AHB2_ENR  |= 0x1;

    // Enable Alternate function for PA2
    *(volatile uint32_t*) GPIOA_MODER &= ~(0x3 << 4);
    *(volatile uint32_t*) GPIOA_MODER |= (0x2 << 4);

    // Enable Alternate function for PA3
    *(volatile uint32_t*) GPIOA_MODER &= ~(0x3 << 6);
    *(volatile uint32_t*) GPIOA_MODER |= (0x2 << 6);

    // Establish connection between PA2 and USART2_TX
    *(volatile uint32_t*) GPIOA_AFRL &= ~(0xF << 8);
    *(volatile uint32_t*) GPIOA_AFRL |= (0x7 << 8); 

    // Establish connection between PA3 and USART2_RX
    *(volatile uint32_t*) GPIOA_AFRL &= ~(0xF << 12);
    *(volatile uint32_t*) GPIOA_AFRL |= (0x7 << 12);
}

void usart2_init() {
    // Enable clock of USART2 
    *(volatile uint32_t*) RCC_APB1ENR1 |= (0x1 << 17);

    // Enable Transmitter
    *(volatile uint32_t*) USART_CR1 |= (0x1 << 3);

    // Set UE bit to 0
    *(volatile uint32_t*) USART_CR1 &= ~(0x1);

    // Set Baud Rate
    *(volatile uint32_t*) USART_BRR = 0x23;

    // Enable USART
    *(volatile uint32_t*) USART_CR1 |= 0x1;

}

uint32_t print(char* text) {
    uint32_t length = 0;
    for (char* c = text; *c != '\0'; c++) {
        while (!((*(volatile uint32_t*) USART_ISR) & (0x1 << 7))); // wait while bit is not 1
        *(volatile uint32_t*) USART_TDR = *c;
        length++;
    }
    return length;
}

int main() {
    gpio_init();

    usart2_init();
 
    while(true) {
        print("Hello\r\n");
    }
}
