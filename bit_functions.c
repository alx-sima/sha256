/* Copyright 2023 Alexandru Sima & Iarina-Ioana Popa */
#include "bit_functions.h"
#include <stdio.h>
#include <stdlib.h>

#define CHARSPERWORD sizeof(word) / sizeof(char)

void __swprint(char **dest, word wrd)
{
	char *str = calloc(33, sizeof(char));
	for (int i = 0; i < 32; ++i) {
		str[31 - i] = (wrd & 1) /*paritate*/ + '0';
		wrd >>= 1;
	}
	*dest = str;
}

// printeaza wrd in binar
void __wprint(word wrd)
{
	char *str;
	__swprint(&str, wrd);
	printf("%s\n", str);
	free(str);
}

// roteste la dreapta i biti din wrd
inline word rotr(word wrd, int i)
{
	word filtiulticif = ((1 << i) - 1);
	word ulticif = (wrd & filtiulticif) << (sizeof(word) * 8 - i);
	return ulticif | (wrd >> i);
}

inline word sigma0(word wrd)
{
	return rotr(wrd, 7) ^ rotr(wrd, 18) ^ (wrd >> 3);
}

inline word sigma1(word wrd)
{
	return rotr(wrd, 17) ^ rotr(wrd, 19) ^ (wrd >> 10);
}

inline word big_sigma0(word wrd)
{
	return rotr(wrd, 2) ^ rotr(wrd, 13) ^ rotr(wrd, 22);
}

inline word big_sigma1(word wrd)
{
	return rotr(wrd, 6) ^ rotr(wrd, 11) ^ rotr(wrd, 25);
}

inline word ch(word x, word y, word z) { return (x & y) ^ ((~x) & z); }

inline word maj(word x, word y, word z) { return (x & y) ^ (x & z) ^ (y & z); }
