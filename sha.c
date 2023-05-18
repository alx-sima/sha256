/* Copyright 2023 Alexandru Sima & Iarina-Ioana Popa */
#include <stdio.h>

#include "io.h"
#include "sha.h"

void sha_file(char *filename)
{
	char *content = read_file_contents(filename);

	// TODO calculeaza sha-ul
	printf("%s %s\n", content, filename);
}