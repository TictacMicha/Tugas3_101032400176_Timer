#include "stm32f4xx.h"

void init_hardware(void) {
    RCC->AHB1ENR |= (1 << 0);
    RCC->APB1ENR |= (1 << 1);

    GPIOA->MODER &= ~(3 << 2);
    GPIOA->MODER |= (1 << 2);

    GPIOA->MODER &= ~(3 << 8);
    GPIOA->PUPDR &= ~(3 << 8);
    GPIOA->PUPDR |= (1 << 8);

    GPIOA->ODR &= ~(1 << 1);

    TIM3->PSC = 15999;
    TIM3->ARR = 99;
    TIM3->DIER |= (1 << 0);
    NVIC_EnableIRQ(TIM3_IRQn);
}

void TIM3_IRQHandler(void) {
    if (TIM3->SR & (1 << 0)) {
        TIM3->SR &= ~(1 << 0);
        GPIOA->ODR ^= (1 << 1);
    }
}

int main(void) {
    init_hardware();

    while (1) {
        if ((GPIOA->IDR & (1 << 4)) == 0) {
            TIM3->CR1 |= (1 << 0);
        } else {
            TIM3->CR1 &= ~(1 << 0);
            TIM3->CNT = 0;
            GPIOA->ODR &= ~(1 << 1);
        }
    }
}
