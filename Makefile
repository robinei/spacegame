rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

CC=gcc
CFLAGS=-fno-exceptions -Wno-unused-variable
LIBS=-lm -lrt -lpthread -ldl -lSDL2 -lSDLmain -lSDL2_mixer -lGL

SRC_ALL=$(call rwildcard, src/, *.cpp *.c *.h)
DEPS_ALL=$(call rwildcard, deps/, *.cpp *.c *.h)
DEPS_C=$(call rwildcard, deps/, *.c)
DEPS_CPP=$(call rwildcard, deps/, *.cpp)
DEPS_OBJ=$(DEPS_CPP:.cpp=.o) $(DEPS_C:.c=.o)


.PHONY: debug release clean

all: debug

debug: CFLAGS += -DDEBUG -g
debug: main

release: CFLAGS += -DNDEBUG -O2
release: main

CPPFLAGS=$(CFLAGS) -fno-rtti -std=c++98


main: $(SRC_ALL) $(DEPS_ALL) deps.a
	$(CC) $(CPPFLAGS) $(LIBS) -Wall -I./src -I./deps -o main src/main.cpp deps.a

deps.a: $(DEPS_OBJ)
	ar rcs $@ $^

%.o: %.cpp
	$(CC) $(CPPFLAGS) -I./deps -c -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -I./deps -c -o $@ $<

clean:
	find . -name '*.o' -delete
	rm -f *.a
	rm -f main
