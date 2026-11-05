#include "stdint.h"

// Start Address For the Initialization Values of the .data Section.
extern uint32_t _sidata;
// Start Address For the .data Section.
extern uint32_t _sdata;
// End Address For the .data Section.
extern uint32_t _edata;
// Start Address For the .bss Section.
extern uint32_t _sbss;
// End Address for the .bss Section.
extern uint32_t _ebss;
// End of Stack.
extern uint32_t _estack;

extern int main();

// Reset Handler
void Reset_Handler() {
    // Initialize data Segment
    uint32_t* dataInit = &_sidata;
    uint32_t* data = &_sdata;
    while(data < &_edata) *data++ = *dataInit++;

    // Initialize bss Segment.
    uint32_t *bss = &_sbss;
    while (bss < &_ebss) *bss++ = 0;

    main();
    // Handle Case Where Main Function Returns.
    while(1);
}

// Interrupt Vector Table
__attribute__((section(".isr_vector")))
const void(*VectorTable[])(void) = {
    (const void(*)(void))&_estack,
    Reset_Handler
};
