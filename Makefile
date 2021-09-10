all:
	gcc source.c -o Raymarching.exe -Wall -W -Werror -lraylib -lgdi32 -lwinmm
	./Raymarching.exe