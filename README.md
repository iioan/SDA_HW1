# Text Analysis Tool - Data Structures and Algorithms Project
We want to create a statistic for analyzing a text file. For example, we want to determine the frequencies of words in the text, the frequency of words with a certain length, etc.

To achieve this, it is necessary to build a hash table in which we store the encountered words. Words will be considered as strings (with a length >= 3) composed of lowercase/uppercase letters.

The program builds a hash table in which we store the encountered words along with their respective occurrence counts. While reading sentences (one at a time) from the respective files, the program identifies what to do by analyzing the first word (either 'print' or 'insert'). 

If it's 'insert,' then each word is added to the list L, which is later used to generate the hash table. The insertion algorithm is similar to the one used in the labs. In the InsTHOrd function from functii-tabHash.c, sublists are generated and inserted in ascending order into the lists in the vector v (Ins_OrdLG(&a->v[cod], M);), and in the case of having an element of type TCuvant that needs to be added to one of the sublists, I will search for the respective sublist in which I will insert the element according to the specified order in the statement. 

Important steps are accompanied by comments placed before the execution of each step. If the first word in the paragraph is 'print,' then each case is handled, and sublists are displayed according to the requirements.

# Tema 1 Structuri de date si Algoritmi
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
