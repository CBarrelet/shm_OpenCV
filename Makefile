CC = g++
PROJECT = main
SRC = main.cpp Shared_memory.cpp
LIBS = `pkg-config --cflags --libs opencv`
LDFLAGS = -lrt
$(PROJECT) : $(SRC)
	$(CC) $(SRC) -o $(PROJECT) $(LIBS) $(LDFLAGS)