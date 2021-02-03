BIN_DIR=bin
FLAGS=-W -O2 -g -std=c99
CC=gcc
INC=-Isrc

.PHONY: tests check

all: tests

tests:
	mkdir -p $(BIN_DIR)
	$(CC) $(FLAGS) $(INC) src/uintv.c tests/test_uintv.c -o $(BIN_DIR)/test_uintv
	$(CC) $(FLAGS) $(INC) src/uintv.c src/uintvv.c tests/test_uintvv.c -o $(BIN_DIR)/test_uintvv
	$(CC) $(FLAGS) $(INC) src/uintv.c src/uintvv.c src/transition.c src/transitionv.c src/dfa.c tests/test_dfa.c -o $(BIN_DIR)/test_dfa

check: tests
	./$(BIN_DIR)/test_uintv
	./$(BIN_DIR)/test_uintvv
	./$(BIN_DIR)/test_dfa

clean:
	rm $(BIN_DIR)/*
	rmdir $(BIN_DIR)
