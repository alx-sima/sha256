/* Copyright 2023 Alexandru Sima & Iarina-Ioana Popa */
#ifndef SHA256_H_
#define SHA256_H_

/**
 * @brief Calculeaza sha-ul continutului fisierului `filename` sau de la stdin
 * daca `filename == "-"`.
 *
 * @param filename calea catre fisier
 */
void sha_file(char *filename);

#endif /* SHA256_H_ */