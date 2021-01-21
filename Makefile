CFLAGS=--std=c11 -Wall -pedantic -Isrc/ -ggdb -Wextra -Werror -DDEBUG
CC=gcc

all: rotate_image

bmp.o: bmp.c
	$(CC) -c $(CFLAGS) $< -o $@

image.o: image.c
	$(CC) -c $(CFLAGS) $< -o $@

util.o: util.c
	$(CC) -c $(CFLAGS) $< -o $@

main.o: main.c
	$(CC) -c $(CFLAGS) $< -o $@

rotate_image: main.o util.o image.o bmp.o
	$(CC) -o rotate_image $^

clean:
	rm -f main.o util.o image.o bmp.o rotate_image

