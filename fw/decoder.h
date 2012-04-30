#ifndef _DECODER_H_
#define _DECODER_H_

#include "global.h"

char decodePosition(uint8_t idx);

#define DELIM_GR    1
#define DELIM_CL    2
#define DELIM_DL    4
#define DELIM_PNT   8

uint8_t decodeDelimiter(void);

#endif

