/* Copyright 2023 Alexandru Sima & Iarina Popa */
#include <stddef.h>
#include <stdio.h>

#include "sha.h"

int main(int argc, char *argv[])
{
	for (int i = 0; i < argc; ++i)
		sha_file(argv[i]);

	/* Daca programul este invocat fara argumente,
	 * se citesc informatiile de la stdin. */
	if (argc == 1)
		sha_file("-");
	return 0;
}