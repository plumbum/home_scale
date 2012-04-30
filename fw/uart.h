/*
 * =====================================================================================
 * 
 *       Filename:  uart.h
 * 
 *    Description:  UART routines
 * 
 *        Version:  1.0
 *        Created:  03.11.2007 16:35:24 MSK
 *       Revision:  none
 *       Compiler:  gcc
 * 
 *         Author:  Ivan Alfiorov-Romamentiev (http://iar.spb.ru), ivalrom@gmail.com
 *        Company:  Freelancer
 * 
 * =====================================================================================
 */

#ifndef  UART_FILE_HEADER_INC
#define  UART_FILE_HEADER_INC

#include "global.h"
#include <avr/pgmspace.h>

// UART constant
#define UARTN(x) (uint16_t)((F_CPU)/((x)*16l)-1)

#define UART1200 UARTN(1200)
#define UART2400 UARTN(2400)
#define UART4800 UARTN(4800)
#define UART9600 UARTN(9600)
#define UART19200 UARTN(19200)
#define UART38400 UARTN(38400)
#define UART57600 UARTN(57600)
#define UART115200 UARTN(115200)
#define UART230400 UARTN(230400)
#define UART460800 UARTN(460800)


// Functions
#define uartSTATE ( UCSRA & (1<<RXC) )

void uartInit(uint16_t baud);

uint8_t uartGet(void);

void uartPut(uint8_t data);
void uartPuts_p(prog_char* s);
void uartPuts(char* s);

void uartPutHex(uint8_t v);


#define uartTxComplete() while ( !( UCSRA & (1<<TXC)) )

#define uart16(u16) { uartPut((u16) & 0xFF); uartPut(((u16) & 0xFF00) >> 8); }
#define uart32(u32) { uartPut((u32) & 0xFF); uartPut(((u32) & 0xFF00) >> 8); \
                      uartPut(((u32) & 0xFF0000) >> 16); uartPut(((u32) & 0xFF000000) >> 24); }

#endif   /* ----- #ifndef UART_FILE_HEADER_INC  ----- */

