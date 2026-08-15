CC = gcc

CFLAGS = -Wall -O2 $(shell sdl2-config --cflags)

LDFLAGS = $(shell sdl2-config --libs) -lSDL2_ttf -lSDL2_image

TARGET = game

OBJS = main.o render.o render_map.o player.o map.o battle.o \
magic.o chest.o cave.o cave_b1.o cave_b2.o enemy.o equipment.o \
enemy_skill.o temple.o message_ui.o save.o

all: $(TARGET)

run: all
	./$(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(TARGET) *.o
