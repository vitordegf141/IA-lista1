main: main.cpp objects/inputreader.o objects/board.o objects/manhattan.o objects/bfs.o objects/queue.o objects/hash.o
	g++ objects/result.o objects/hash.o objects/bfs.o  objects/inputreader.o objects/board.o objects/queue.o objects/manhattan.o main.cpp -o  main 

test_board: tests/test_board.cpp objects/board.o
	g++ objects/board.o tests/test_board.cpp -o  tests/run_tests/test_board

test_manhattan: tests/test_manhattan.cpp objects/board.o objects/manhattan.o
	g++ objects/manhattan.o objects/board.o tests/test_manhattan.cpp -o  tests/run_tests/test_manhattan

objects/inputreader.o: headers/modules/inputreader.cpp
	g++ -o objects/inputreader.o -c headers/modules/inputreader.cpp

objects/board.o: headers/modules/board.cpp
	g++ -o objects/board.o -c headers/modules/board.cpp 

objects/manhattan.o: headers/modules/manhattan.cpp objects/board.o
	g++ -o objects/manhattan.o -c headers/modules/manhattan.cpp
	

objects/hash.o: headers/modules/hash.cpp
	g++ -o objects/hash.o -c headers/modules/hash.cpp

objects/result.o: headers/modules/result.cpp
	g++ -o objects/result.o -c headers/modules/result.cpp

objects/queue.o: headers/modules/queue.cpp objects/board.o
	g++ -o objects/queue.o -c headers/modules/queue.cpp


objects/bfs.o: objects/result.o objects/hash.o headers/modules/bfs.cpp objects/board.o objects/manhattan.o objects/queue.o
	g++ objects/result.o objects/queue.o objects/board.o objects/manhattan.o objects/hash.o -o objects/bfs.o -c headers/modules/bfs.cpp

clean:
	rm objects/*

