#include <stdint.h>
#include <xdc/std.h>
#include "inc/tm4c123gh6pm.h"
#include <xdc/runtime/Log.h>

/* Board Header file */
#include "Board.h"

/**Bu fonksiyon portf�ye eri�ip m�dahale edebilmemiz i�in gerekli ayarlar� yap�yor.*/
void init_port_F() {
   volatile unsigned long tmp; // bu degisken gecikme yapmak icin gerekli
   tmp = SYSCTL_RCGCGPIO_R;     // allow time for clock to start
   SYSCTL_RCGCGPIO_R |= 0x00000020;  // 1) activate clock for Port F
   GPIO_PORTF_DIR_R = 0x0E;         // 5) PF4,PF0 giri� , PF3-1 ��k��
   GPIO_PORTF_DEN_R = 0x1F;         // 7) portlar� aktifle�tir I/O on PF4-0
}


Int main(Void)
{
    volatile unsigned long delay;
    init_port_F();

    while(1){

        // kirmizi ledi yak
        GPIO_PORTF_DATA_R |= 0b00010; // 0x02

        for (delay = 0; delay < 400000; delay++)
            /* bos dongu ile bekle */;

        // kirmizi ledi sondur
        GPIO_PORTF_DATA_R &= ~0b00010;

        for (delay = 0; delay < 400000; delay++)
            /* bos dongu ile bekle */;

        // mavi ledi yak
        GPIO_PORTF_DATA_R |= 0b00100; // 0x04

        for (delay = 0; delay < 400000; delay++)
            /* bos dongu ile bekle */;

        // mavi ledi sondur
        GPIO_PORTF_DATA_R &= ~0b00100;

        for (delay = 0; delay < 400000; delay++)
            /* bos dongu ile bekle */;

        // ye�il ledi yak
        GPIO_PORTF_DATA_R |= 0b01000; // 0x04

        for (delay = 0; delay < 400000; delay++)
            /* bos dongu ile bekle */;

        // ye�il ledi sondur
        GPIO_PORTF_DATA_R &= ~0b01000;
    }

    return (0);
}
