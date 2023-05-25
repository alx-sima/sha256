/* Copyright (C) 2023 Alexandru Sima & Iarina-Ioana Popa (312CA) */

#ifndef IO_H_
#define IO_H_

/**
 * @brief Citeste continutul unui fisier.
 *
 * @param filename 	numele fisierului; daca este "-", citeste de la stdin
 * @return char* 	continutul fisierului
 * @retval NULL 	eroare la citire (fisierul nu exista)
 */
char *read_file_contents(char *filename);

#endif /* IO_H_ */
