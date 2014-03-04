graph: graph.o
	gcc -Wall graph.c -o graph

# graph.o: graph.c 
#	gcc -Wall -c graph.c 

t: graph
#./graph test.dat
	./graph read.dat

clean:
	rm -f core* graph.o 
