# Tema01 PA 2020

## Scopul temei

Familiarizarea cu tehnici de programare precum Greedy si programare dinamica.


## Implementare

##### Problema 1 - Bani

- Citim numarul de bancnote si setul de instructiuni.
- Pentru setul 1, deducem o formula de recurenta: cum fiecare bancnota are cate 2 succesori, numarul de combinatii de la pasul urmator va fi dublu numarului de la pasul anterior. Avand 5 bancnote disponibile, reiese formula 5 * 2 ^ (n - 1).
- Pentru setul 2, folosim programarea dinamica si retinem la fiecare pas numarul de combinatii specifice fiecarei bancnote. Numarul de combinatii ale unei bancnote se obtine adunand numarul de combinatii ale unei bancnote care o preced de la pasul anterior.
*eg.* bancnota de 10 lei urmeaza dupa bancnotele de 50, 100 si 500 de lei. Asadar, numarul de bancnote de 10 lei de la pasul curent este egal cu suma numerelor de bancnote de 50, 100 si 500 de lei de la pasul anterior.
- Repetam procesul pentru fiecare tip de bancnota pana la N, apoi adunam numerele de bancnote de la pasul N pentru a obtine numarul total de combinatii pe care le putem obtine din cele 5 bancnote.
- *Complexitate: O(N)*


##### Problema 2 - Gard

- Rezolvam problema folosind metoda Greedy.
- Cream o structura Plank care retine coordonata start si end a unei placi.
- Sortam vectorul de planks crescator dupa coordonata start.
- Retinem in variabila last_good_plank (nu am gasit un nume mai bun) prima placa din vector, pe care o consideram neredundanta.
- Parcurgem vectorul de placi si verificam daca coordonata end a plank[i] este mai mica decat cea a ultimei placi neredundante. Daca este mai mica sau egala, incrementam numarul de placi redundante. In caz contrar, consideram placa gasita ca fiind neredundanta, updatand variabila last_good_plank.
- Returnam numarul de placi redundante gasite.
- *Complexitate: O(N * log N)*

##### Problema 3 - Bomboane

- Pentru inceput, calculam suma limitelor inferioare si superioare ale intervalelor de probleme, pentru a verifica daca e posibil sa impartim bomboane:
        - Daca numarul de bomboane este egal cu suma capetelor superioare sau a capetelor inferioare ale intervalelor, se pot imparti bomboane intr-un singur mod.
        - Daca numarul de bomboane este mai mic decat suma capetelor inferioare sau mai mare decat suma capetelor superioare, nu putem imparti in niciun mod.
- Folosim programare dinamica si alegem o matrice dp de N * M elemente, in care retinem numarul de moduri prin care se poate obtine suma M din intervalele date.
- Retinem in variabila combinations_number suma elementelor din matricea dp de la [j - max] la [j - min] de pe linia precedenta, care reprezinta numarul de combinatii prin care se poate obtine suma j cu ajutorul intervalelor de pana acum.
- Vom obtine astfel pe ultimul element al matricei numarul total de moduri in care putem obtine suma M.
- *Complexitate: O(M * N)*
