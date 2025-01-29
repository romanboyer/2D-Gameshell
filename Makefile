CC = gcc

# Options de compilation et d'inclusion
CFLAGS = -I/opt/homebrew/include/SDL2 \
         -I/opt/homebrew/Cellar/sdl2_image/2.8.2_2/include/SDL2 \
         -I/opt/homebrew/Cellar/sdl2_ttf/2.22.0/include/SDL2 \
         -I/opt/homebrew/Cellar/sdl2_mixer/2.8.0/include/SDL2 \

# Options de lien
LDFLAGS = -L/opt/homebrew/lib \
          -L/opt/homebrew/Cellar/sdl2_image/2.8.2_2/lib \
          -L/opt/homebrew/Cellar/sdl2_ttf/2.22.0/lib \
          -L/opt/homebrew/Cellar/sdl2_mixer/2.8.0/lib \
          -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

all : clean prog

prog : main.o map_base.o map_1.o map_2.o map_3.o
	$(CC) -o prog main.o map_base.o map_1.o map_2.o map_3.o $(LDFLAGS)

main.o : src/main.c header/map_base.h header/windows_settings.h header/state.h
	$(CC) $(CFLAGS) -o main.o -c src/main.c

map_base.o : src/map_base.c header/map_base.h header/windows_settings.h header/state.h
	$(CC) $(CFLAGS) -o map_base.o -c src/map_base.c

map_1.o : src/map_1.c header/map_base.h header/windows_settings.h header/state.h
	$(CC) $(CFLAGS) -o map_1.o -c src/map_1.c

map_2.o : src/map_2.c header/map_base.h header/windows_settings.h header/state.h
	$(CC) $(CFLAGS) -o map_2.o -c src/map_2.c

map_3.o : src/map_3.c header/map_base.h header/windows_settings.h header/state.h
	$(CC) $(CFLAGS) -o map_3.o -c src/map_3.c

clean : 
	rm -rf *.o prog


