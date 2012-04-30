#include "decoder.h"
#include <avr/pgmspace.h>

#include "pulseproto.h"
#include "uart.h"


static prog_uint8_t translate_table[] = {
    0x7B, '0',
    0x30, '1',
    0x6D, '2',
    0x7C, '3',
    0x36, '4',
    0x5E, '5',
    0x5F, '6',
    0x38, '7',
    0x7F, '8',
    0x7E, '9',
    0x00, ' ',
    0x04, '-',
    0x54, 'a',
    0x45, 'c',
    0x75, 'd',
    0x03, 'l',
    0x33, 'M',
    0x0A, 'r'
};

static char decodeSegs(uint8_t segs)
{
    uint8_t i;
    for(i=0; i<sizeof(translate_table); i+=2)
    {
        if(segs == pgm_read_byte(translate_table+i))
            return pgm_read_byte(translate_table+i+1);
    }
#if DEBUG_UART 
    uartPut('(');
    uartPutHex(segs);
    uartPut(')');
#endif
    return '#';
}

char decodePosition(uint8_t idx)
{
    uint8_t segs;
    switch(idx)
    {
        case 0:
            segs = (recv_buf[4]&0xFC)>>2 | (recv_buf[5]&0x01)<<6;
            return decodeSegs(segs);
            break;
        case 1:
            segs = (recv_buf[3]&0xFC)>>2 | (recv_buf[4]&0x01)<<6;
            return decodeSegs(segs);
            break;
        case 2:
            segs = (recv_buf[2]&0xFC)>>2 | (recv_buf[3]&0x01)<<6;
            return decodeSegs(segs);
            break;
        case 3:
            segs = (recv_buf[1]&0xFC)>>2 | (recv_buf[2]&0x01)<<6;
            return decodeSegs(segs);
            break;
    }
    return '$';
}


uint8_t decodeDelimiter(void)
{
    uint8_t r = 0;
    if(recv_buf[5] & 0x04) r |= DELIM_CL;
    if(recv_buf[4] & 0x02) r |= DELIM_GR;
    if(recv_buf[1] & 0x02) r |= DELIM_DL;
    return r;
}


