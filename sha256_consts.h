/* Copyright 2023 Alexandru Sima & Iarina-Ioana Popa */

#ifndef SHA256_CONSTS_H_
#define SHA256_CONSTS_H_

#include <stdint.h>

typedef uint32_t word;

#define CHUNK (512 / 8)
#define WORDNO 64

#define RESWORDS 8

extern const word wconsts[WORDNO];
extern const word initwrd[RESWORDS];

#endif /* SHA256_CONSTS_H_ */