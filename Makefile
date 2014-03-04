graph: graph.c
	gcc -Wall graph.c -o graph

test: graph
	./graph read.dat

clean:
	rm -f core* graph.o 
