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

void init_port_F() {
   volatile unsigned long tmp;       // bu degisken gecikme yapmak icin gerekli
   tmp = SYSCTL_RCGCGPIO_R;          // allow time for clock to start
   SYSCTL_RCGCGPIO_R |= 0x00000020;  // 1) activate clock for Port F
   GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock GPIO Port F
   GPIO_PORTF_CR_R = 0x01;           // allow changes to PF-0
   GPIO_PORTF_DIR_R = 0x0E;          // 5) PF4,PF0 giriþ , PF3-1 çýkýþ
   GPIO_PORTF_PUR_R = 0x11;          // PF0 and PF4 üzerinden button deðerlerini okumak için aktifleþtiriyor
   GPIO_PORTF_DEN_R = 0x1F;          // 7) portlarý aktifleþtir I/O on PF4-0
}

void yan_sön1()
{
    volatile unsigned long delay;
    GPIO_PORTD_DATA_R |=  0b0010;//D1 portundaki ledi yak
    GPIO_PORTD_DATA_R &= ~0b0001;//D0 portundaki ledi kapa
    for (delay = 0 ; delay < 400000 ; delay++)    /* bos dongu */;
    GPIO_PORTD_DATA_R |=  0b0001;//D0 portundaki ledi yak
    GPIO_PORTD_DATA_R &= ~0b0010;//D1 portundaki ledi kapat
    for (delay = 0 ; delay < 400000 ; delay++)    /* bos dongu */;
}

void yan_sön2()
{
    volatile unsigned long delay;
    GPIO_PORTD_DATA_R |=  0b0100;//D2 portundaki ledi yak
    GPIO_PORTD_DATA_R &= ~0b1000;//D3 portundaki ledi kapa
    for (delay = 0 ; delay < 400000 ; delay++)    /* bos dongu */;
    GPIO_PORTD_DATA_R |=  0b1000;//D3 portundaki ledi yak
    GPIO_PORTD_DATA_R &= ~0b0100;//D2 portundaki ledi kapat
    for (delay = 0 ; delay < 400000 ; delay++)    /* bos dongu */;

}

Int main(Void)
{
    init_port_D();
    init_port_F();

    int button_sag, button_sol;

    while (1)
    {
        button_sag = GPIO_PORTF_DATA_R & 0b00001;
        button_sol = GPIO_PORTF_DATA_R & 0b10000;

        if (button_sag == 0)
        {
            yan_sön1();
        }
        if (button_sol == 0)
        {
            yan_sön2();
        }
    }
    return (0);
}
