/* Copyright 2023 Alexandru Sima & Iarina-Ioana Popa */
#ifndef BIT_FUNCTIONS_H_
#define BIT_FUNCTIONS_H_

typedef unsigned int word;

void __swprint(char **dest, word wrd);

void __wprint(word wrd);

inline word rotr(word wrd, int i);

inline word sigma0(word wrd);

inline word sigma1(word wrd);

inline word big_sigma0(word wrd);

inline word big_sigma1(word wrd);

inline word ch(word x, word y, word z);

inline word maj(word x, word y, word z);

#endif /* BIT_FUNCTIONS_H_ */
