#ifndef _PULSEPROTO_H_
#define _PULSEPROTO_H_

#include "global.h"
#include <avr/interrupt.h>

extern volatile uint8_t pack_done;

extern volatile uint8_t recv_buf[8];

void pulseInit(void);


#endif /* _PULSEPROTO_H_ */

