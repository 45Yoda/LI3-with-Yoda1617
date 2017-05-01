CC = gcc
CFLAGS = -Wall -g `pkg-config --cflags libxml-2.0` `pkg-config --cflags glib-2.0`
LIBS = `pkg-config --libs libxml-2.0` `pkg-config --libs glib-2.0`

program:
	$(CC) $(CFLAGS) *.c -o program $(LIBS)

clean:
	rm  program

cleanAll: clean
	-@rm -rf doc
	-@rm -rf html
	-@rm -rf latex
	
.PHONY: doc
doc:$(OBJS)
		doxygen doxygen.conf
