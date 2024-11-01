main: main.cpp objects/inputreader.o objects/board.o objects/manhattan.o objects/bfs.o objects/queue.o objects/hash.o objects/idfs.o objects/astar.o objects/idastar.o objects/gbfs.o
	g++ objects/result.o objects/hash.o  objects/inputreader.o objects/board.o objects/queue.o objects/manhattan.o objects/bfs.o objects/idfs.o objects/astar.o objects/idastar.o objects/gbfs.o main.cpp -O2 -o main 

test_board: tests/test_board.c objects/board.o
	gcc objects/board.o tests/test_board.c -o  tests/run_tests/test_board

test_manhattan: tests/test_manhattan.c objects/board.o objects/manhattan.o
	gcc objects/manhattan.o objects/board.o -O2 tests/test_manhattan.c -o  tests/run_tests/test_manhattan

objects/inputreader.o: headers/modules/inputreader.c
	gcc -o objects/inputreader.o -c headers/modules/inputreader.c

objects/board.o: headers/modules/board.c
	gcc -o objects/board.o -O2 -c headers/modules/board.c 

objects/manhattan.o: headers/modules/manhattan.c objects/board.o
	gcc -o objects/manhattan.o -c headers/modules/manhattan.c

objects/hash.o: headers/modules/hash.c
	gcc -o objects/hash.o -c headers/modules/hash.c

objects/result.o: headers/modules/result.c
	gcc -o objects/result.o -c headers/modules/result.c

objects/queue.o: headers/modules/queue.c objects/board.o
	gcc -o objects/queue.o -c headers/modules/queue.c


objects/bfs.o: objects/result.o objects/hash.o headers/modules/bfs.cpp objects/board.o objects/manhattan.o objects/queue.o
	g++ -o objects/bfs.o -c -O2 headers/modules/bfs.cpp

objects/idfs.o: objects/result.o objects/hash.o headers/modules/idfs.cpp objects/board.o objects/manhattan.o objects/queue.o
	g++ -o objects/idfs.o -c -O2 headers/modules/idfs.cpp

objects/astar.o: objects/result.o objects/hash.o headers/modules/astar.cpp objects/board.o objects/manhattan.o objects/queue.o
	g++ -o objects/astar.o -c -O2 headers/modules/astar.cpp

objects/idastar.o: objects/result.o objects/hash.o headers/modules/idastar.cpp objects/board.o objects/manhattan.o objects/queue.o
	g++ -o objects/idastar.o -c -O2 headers/modules/idastar.cpp

objects/gbfs.o: objects/result.o objects/hash.o headers/modules/gbfs.cpp objects/board.o objects/manhattan.o objects/queue.o
	g++ -o objects/gbfs.o -c -O2 headers/modules/gbfs.cpp

clean:
	rm objects/*

