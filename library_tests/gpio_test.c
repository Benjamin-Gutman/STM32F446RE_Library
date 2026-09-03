#include "gpio.h"

int main(void)
{
    // Configure PA5 as output
    gpio_enable_clock(GPIOA);
    gpio_set_mode(GPIOA, 5, GPIO_OUTPUT);

    while (1)
    {
        gpio_toggle(GPIOA, 5);

        // Temporary delay
        for (volatile uint32_t i = 0; i < 1000000; i++);
    }
}
