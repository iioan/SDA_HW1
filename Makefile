build: 
	gcc -o tema1 functiiLG.c functii-tabHash.c testHash.c -std=gnu99 -Wall -Wextra
run:
	./tema1
clean:
	rm -rf tema1
