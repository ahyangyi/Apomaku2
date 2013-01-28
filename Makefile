LDFLAGS=-lallegro -lallegro_main -lallegro_font -lallegro_ttf -lallegro_image

all: main

main: alu.o resource.o

alu.o: alu.cpp alu.h

resource.o: resource.cpp resource.h

clean:
	-rm -rf *.o main
