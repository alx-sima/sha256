/* Copyright 2023 Alexandru Sima & Iarina-Ioana Popa */

#include <stdio.h>
#include <stdlib.h>

#include "bit_functions.h"

word rotr(word wrd, int i)
{
	word mask = ((1 << i) - 1);
	word last_digit = (wrd & mask) << (sizeof(word) * 8 - i);
	return last_digit | (wrd >> i);
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
