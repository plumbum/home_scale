#include "pulseproto.h"

#include "uart.h"

volatile uint8_t pack_done;
volatile uint8_t recv_buf[8];
static uint8_t tmp_buf[8];
static uint8_t bitcnt;


SIGNAL(INT0_vect)
{
    if(PIND & (1<<PD2))
    {
        // Begin bit
        /* Start timer */
        TCNT0 = 0;
        TIMSK |= (1<<TOIE0);
        TCCR0B = (2<<CS00); // Start timer. prescaler 8
    }
    else
    {
        // End bit
        uint8_t bn = bitcnt>>3;
        if(TCNT0 > 30)
        {
            tmp_buf[bn] |= (1<<(bitcnt&0x07));
        }
        else
        {
            tmp_buf[bn] &= ~(1<<(bitcnt&0x07));
        }
        bitcnt++;
    }
}

SIGNAL(TIMER0_OVF_vect)
{
    /* Stop timer */
    TCCR0B = 0;
    TIMSK &= ~(1<<TOIE0);

    /* Copy buffer */
    uint8_t i;
    for(i=0; i<8; i++) recv_buf[i] = tmp_buf[i];
    pack_done = bitcnt;
    bitcnt = 0;
}

void pulseInit(void)
{
    bitcnt = 0;
    pack_done = 0;

    /* Any logical change on INT0 generates an interrupt request. */
    MCUCR = (MCUCR & 0xF0) | (1<<ISC00);
    GIMSK |= (1<<INT0);

    /* Timer 0 */
    TCCR0A = 0;
    TCCR0B = 0;
    // TIMSK |= (1<<TOIE0);
}

