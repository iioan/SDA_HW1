# Tema 1 SDA
TEODORESCU Ioan - 313CB

Programul construieste o tabela hash in care păstram cuvintele întâlnite, alaturi de numarul de aparatii al acestora.
In timp ce citeste propozitiile (pe rand) din fisierele respective, programul identifica ce trebuie sa faca, prin analizarea primului cuvant (print sau insert). 
daca e "insert", atunci fiecare cuvant este adaugat in lista L, ca mai apoi sa fie generata tabela hash. Algoritmul de inserare este asemanator celui din laboratoare. In functia InsTHOrd din functii-tabHash.c, se vor genera subliste si se vor insera in ordine crescatoare in listele din vectorul v (*Ins_OrdLG( & a -> v[cod], M);*), iar in cazul in care am o element de tip TCuvant si vreau sa-l adaug intr-una din subliste, voi cauta sublista respectiva, in care voi insera elementul respectiv, in ordinea ceruta in enunt. Pasii importanti sunt insotite de comentariile aflate inaintea executarea pasilor.
daca primul cuvant din alineat este "print", atunci se trateaza fiecare caz si se vor afisa sublistele in functie de cerinte.

Pentru a rula tema, rulati in terminal
```
make
chmod +x check.sh
./check.sh
```
