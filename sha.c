/* Copyright 2023 Alexandru Sima & Iarina-Ioana Popa */

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
size_t pre_process(unsigned char **dest, char *str)
{
	const int padd_size = 1 + CHUNK / 8;
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

	size_t len = initial_length * 8;
	for (int i = 0; len; ++i) {
		(*dest)[str_size - i - 1] = (unsigned char)(len & 0xff);
		len >>= 8;
	}

	return str_size;
}

/**
 * @brief Genereaza primele 16 worduri dintr-un bloc de 512 biti.
 *
 * @param block blocul de 512 biti
 * @return word vectorul de worduri
 */
word *split_block_to_words(unsigned char *block)
{
	word *words = calloc(WORDNO, sizeof(word));
	DIE(!words, "failed malloc() of words array");

	for (int i = 0; i < 16; ++i) {
		for (size_t j = 0; j < sizeof(word); ++j) {
			words[i] <<= sizeof(char) * 8;
			words[i] |= block[sizeof(word) * i + j];
		}
	}

	return words;
}

/**
 * @brief Genereaza ultimele 48 de worduri, aplicand operatii sigma pe worduri
 * generate anterior.
 *
 * @param words vectorul de worduri
 */
void gen_words(word *words)
{
	for (int i = 16; i < WORDNO; ++i) {
		words[i] = sigma1(words[i - 2]) + words[i - 7] + sigma0(words[i - 15]) +
				   words[i - 16];
	}
}

void sha_file(char *filename)
{
	char *content = read_file_contents(filename);
	if (!content)
		return;

	unsigned char *message;
	int processed_size = pre_process(&message, content);

	/* Initializeaza digestul mesajului.
	 * (variabilele h0...h7) */
	word digest[RESWORDS];
	memcpy(digest, initwrd, RESWORDS * sizeof(word));

	for (int i = 0; i < processed_size; i += CHUNK) {
		/* Genereaza primele 16 worduri din blocul de 512 biti. */
		word *wrd = split_block_to_words(&message[i]);
		/* Completeaza cu restul de 48 de worduri, folosindu-le
		 * pe cele generate anterior. */
		gen_words(wrd);

		/* Initializeaza registrele de lucru.
		 * (variabilele a...h) */
		word wreg[RESWORDS];
		memcpy(wreg, digest, RESWORDS * sizeof(word));

		for (int k = 0; k < WORDNO; ++k) {
			/* SIGMA1(e) + ch(e, f, g) + h + K(i) + W(i); */
			word t1 = big_sigma1(wreg[4]) + ch(wreg[4], wreg[5], wreg[6]) +
					  wreg[7] + wconsts[k] + wrd[k];

			/* SIGMA0(a) + maj(a, b, c); */
			word t2 = big_sigma0(wreg[0]) + maj(wreg[0], wreg[1], wreg[2]);

			for (int l = 7; l > 0; --l)
				wreg[l] = wreg[l - 1];
			wreg[0] = t1 + t2; /* a = T1 + T2; */
			wreg[4] += t1;	   /* e =  e + T1; */
		}

		/* Adauga registrele la digest. */
		for (int k = 0; k < 8; ++k)
			digest[k] += wreg[k];

		free(wrd);
	}

	/* SHA-ul final este obtinut prin concatenarea digestului. */
	for (int k = 0; k < RESWORDS; ++k)
		printf("%08x", digest[k]);

	printf("  %s\n", filename);

	free(content);
	free(message);
}