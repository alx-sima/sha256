/* Copyright (C) 2023 Alexandru Sima & Iarina-Ioana Popa (312CA) */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bit_functions.h"
#include "io.h"
#include "sha.h"
#include "sha256_consts.h"
#include "utils.h"

/**
 * @brief Pregateste stringul pentru hashing, adaugand padding un bit de 1 si
 * restul 0, apoi lungimea stringului original, pana obtinerea unui string cu
 * lungime un multiplu de 512.
 *
 * @param dest		locatia stringului procesat
 * @param str 		stringul de procesat
 * @return size_t	lungimea stringului prelucrat
 */
static size_t pre_process(unsigned char **dest, char *str);

/**
 * @brief Genereaza primele 16 worduri dintr-un bloc de 512 biti.
 *
 * @param block blocul de 512 biti
 * @return word vectorul de worduri
 */
static word *split_block_to_words(unsigned char *block);

/**
 * @brief Genereaza ultimele 48 de worduri, aplicand operatii sigma pe worduri
 * generate anterior.
 *
 * @param words vectorul de worduri
 */
static void gen_words(word *words);

void sha_file(char *filename)
{
	char *content = read_file_contents(filename);
	if (!content)
		return;

	unsigned char *message;
	int processed_size = pre_process(&message, content);

	/* Initializeaza digestul mesajului.
	 * (variabilele h0...h7) */
	word digest[NUM_REGS];
	memcpy(digest, initwrd, NUM_REGS * sizeof(word));

	for (int i = 0; i < processed_size; i += CHUNK) {
		/* Genereaza primele 16 worduri din blocul de 512 biti. */
		word *wrd = split_block_to_words(&message[i]);
		/* Completeaza cu restul de 48 de worduri, folosindu-le
		 * pe cele generate anterior. */
		gen_words(wrd);

		/* Initializeaza registrele de lucru.
		 * (variabilele a...h) */
		word work_regs[NUM_REGS];
		memcpy(work_regs, digest, NUM_REGS * sizeof(word));

		for (int k = 0; k < NUM_WORDS; ++k) {
			/* SIGMA1(e) + ch(e, f, g) + h + K(i) + W(i); */
			word t1 = big_sigma1(work_regs[4]) +
					  ch(work_regs[4], work_regs[5], work_regs[6]) +
					  work_regs[7] + wconsts[k] + wrd[k];

			/* SIGMA0(a) + maj(a, b, c); */
			word t2 = big_sigma0(work_regs[0]) +
					  maj(work_regs[0], work_regs[1], work_regs[2]);

			for (int l = 7; l > 0; --l)
				work_regs[l] = work_regs[l - 1];

			work_regs[0] = t1 + t2; /* a = T1 + T2; */
			work_regs[4] += t1;		/* e =  e + T1; */
		}

		/* Adauga registrele la digest. */
		for (int k = 0; k < NUM_REGS; ++k)
			digest[k] += work_regs[k];

		free(wrd);
	}

	/* SHA-ul final este obtinut prin concatenarea digestului. */
	for (int k = 0; k < NUM_REGS; ++k)
		printf("%08x", digest[k]);

	printf("  %s\n", filename);

	free(content);
	free(message);
}

static size_t pre_process(unsigned char **dest, char *str)
{
	/* Numarul de octeti cu care se face padding. */
	const int padd_size = 1 + CHUNK / __CHAR_BIT__;
	size_t initial_length = strlen(str);

	size_t str_size = initial_length + padd_size;

	/* Stringul se va completa pana la un multiplu de 512 biti. */
	if (str_size % CHUNK)
		str_size += CHUNK - (str_size % CHUNK);

	*dest = calloc(str_size, sizeof(unsigned char));
	DIE(!*dest, "failed malloc() of processed string");

	memcpy(dest, str, initial_length);
	/* Adauga la finalul stringului un bit de 1. */
	(*dest)[initial_length] = 0x80;

	/* Adauga lungimea initiala a stringului octet cu octet la final
	 * in format big-endian (invers fata de cum e stocat). */
	size_t bit_len = initial_length * __CHAR_BIT__;
	for (int i = 0; bit_len; ++i) {
		(*dest)[str_size - i - 1] = (unsigned char)(bit_len & 0xff);
		bit_len >>= __CHAR_BIT__;
	}

	return str_size;
}

static word *split_block_to_words(unsigned char *block)
{
	word *words = calloc(NUM_WORDS, sizeof(word));
	DIE(!words, "failed malloc() of words array");

	for (int i = 0; i < 16; ++i) {
		for (size_t j = 0; j < sizeof(word); ++j) {
			words[i] <<= sizeof(char) * __CHAR_BIT__;
			words[i] |= block[sizeof(word) * i + j];
		}
	}

	return words;
}

static void gen_words(word *words)
{
	for (int i = 16; i < NUM_WORDS; ++i) {
		words[i] = sigma1(words[i - 2]) + words[i - 7] + sigma0(words[i - 15]) +
				   words[i - 16];
	}
}
