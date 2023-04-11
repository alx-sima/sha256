#### Sima Alexandru și Popa Iarina-Ioana (312CA) 2023

# SHA-256

## Standard

- SHA-2 (Secure Hash Algorithm 2) este un set de algoritmi de criptografici
  dezvoltati de NSA.

- Acesta a devenit standard în 2002.

- SHA-256 este o funcție din standardul SHA-2 care returnează un hash de 256 de
  biți.

--------------------------------------------------------------------------------

## Algoritm

- Se inițializează 8 variabile care reprezintă hashul (primii 32 de biți ai
  părților fracționare ale radicalilor primelor 8 numere prime)

- round constants (TODO)

- preprocesare (TODO)

- Mesajul se prelucrează în chunk-uri de câte 512 biți, astfel:
  - Se copiază mesajul în primele 16 variabile de lucru.
  - Se calculează încă 48 de variabile de lucru aplicându-se operații pe biți
    celor anterioare.
  - Se comprimă chunkul, aplicându-se operații pe biți în care sunt implicate
    variabilele de lucru, hashul până la acest moment și 64 de constante
    matematice (primii 32 de biți ai părților fracționare ale rădăcinilor cubice
    ale primelor 64 de numere prime).
  - Se adaugă "hashul" chunkului comprimat la hashul total.
- La final, se concateneaza cele 8 variabile de hash.
