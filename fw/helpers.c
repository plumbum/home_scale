#include "helpers.h"

#include "global.h"
#include <util/delay.h>

#include <stdio.h>

void delay_ms(unsigned int ms)
/* delay for a minimum of <ms> */
{
        // we use a calibrated macro. This is more
        // accurate and not so much compiler dependent
        // as self made code.
        while(ms){
                _delay_ms(0.96);
                ms--;
                wdr();
        }
}

