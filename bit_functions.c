/* Copyright 2023 Alexandru Sima & Iarina-Ioana Popa */

#include <stdio.h>
#include <stdlib.h>

#include "bit_functions.h"

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
word rotr(word wrd, int i)
{
	word filtiulticif = ((1 << i) - 1);
	word ulticif = (wrd & filtiulticif) << (sizeof(word) * 8 - i);
	return ulticif | (wrd >> i);
}

word sigma0(word wrd)
{
	return rotr(wrd, 7) ^ rotr(wrd, 18) ^ (wrd >> 3);
}

word sigma1(word wrd)
{
	return rotr(wrd, 17) ^ rotr(wrd, 19) ^ (wrd >> 10);
}

word big_sigma0(word wrd)
{
	return rotr(wrd, 2) ^ rotr(wrd, 13) ^ rotr(wrd, 22);
}

word big_sigma1(word wrd)
{
	return rotr(wrd, 6) ^ rotr(wrd, 11) ^ rotr(wrd, 25);
}

word ch(word x, word y, word z)
{
	return (x & y) ^ ((~x) & z);
}

word maj(word x, word y, word z)
{
	return (x & y) ^ (x & z) ^ (y & z);
}
