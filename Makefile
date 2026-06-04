CC = gcc

CFLAGS = -Wall -O2 $(shell sdl2-config --cflags)

LDFLAGS = $(shell sdl2-config --libs)

TARGET = game

OBJS = main.o render.o player.o map.o

all: $(TARGET)

run: all
	./$(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(TARGET) *.o
