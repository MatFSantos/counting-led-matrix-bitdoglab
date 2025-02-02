#include "rgb_led.h"

void init_rgb_led(){
    // inicialyze blue LED and turn off
    gpio_init(PIN_BLUE_LED);
    gpio_set_dir(PIN_BLUE_LED, GPIO_OUT);
    gpio_put(PIN_BLUE_LED, true);

    // inicialyze green LED and turn off
    gpio_init(PIN_GREEN_LED);
    gpio_set_dir(PIN_GREEN_LED, GPIO_OUT);
    gpio_put(PIN_GREEN_LED, true);

    // inicialyze red LED and turn off
    gpio_init(PIN_RED_LED);
    gpio_set_dir(PIN_RED_LED, GPIO_OUT);
    gpio_put(PIN_RED_LED, true);

}

void rgb_led_manipulate(bool red, bool green, bool blue){
    if(red)
        gpio_put(PIN_RED_LED, true);
    else
        gpio_put(PIN_RED_LED, false);

    if(green)
        gpio_put(PIN_GREEN_LED, true);
    else
        gpio_put(PIN_GREEN_LED, false);
    
    if(blue)
        gpio_put(PIN_BLUE_LED, true);
    else
        gpio_put(PIN_BLUE_LED, false);
}
