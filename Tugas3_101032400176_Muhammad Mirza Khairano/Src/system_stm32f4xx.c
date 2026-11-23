#include "stm32f4xx.h"

void SystemInit(void) {
    // Aktifkan FPU dan biarkan sistem berjalan pada clock default HSI 16 MHz
    *(volatile uint32_t *)0xE000ED88UL |= (0xFUL << 20);
}
