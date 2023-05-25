/* Copyright (C) 2023 Alexandru Sima & Iarina-Ioana Popa (312CA) */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io.h"
#include "utils.h"

/**
 * @brief Citeste input de la `stdin`.
 *
 * @return stringul citit pana la intalnirea EOF (C-d)
 * @retval NULL eroare la citire (lipsa memorie)
 */
static char *read_stdin();

/**
 * @brief Calculeaza dimensiunea unui fisier.
 *
 * @param fstream 	descriptorul fisierului
 * @return long		numarul de caractere stocate in fisier
 */
static inline long get_file_size(FILE *fstream);

char *read_file_contents(char *filename)
{
	/* `filename`-ul "-" inseamna ca citirea se face de la stdin. */
	if (!strcmp(filename, "-"))
		return read_stdin();

	FILE *fstream = fopen(filename, "rb");
	if (!fstream) {
		fprintf(stderr, "Could not open file %s\n", filename);
		return NULL;
	}

	long file_size = get_file_size(fstream);

	char *contents = malloc(sizeof(char) * (file_size + 1));
	DIE(!contents, "failed malloc() of file buffer");

	fread(contents, sizeof(char), file_size + 1, fstream);
	contents[file_size] = '\0';

	fclose(fstream);
	return contents;
}

static char *read_stdin()
{
	char buffer[BUFSIZ];
	char *read_bytes = NULL;
	size_t len_bytes = 0;

	while (fgets(buffer, BUFSIZ, stdin)) {
		size_t batch_size = strlen(buffer);

		read_bytes = realloc(read_bytes, len_bytes + batch_size);
		DIE(!read_bytes, "failed realloc() of stdin buffer");

		strncpy(read_bytes + len_bytes, buffer, batch_size);
	}

	return read_bytes;
}

static inline long get_file_size(FILE *fstream)
{
	long curr_pos = ftell(fstream);
	fseek(fstream, 0, SEEK_END);
	long size = ftell(fstream);

	/* Restabileste pozitia anterioara a cursorului. */
	fseek(fstream, curr_pos, SEEK_SET);

	return size;
}
