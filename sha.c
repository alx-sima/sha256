/* Copyright 2023 Alexandru Sima & Iarina-Ioana Popa */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bit_functions.h"
#include "io.h"
#include "sha.h"
#include "sha256_consts.h"

/**
 * @brief Pregateste stringul pentru hashing, adaugand padding un bit de 1 si
 * restul 0, apoi lungimea stringului original, pana obtinerea unui string cu
 * lungime un multiplu de 512.
 *
 * @param dest 	locatia stringului procesat
 * @param str 	stringul de procesat
 * @return int 	lungimea stringului prelucrat
 */
int pre_process(unsigned char **dest, char *str)
{
	const int padd_size = 1 + CHUNK / 8;
	size_t str_length = strlen(str);

	// TODO: salveaza in bytes individuali
	int str_size = str_length + padd_size;
	if (str_size % CHUNK)
		str_size += CHUNK - (str_size % CHUNK);

	unsigned char *blob = calloc(str_size, sizeof(unsigned char));
	memcpy(blob, str, str_length);
	blob[str_length] = 0x80;

	size_t len = str_length * 8;
	for (int i = 0; len; ++i) {
		blob[str_size - i - 1] = (unsigned char)(len & 0xff);
		len >>= 8;
	}
	*dest = blob;
	return str_size;
}

/**
 * @brief Genereaza primele 16 worduri dintr-un bloc de 512 biti.
 *
 * @param first blocul de 512 biti
 * @param dest 	vectorul de worduri
 */
void split_block_to_words(unsigned char *first, word **dest)
{
	word *words = calloc(WORDNO, sizeof(word));
	for (int i = 0; i < 16; ++i) {
		for (size_t j = 0; j < sizeof(word); ++j) {
			words[i] <<= sizeof(char) * 8;
			words[i] |= first[sizeof(word) * i + j];
		}
	}
	*dest = words;
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
	unsigned char *dest;
	char *content = read_file_contents(filename);
	if (!content)
		return;
	int j = pre_process(&dest, content);

	// variabilele h0-h7
	word digest[8];
	memcpy(digest, initwrd, 8 * sizeof(word));

	for (int i = 0; i < j; i += CHUNK) {
		word *wrd;
		split_block_to_words(dest + i, &wrd);
		gen_words(wrd);

		// variabilele a-h
		word wreg[8];
		memcpy(wreg, digest, 8 * sizeof(word));

		for (int k = 0; k < WORDNO; ++k) {
			// SIGMA1(e) + ch(e, f, g) + h + K(i) + W(i)
			word t1 = big_sigma1(wreg[4]) + ch(wreg[4], wreg[5], wreg[6]) +
					  wreg[7] + wconsts[k] + wrd[k];
			// SIGMA0(a) + maj(a, b, c)
			word t2 = big_sigma0(wreg[0]) + maj(wreg[0], wreg[1], wreg[2]);

			for (int l = 7; l > 0; --l)
				wreg[l] = wreg[l - 1];
			// a = T1 + T2
			wreg[0] = t1 + t2;
			// e += t1
			wreg[4] += t1;
		}

		// Adauga a...h la h0...h7
		for (int k = 0; k < 8; ++k)
			digest[k] += wreg[k];
		free(wrd);
	}

	for (int k = 0; k < RESWORDS; ++k)
#ifdef LONGWRD
		printf("%016llx", digest[k]);
#else
		printf("%08x", digest[k]);
#endif

	printf("%s %s\n", content, filename);
	free(content);
	free(dest);
}