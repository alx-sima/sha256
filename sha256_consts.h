/* Copyright (C) 2023 Alexandru Sima & Iarina-Ioana Popa (312CA) */

#ifndef SHA256_CONSTS_H_
#define SHA256_CONSTS_H_

#include <stdint.h>

/** Dimensiunea unitatilor cu care se lucreaza. */
typedef uint32_t word;

#define CHUNK (512 / 8)
#define NUM_WORDS 64

#define NUM_REGS 8

/** Constantele folosite pentru fiecare runda de hashing. */
extern const word wconsts[NUM_WORDS];

/** Valoarea initiala a hashului. */
extern const word initwrd[NUM_REGS];

#endif /* SHA256_CONSTS_H_ */
