CFLAGS=-Wall
FICHEIROS=cgi.h images.h inicio.c Makefile

install: Animelike
	sudo cp Animelike /usr/lib/cgi-bin
	sudo chown -R www-data:www-data /var/www/html/
	touch install


Animelike: Animelike.o
	cc -o Animelike Animelike.o


doc:
		doxygen -g
		doxygen
		rm -rf latex/

clean:
	rm -rf *.o Animelike Doxyfile latex html install

Animelike.o: Animelike.c cgi.h images.h
