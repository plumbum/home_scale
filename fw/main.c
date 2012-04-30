/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  Thermostat
 *
 *        Version:  1.0
 *        Created:  Fri Mar 14 17:43:49 MSK 2008
 *       Revision:  $Id$
 *       Compiler:  gcc
 *
 *         Author:  Ivan Alfiorov-Romamentiev (http://iar.spb.ru), ivalrom@gmail.com
 *        Company:  Freelancer
 *
 * =====================================================================================
 */

#include "global.h"

#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <string.h>

#include "helpers.h"
#include "uart.h"
#include "pulseproto.h"
#include "decoder.h"

int main(void)
{
#ifdef WDTON
    wdt_enable(WDTO_15MS);
#endif

    PORTB  = 0xFC; // PB0 - debug pulse
    DDRB   = 0x01;

    PORTD  = 0xFF;
    DDRD   = (1<<1); // PD1 - TXD

    ACSR |= (1<<ACD); // Disable comparator

    uartInit(UART9600);

    pulseInit();

    sei();

    uint8_t i;
    while(1)
    {
        pack_done = 0;
        wdr();
        /* Go IDLE mode */
        set_sleep_mode(SLEEP_MODE_STANDBY);
        cli();
        if (1)
        {
            sleep_enable();
            sei();
            sleep_cpu();
            sleep_disable();
        }
        sei();

        MCUCR |= (1<<PUD);
        PORTB |= 1;
        /* Wait packet */
        while(pack_done == 0) wdr();
        i = 5;
        do
        {
            uartPutHex(recv_buf[i]);
        } while(i--);
        uartPut(':');
        uint8_t dlm = decodeDelimiter();
        uartPut(decodePosition(3));
        uartPut(decodePosition(2));
        uartPut(decodePosition(1));
        uartPut(decodePosition(0));
        uartPut(' ');
        if(dlm & DELIM_GR) { uartPut('g'); }
        if(dlm & DELIM_CL) { uartPut('c'); uartPut('l'); }
        if(dlm & DELIM_DL) { uartPut('d'); uartPut('l'); }
        uartPut('\r');
        uartPut('\n');
        uartTxComplete();
        _delay_ms(1);
        PORTB &= ~1;
        MCUCR &= ~(1<<PUD);
    }
}

// vim: sw=4:ts=4:si:et
