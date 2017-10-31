CFLAGS=-Wall
FICHEIROS=cgi.h Makefile gameover.c song.mp3

install: gameover
	sudo cp gameover /usr/lib/cgi-bin
	sudo cp score /var/www/html/user/
	sudo chown -R www-data:www-data /var/www/html/
	touch install


gameover: gameover.o leitura.o escreve.o
	cc -o gameover gameover.o leitura.o escreve.o

doc:
		doxygen -g
		doxygen
		rm -rf latex/


clean:
	rm -rf *.o gameover Doxyfile latex html install

gameover.o: gameover.c cgi.h leitura.c
leitura.o: leitura.c cgi.h
escreve.o: escreve.c cgi.h
