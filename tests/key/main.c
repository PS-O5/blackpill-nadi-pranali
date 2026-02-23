#include <stdint.h>

// Registers for GPIOA
#define RCC_AHB1ENR (*(volatile uint32_t*)0x40023830)
#define GPIOA_MODER (*(volatile uint32_t*)0x40020000)
#define GPIOA_PUPDR (*(volatile uint32_t*)0x4002000C) // Pull-Up / Pull-Down Register
#define GPIOA_IDR   (*(volatile uint32_t*)0x40020010) // Input Data Register
#define GPIOA_ODR   (*(volatile uint32_t*)0x40020014) // Output Data Register

// A rough millisecond delay function
void delay_ms(uint32_t ms) {
    for (volatile uint32_t i = 0; i < (ms * 2000); i++) {
        __asm__ volatile ("nop"); 
    }
}

int main() {
    // 1. Enable GPIOA clock (Bit 0)
    RCC_AHB1ENR |= (1 << 0);

    // 2. Configure PA5 as general purpose output (LED)
    GPIOA_MODER &= ~(3U << (5 * 2));
    GPIOA_MODER |=  (1U << (5 * 2));

    // 3. Configure PA0 as input (Button)
    GPIOA_MODER &= ~(3U << (0 * 2)); // Setting both mode bits to 00 makes it an input

    // 4. Enable the Internal Pull-Up Resistor for PA0
    GPIOA_PUPDR &= ~(3U << (0 * 2)); // Clear the configuration bits
    GPIOA_PUPDR |=  (1U << (0 * 2)); // Set to 01 (Pull-Up)

    // Variable to track the button state. 
    // It defaults to 1 (HIGH) because of the pull-up resistor.
    uint8_t previous_button_state = 1; 

    while (1) {
        // Read the current state of PA0 from the Input Data Register (Bit 0)
        uint8_t current_button_state = (GPIOA_IDR & (1 << 0)) ? 1 : 0;

        // Check for a "Falling Edge" (button was unpressed, and is now pressed)
        if (previous_button_state == 1 && current_button_state == 0) {
            
            // Toggle the LED on PA5
            GPIOA_ODR ^= (1 << 5);  
            
            // Wait 50ms to ignore the mechanical bouncing of the button contacts
            delay_ms(50);
        }

        // Update the previous state for the next loop iteration
        previous_button_state = current_button_state;
    }
    
    return 0;
}
