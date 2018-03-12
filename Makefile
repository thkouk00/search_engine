OBJS	= minisearch.o get_info.o trie.o list.o funcs.o stack.o max_heap.o
SOURCE	= minisearch.c get_info.c trie.c list.c funcs.c stack.c max_heap.c
HEADER	= get_info.h trie.h list.h funcs.h stack.h max_heap.h
OUT	= minisearch
CC	= gcc
FLAGS	= -c

all: $(OBJS)
	$(CC) -o $(OUT) $(OBJS) -lm

minisearch.o: minisearch.c
	$(CC) $(FLAGS) minisearch.c

get_info.o: get_info.c
	$(CC) $(FLAGS) get_info.c 

trie.o: trie.c
	$(CC) $(FLAGS) trie.c

list.o: list.c
	$(CC) $(FLAGS) list.c

funcs.o: funcs.c
	$(CC) $(FLAGS) funcs.c

stack.o: stack.c
	$(CC) $(FLAGS) stack.c

max_heap.o: max_heap.c
	$(CC) $(FLAGS) max_heap.c

clean:
	rm -f $(OBJS) $(OUT)