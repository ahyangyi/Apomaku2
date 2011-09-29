LDFLAGS=-lallegro -lallegro_main -lallegro_font -lallegro_ttf -lallegro_image

all: main

main: alu.o resource.o

clean:
	-rm -rf *.o main
