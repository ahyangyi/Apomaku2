LDFLAGS=-lallegro -lallegro_main -lallegro_font -lallegro_ttf -lallegro_image

all: main

main: alu.o resource.o

alu.o: alu.c alu.h

resource.o: resource.c resource.h

clean:
	-rm -rf *.o main
