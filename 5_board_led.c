#include <stdint.h>
#include <xdc/std.h>
#include "inc/tm4c123gh6pm.h"
#include <xdc/runtime/Log.h>

/* Board Header file */
#include "Board.h"

void init_port_D() {
    volatile unsigned long delay;
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOD;
    delay = SYSCTL_RCGC2_R;
    GPIO_PORTD_DIR_R |= 0x0F;
    GPIO_PORTD_AFSEL_R &= ~0x0F;
    GPIO_PORTD_DEN_R |= 0x0F;
}

Int main(Void)
{
    volatile unsigned long delay;
    init_port_D();
    while (1) {
        GPIO_PORTD_DATA_R |= 0b0010;//D1 portundaki ledi yak
        GPIO_PORTD_DATA_R &= ~0b0001;//D0 portundaki ledi kapa
        for (delay = 0 ; delay < 400000 ; delay++)    /* bos dongu */;
        GPIO_PORTD_DATA_R |= 0b0001;//D0 portundaki ledi kapa
        GPIO_PORTD_DATA_R &= ~0b0010;//D1 portundaki ledi yak
        for (delay = 0 ; delay < 400000 ; delay++)    /* bos dongu */;
    }
    return (0);
}
