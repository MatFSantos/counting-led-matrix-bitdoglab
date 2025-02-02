#include "modules/ws2812b.h"
#include "modules/push_button.h"
#include "modules/rgb_led.h"


#include "pico/stdlib.h"
#include "hardware/clocks.h"
#include <stdio.h>
#include "pico/bootrom.h"


int8_t count_idx = 0;
static volatile uint32_t last_time = 0;
_ws2812b * ws;
static bool is_whitin_range(volatile int8_t value) { return (value > 0 && value < 10 ? true : false); }

static void set_bounds(volatile int8_t *value) { *value = (*value < 0) ? 9 : 0; }

void init_gpio(){
    // inicia o LED RGB
    init_rgb_led();

    // inicia os botões A e B
    init_push_button(PIN_BUTTON_A);
    init_push_button(PIN_BUTTON_B);
}

void gpio_irq_handler(uint gpio, uint32_t event) {
    uint32_t current_time = to_ms_since_boot(get_absolute_time());
    if(current_time - last_time >= 200){
        count_idx = (gpio == PIN_BUTTON_A) ? count_idx + 1 : count_idx - 1;
        if (count_idx > 9) count_idx = 0;
        if (count_idx < 0) count_idx = 9;
        ws2812b_plot(ws,NUMERIC[count_idx]);
        last_time = current_time;
    }
}
int main(){
    PIO pio = pio0;
    bool ok;

    //coloca a frequência de clock para 128 MHz, facilitando a divisão pelo clock
    ok = set_sys_clock_khz(128000, false);
    printf("iniciando a transmissão PIO");
    if (ok) printf("clock set to %ld\n", clock_get_hz(clk_sys));

    stdio_init_all();
    
    ws = init_ws2812b(pio, PIN_WS2812B);

    init_gpio();

    gpio_set_irq_enabled_with_callback(PIN_BUTTON_A, GPIO_IRQ_EDGE_FALL, 1, &gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(PIN_BUTTON_B, GPIO_IRQ_EDGE_FALL, 1, &gpio_irq_handler);
    sleep_ms(50);
    ws2812b_plot(ws,NUMERIC[0]);

    while (1) {
        rgb_led_manipulate(true, false, false); // liga led vermelho
        sleep_ms(100);
        rgb_led_manipulate(false, false, false); // desliga todos os leds
        sleep_ms(100);
    }

    return 0;
}