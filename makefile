main: main.cpp objects/inputreader.o objects/board.o objects/manhattan.o objects/bfs.o objects/queue.o objects/hash.o
	g++ objects/result.o objects/hash.o  objects/inputreader.o objects/board.o objects/queue.o objects/manhattan.o objects/bfs.o main.cpp -o  main 

test_board: tests/test_board.c objects/board.o
	gcc objects/board.o tests/test_board.c -o  tests/run_tests/test_board

test_manhattan: tests/test_manhattan.c objects/board.o objects/manhattan.o
	gcc objects/manhattan.o objects/board.o tests/test_manhattan.c -o  tests/run_tests/test_manhattan

objects/inputreader.o: headers/modules/inputreader.c
	gcc -o objects/inputreader.o -c headers/modules/inputreader.c

objects/board.o: headers/modules/board.c
	gcc -o objects/board.o -c headers/modules/board.c 

objects/manhattan.o: headers/modules/manhattan.c objects/board.o
	gcc -o objects/manhattan.o -c headers/modules/manhattan.c
	

objects/hash.o: headers/modules/hash.c
	gcc -o objects/hash.o -c headers/modules/hash.c

objects/result.o: headers/modules/result.c
	gcc -o objects/result.o -c headers/modules/result.c

objects/queue.o: headers/modules/queue.c objects/board.o
	gcc -o objects/queue.o -c headers/modules/queue.c


objects/bfs.o: objects/result.o objects/hash.o headers/modules/bfs.cpp objects/board.o objects/manhattan.o objects/queue.o
	g++ objects/result.o objects/queue.o objects/board.o objects/manhattan.o objects/hash.o -o objects/bfs.o -c headers/modules/bfs.cpp

clean:
	rm objects/*

