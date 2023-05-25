/* Copyright (C) 2023 Alexandru Sima & Iarina-Ioana Popa (312CA) */

#ifndef UTILS_H_
#define UTILS_H_

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

/** Macro de assert care intrerupe programul in caz de eroare. */
#define DIE(assertion, call_description)                                       \
	do {                                                                       \
		if (assertion) {                                                       \
			fprintf(stderr, "(%s, %d): ", __FILE__, __LINE__);                 \
			perror(call_description);                                          \
			exit(errno);                                                       \
		}                                                                      \
	} while (0)

#endif /* UTILS_H_ */
