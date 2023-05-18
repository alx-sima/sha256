/* Copyright 2023 Alexandru Sima & Iarina-Ioana Popa */
#ifndef IO_H_
#define IO_H_

/**
 * @brief Citeste si intoarce continutul unui fisier/de la tastatura.
 *
 * @param filename calea fisierului citit. calea speciala "-" inseamna STDIN
 *
 * @return      continutul fisierului
 * @retval NULL a intervenit o eroare la citire
 */
char *read_file_contents(char *filename);

#endif /* IO_H_ */