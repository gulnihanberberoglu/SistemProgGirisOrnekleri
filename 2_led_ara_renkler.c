#include <stdint.h>
#include <xdc/std.h>
#include "inc/tm4c123gh6pm.h"
#include <xdc/runtime/Log.h>

/* Board Header file */
#include "Board.h"

/**Bu fonksiyon portf’ye eriþip müdahale edebilmemiz için gerekli ayarlarý yapýyor.*/
void init_port_F() {
   volatile unsigned long tmp; // bu degisken gecikme yapmak icin gerekli
   tmp = SYSCTL_RCGCGPIO_R;     // allow time for clock to start
   SYSCTL_RCGCGPIO_R |= 0x00000020;  // 1) activate clock for Port F
   GPIO_PORTF_DIR_R = 0x0E;         // 5) PF4,PF0 giriþ , PF3-1 çýkýþ
   GPIO_PORTF_DEN_R = 0x1F;         // 7) portlarý aktifleþtir I/O on PF4-0
}


Int main(Void)
{
    volatile unsigned long delay;
    init_port_F();

    while(1){

        // kirmizi+yeþil = sarý ledi yak
        GPIO_PORTF_DATA_R |= 0b01010; // 0x02

        for (delay = 0; delay < 400000; delay++)
            /* bos dongu ile bekle */;

        // kirmizi+yeþil = sarý ledi sondur
        GPIO_PORTF_DATA_R &= ~0b01010;

        for (delay = 0; delay < 400000; delay++)
            /* bos dongu ile bekle */;

        // mavi+yeþil = siyan ledi yak
        GPIO_PORTF_DATA_R |= 0b01100; // 0x04

        for (delay = 0; delay < 400000; delay++)
            /* bos dongu ile bekle */;

        // mavi+yeþil = siyan ledi sondur
        GPIO_PORTF_DATA_R &= ~0b01100;

        for (delay = 0; delay < 400000; delay++)
            /* bos dongu ile bekle */;

        // kýrmýzý+mavi=majenta ledi yak
        GPIO_PORTF_DATA_R |= 0b00110; // 0x04

        for (delay = 0; delay < 400000; delay++)
            /* bos dongu ile bekle */;

        // kýrmýzý+mavi=majenta ledi sondur
        GPIO_PORTF_DATA_R &= ~0b00110;
        // beyaz ledi yak
         GPIO_PORTF_DATA_R |= 0b01110; // 0x04

         for (delay = 0; delay < 400000; delay++)
          /* bos dongu ile bekle */;
          // beyaz ledi sondur
          GPIO_PORTF_DATA_R &= ~0b01110;
    }

    return (0);
}
