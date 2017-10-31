CFLAGS=-Wall -Wextra -pedantic
FICHEIROS=cgi.h estado.h game.c images.h prototipos.h easteregg.c ler_ficheiro.c escreve_ficheiro.c Makefile images2.0 moves.c ataques.c

install: game
	sudo cp game /usr/lib/cgi-bin
	sudo rm -rf /var/www/html/images2.0/
	sudo cp -a images2.0 /var/www/html/
	gcc -o duvida duvida.c
	sudo cp duvida /usr/lib/cgi-bin
	touch username
	sudo rm -rf /var/www/html/user
	sudo mkdir /var/www/html/user
	sudo cp username /var/www/html/user
	touch myscore
	sudo cp myscore /var/www/html/user
	rm myscore username
	(cd gameover/ && make)
	(cd pagInicial/ && make)
	sudo chown -R www-data:www-data /var/www/html/
	(cd /var/www/html/user/ && sudo chmod a+rw * /var/www/html/user/)
	touch install
	nano README.txt

game: game.o easteregg.o moves.o moves.o escreve_ficheiro.o ler_ficheiro.o ataques.o escreve_pontos.o
	cc -o game game.o easteregg.o moves.o escreve_ficheiro.o ler_ficheiro.o ataques.o escreve_pontos.o


game.zip: $(FICHEIROS)
	zip -9 game.zip $(FICHEIROS)

doc:
	doxygen -g
	doxygen
	rm -rf latex/
	(cd gameover/ && make doc)
	(cd pagInicial/ && make doc)

clean all:
	rm -rf *.o game duvida username Doxyfile latex html install
	(cd gameover/ && make clean)
	(cd pagInicial/ && make clean)

clean:
	rm -rf *.o game username Doxyfile latex html install


easteregg.o: easteregg.c prototipos.h game.c
game.o: game.c cgi.h estado.h prototipos.h easteregg.o moves.o escreve_ficheiro.o ler_ficheiro.o ataques.o
moves.o: moves.c prototipos.h cgi.h estado.h
escreve_ficheiro.o: prototipos.h estado.h
ler_ficheiro.o: prototipos.h estado.h
ataques.o: ataques.c prototipos.h estado.h
escreve_pontos.o: escreve_pontos.c cgi.h
