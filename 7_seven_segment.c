#include <stdint.h>
#include <xdc/std.h>
#include "inc/tm4c123gh6pm.h"
#include <xdc/runtime/Log.h>

/* Board Header file */
#include "Board.h"

void init_port_B() {
        volatile unsigned long delay;
// Port B’nin saati aktifleþtir
        SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOB;
// Gecikme
        delay = SYSCTL_RCGC2_R;
// Port B’nin tüm bitleri cikis olarak ayarla
        GPIO_PORTB_DIR_R |= 0xFF;
// Alternatif fonksiyonlar kapat
        GPIO_PORTB_AFSEL_R &= ~0xFF;
// Tüm Port B için Digital çalýþmayý aktifleþtir
        GPIO_PORTB_DEN_R |= 0xFF;
}

Int main(Void)
{
    init_port_B();
    uint8_t kodlar[10] = {
        ~0b0111111,
        ~0b0000110,
        ~0b1011011,
        ~0b1001111,
        ~0b1100110,
        ~0b1101101,
        ~0b1111101,
        ~0b0000111,
        ~0b1111111,
        ~0b1101111
    };
    volatile unsigned long delay;
    int sayi = 0;
        while (1) {
         GPIO_PORTB_DATA_R = kodlar[sayi];
         for (delay = 0 ; delay < 1000000 ; delay++)
             /* */;
         sayi = (sayi + 1) % 10;
        }

    return (0);
}
