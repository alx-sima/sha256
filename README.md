#### Sima Alexandru și Popa Iarina-Ioana (312CA) 2023

# SHA-256

## Standard

- SHA-2 (Secure Hash Algorithm 2) este un set de algoritmi criptografici
  dezvoltați de NSA.

- Acesta a devenit standard în 2002.

- SHA-256 este o funcție din standardul SHA-2 care returnează un hash de 256 de
  biți.

---

## De ce am ales acest proiect?

- Algoritmii de hash sunt foarte importanți, deoarece ajută la verificarea
  integrității datelor și la crearea de semnături digitale.

- Criptarea parolelor este un mecanism de securitate esențial.

- Funcțiile de hash au proprietăți matematice interesante, precum
  imposibilitatea inversării lor fără brute-force și variația mică a inputului
  care duce la o variație mare a outputului.

- Având în vedere că am învățat importanța funcțiilor de hash semestrul trecut,
  ne-am gândit că ar fi interesant să vedem implementarea algoritmilor și să
  înțelegem matematica din spate.

---

## Algoritm

- Se inițializează 8 variabile care reprezintă hashul (primii 32 de biți ai
  părților fracționare ale radicalilor primelor 8 numere prime)

- Mesajul se preprocesează, adaugându-se un bit 1 la finalul acestuia și
  completându-se cu 0 și cu un întreg pe 64 de biți (reprezentând lungimea
  șirului) până la o lungime multiplu de 512 biți.

- Mesajul se prelucrează în chunkuri de câte 512 biți, astfel:
  - Se copiază mesajul în primele 16 variabile de lucru.
  - Se calculează încă 48 de variabile de lucru, aplicându-se operații pe biți
    celor anterioare.
  - Se comprimă chunkul, aplicându-se operații pe biți în care sunt implicate
    variabilele de lucru, hashul până la acest moment și 64 de constante
    matematice (primii 32 de biți ai părților fracționare ale rădăcinilor cubice
    ale primelor 64 de numere prime).
  - Se adaugă "hashul" chunkului comprimat la hashul total.

- La final, se concatenează cele 8 variabile de hash.

---
