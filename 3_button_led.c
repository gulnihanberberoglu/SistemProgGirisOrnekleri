#include <stdint.h>
#include <xdc/std.h>
#include "inc/tm4c123gh6pm.h"
#include <xdc/runtime/Log.h>

/* Board Header file */
#include "Board.h"

/**Bu fonksiyon portf’ye eriþip müdahale edebilmemiz için gerekli ayarlarý yapýyor.*/
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


Int main(Void)
{
    int button_sag, button_sol;
    init_port_F();
    while(1){
        // sagdaki button 0. bit, soldaki button 4. bit
        // button basiliyken 0, basili degilken 1 deðerini alýr.

        // sagdaki buttonun degerini oku, degiskene degerini ata
        button_sag = GPIO_PORTF_DATA_R & 0b00001;

        // soldaki buttonun degerini oku, degiskene degerini ata
        button_sol = GPIO_PORTF_DATA_R & 0b10000;
        if (button_sag == 0) {
                 // kirmizi ledi yak
                 GPIO_PORTF_DATA_R |= 0b00010; // 0x02
        }
        else {
            // button basili degilse, kirimzi ledi sondur
            GPIO_PORTF_DATA_R &= ~(0b00010);
        }

        if (button_sol == 0) { // button basili ise mavi ledi yak
            GPIO_PORTF_DATA_R |= 0b00100; // 0b01000
        }
        else {
            // button basili degilse mavi ledi sondur
            GPIO_PORTF_DATA_R &= ~(0b00100);
        }
    }
    return (0);
}
