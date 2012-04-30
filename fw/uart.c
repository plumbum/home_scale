/*
 * =====================================================================================
 *
 *       Filename:  uart.c
 *
 *    Description:  UART routines
 *
 *        Version:  1.0
 *        Created:  03.11.2007 16:30:06 MSK
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ivan Alfiorov-Romamentiev (http://iar.spb.ru), ivalrom@gmail.com
 *        Company:  Freelancer
 *
 * =====================================================================================
 */

#include "uart.h"


void uartInit(uint16_t baud)
{
    /* Set baud rate */
    UBRRH = (unsigned char)(baud>>8);
    UBRRL = (unsigned char)baud;
    /* Enable receiver and transmit */
    UCSRB = (1<<RXEN) | (1<<TXEN);
    /* Set frame format: 8data, 2stopbit */
    UCSRC = (1<<USBS) | (3<<UCSZ0);
}

uint8_t uartGet(void)
{
    /* Wait for data to be received */
    while ( !(UCSRA & (1<<RXC)) )
       ;
    /* Get and return received data from buffer */
    return UDR;
}


void uartPut(uint8_t data)
{
    /* Wait for empty transmit buffer */
    while ( !( UCSRA & (1<<UDRE)) )
         ;
    /* Put data into buffer, sends the data */
    UDR = data;
}

void uartPuts_p(prog_char* s)
{
    uint8_t c;
    while((c = pgm_read_byte(s++)) != 0)
    {
        uartPut(c);
    }
}

void uartPuts(char* s)
{
    char c;
    while((c = *s++) != 0)
    {
        uartPut(c);
    }
}

static inline char _hex(uint8_t v)
{
    if(v<10)
        return v + '0';
    return v + 'A'-10;
}

void uartPutHex(uint8_t v)
{
    uartPut(_hex(v>>4));
    uartPut(_hex(v&0x0F));
}

