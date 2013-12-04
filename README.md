jnp4
====

Tutaj jakieś uwagi na bieżąco.

Monika, wtorek 2:00 AM

Więc tak, dopisałam trochę kodu, ale w wielu miejscach nie jestem pewna - zaznaczone ??
Niektorych rzeczy nie pisalam do konca (szczegolnie tych wszytskich metod operatorow, bo 
to jest w znacznej czesci copy-paste, wiec ustalny na razie strukure ostateczna, a potem
to sie w mig zrobi)

1. Nie wiem zupelnie, jak mamy wykorzystac struct Company do stworzenia Konatoru itp. Wiesz moze? 

2. Spojrz na tego typedef'a w Groupie

3. Wydaje mi sie, ze opratyor + mozna zapisac pooprzez konstruktor i =+ -> kom w kodzie

4. Nie uwzglednialam nigdzie dzielenia przez zero, ktore ma dac 0 -> NIE ZAPOMNIEC!

I tyle chyba na biezaco ;)

Maciej, sroda 3:30

Ad 1. Chyba zrobione :)
Ad 2. Spojrzane, zmienione, chyba tak jest ok.
Ad 3. Tez tak mysle.
Ad 4. To dodalem.

Dodalem wszystko poza tymi operacjami "globalnymi". Bez tego nie ma juz zadnych bledow kompilacji, poza
oczywiscie "niewidocznoscią" niezdefiniowanych jeszcze funkcji. Jakiś maly problem sie pojawil przy 
solve_auction, gdy probowalem napisac, ale juz nie mam sily nad tym myslec. Jezeli masz jakies uwagi
do wprowadzonych zmian to smialo. Wydaje mi sie, ze "glowna" koncepcja jest ok, jezeli nie ma wiekszych bledow
to pozostalo napisac te globalne funkcje.
