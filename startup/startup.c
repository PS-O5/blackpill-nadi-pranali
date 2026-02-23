#include <stdint.h>

// These are pulled from your linker.ld
extern uint32_t _estack;
extern uint32_t _sidata, _sdata, _edata;
extern uint32_t _sbss, _ebss;

int main(void);

// Enable FPU (Coprocessor 10 and 11)
//SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));

void Reset_Handler(void) {
    // 1. Copy initialized data from FLASH to RAM
    uint32_t *data_rom = &_sidata;
    uint32_t *data_ram = &_sdata;
    while (data_ram < &_edata) {
        *data_ram++ = *data_rom++;
    }

    // 2. Zero out uninitialized data in RAM
    uint32_t *bss = &_sbss;
    while (bss < &_ebss) {
        *bss++ = 0;
    }

    // 3. Boot into main()
    main();
    
    // 4. If main ever exits, trap it here
    while (1);
}

// The Vector Table: The first thing the CPU looks at in memory
__attribute__((section(".isr_vector")))
uint32_t *isr_vector[] = {
    (uint32_t *)&_estack,      // Initial Stack Pointer
    (uint32_t *)Reset_Handler  // Boot execution address
};
