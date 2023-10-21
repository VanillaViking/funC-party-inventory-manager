
CC = gcc
CFLAGS = -Wall -Werror -ansi -lm -g

SOURCEDIR = src
BUILD = build
EXECUTABLE=party_inventory_manager

all: dir $(BUILD)/main.o $(BUILD)/bstree.o $(BUILD)/database.o
	$(CC) $(CFLAGS) $(BUILD)/main.o $(BUILD)/bstree.o $(BUILD)/database.o -o $(BUILD)/$(EXECUTABLE)
	@echo "Build successful. Run ./build/party_inventory_manager"

dir:
	mkdir -p $(BUILD)

clean:
	rm -rf $(BUILD)

.PHONY: all dir clean

$(BUILD)/main.o: $(SOURCEDIR)/main.c $(SOURCEDIR)/main.h
	$(CC) $(CFLAGS) -c $(SOURCEDIR)/main.c -o $(BUILD)/main.o

$(BUILD)/bstree.o: $(SOURCEDIR)/bstree.c $(SOURCEDIR)/bstree.h
	$(CC) $(CFLAGS) -c $(SOURCEDIR)/bstree.c -o $(BUILD)/bstree.o

$(BUILD)/database.o: $(SOURCEDIR)/database.c $(SOURCEDIR)/database.h
	$(CC) $(CFLAGS) -c $(SOURCEDIR)/database.c -o $(BUILD)/database.o

