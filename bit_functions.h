/* Copyright (C) 2023 Alexandru Sima & Iarina-Ioana Popa (312CA) */

#ifndef BIT_FUNCTIONS_H_
#define BIT_FUNCTIONS_H_

#include "sha256_consts.h"

word rotr(word wrd, int i);

word sigma0(word wrd);

word sigma1(word wrd);

word big_sigma0(word wrd);

word big_sigma1(word wrd);

word ch(word x, word y, word z);

word maj(word x, word y, word z);

#endif /* BIT_FUNCTIONS_H_ */
