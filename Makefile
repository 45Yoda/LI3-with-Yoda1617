CC = gcc
CFLAGS = -Wall -g `pkg-config --cflags libxml-2.0` `pkg-config --cflags glib-2.0`
LIBS = `pkg-config --libs libxml-2.0` `pkg-config --libs glib-2.0`

ourparser:
	$(CC) $(CFLAGS) *.c -o ourparser $(LIBS)

clean:
	rm *.o ourparser
