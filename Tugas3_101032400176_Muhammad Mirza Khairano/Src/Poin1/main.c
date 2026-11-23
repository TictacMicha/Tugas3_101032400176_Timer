#include "stm32f4xx.h"

void GPIO_Init(void) {
    RCC->AHB1ENR |= (1U << 0);

    GPIOA->MODER &= ~((3U << 10) | (3U << 12) | (3U << 14));
    GPIOA->MODER |=  ((1U << 10) | (1U << 12) | (1U << 14));
}

void Timers_Init(void) {
    RCC->APB1ENR |= (1U << 0) | (1U << 1) | (1U << 2);

    TIM2->PSC = 15999;
    TIM2->ARR = 499;
    TIM2->DIER |= (1U << 0);
    NVIC_EnableIRQ(TIM2_IRQn);

    TIM3->PSC = 15999;
    TIM3->ARR = 249;
    TIM3->DIER |= (1U << 0);
    NVIC_EnableIRQ(TIM3_IRQn);

    TIM4->PSC = 15999;
    TIM4->ARR = 99;
    TIM4->DIER |= (1U << 0);
    NVIC_EnableIRQ(TIM4_IRQn);

    TIM2->CR1 |= (1U << 0);
    TIM3->CR1 |= (1U << 0);
    TIM4->CR1 |= (1U << 0);
}

void TIM2_IRQHandler(void) {
    if (TIM2->SR & (1U << 0)) {
        TIM2->SR &= ~(1U << 0);
        GPIOA->ODR ^= (1U << 5);
    }
}

void TIM3_IRQHandler(void) {
    if (TIM3->SR & (1U << 0)) {
        TIM3->SR &= ~(1U << 0);
        GPIOA->ODR ^= (1U << 6);
    }
}

void TIM4_IRQHandler(void) {
    if (TIM4->SR & (1U << 0)) {
        TIM4->SR &= ~(1U << 0);
        GPIOA->ODR ^= (1U << 7);
    }
}

int main(void) {
    GPIO_Init();
    Timers_Init();

    while (1) {
    }
}
