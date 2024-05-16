.default: all

all: ftt test

clean:
	rm -rf ftt *.o *.dSYM tests/test_executable tests/test_ftt.o

# Main executable
ftt: Coin.o Node.o LinkedList.o ftt.o
	g++ -Wall -Werror -std=c++14 -g -O -Iinclude -o $@ $^

# Object files from source
%.o: src/%.cpp
	g++ -Wall -Werror -std=c++14 -g -O -Iinclude -c $< -o $@

# Test compilation
test: tests/test_executable

tests/test_executable: tests/test_Coin.o tests/test_Node.o tests/test_Linkedlist.o tests/test_ftt.o
	g++ -Wall -Werror -std=c++14 -g -O -Iinclude -o $@ $^

# Pattern rule for test object files
tests/%.o: tests/%.cpp
	g++ -Wall -Werror -std=c++14 -g -O -Iinclude -c $< -o $@

# Run tests
run_test: test
	./tests/test_executable
