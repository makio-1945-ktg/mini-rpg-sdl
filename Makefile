CC = gcc

CFLAGS = -Wall -O2 $(shell sdl2-config --cflags)

LDFLAGS = $(shell sdl2-config --libs) -lSDL2_ttf -lSDL2_image

TARGET = game

OBJS = main.o render.o render_map.o player.o equipment.o \
battle_core.o battle_input.o battle_start.o magic.o \
chest.o map.o cave.o cave_b1.o cave_b2.o temple.o \
enemy.o enemy_skill.o message_ui.o save.o

all: $(TARGET)

run: all
	./$(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(TARGET) *.o
