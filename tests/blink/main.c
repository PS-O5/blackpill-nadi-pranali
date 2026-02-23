#include <stdint.h>

// Registers for GPIOA
#define RCC_AHB1ENR (*(volatile uint32_t*)0x40023830)
#define GPIOA_MODER (*(volatile uint32_t*)0x40020000)
#define GPIOA_ODR   (*(volatile uint32_t*)0x40020014)

void delay() {
    // Keeping the longer delay so it doesn't blink too fast to see
    for (volatile uint32_t i = 0; i < 2000000; i++) {
        __asm__ volatile ("nop"); 
    }
}

int main() {
    // 1. Enable GPIOA clock (Bit 0 for Port A) 
    RCC_AHB1ENR |= (1 << 0);

    // 2. Set PA5 as general purpose output 
    GPIOA_MODER &= ~(3U << (5 * 2));
    GPIOA_MODER |=  (1U << (5 * 2));

    while (1) {
        // 3. Toggle PA5 
        GPIOA_ODR ^= (1 << 5);  
        delay();
    }
    
    return 0;
}
