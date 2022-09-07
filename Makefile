CXXFLAGS=-std=c++17 -Wall -Wextra

all: fc-sui

fc-sui: fc-sui.o card.o card-storage.o move.o
	$(CXX) $^ -o $@

%.o: %.cc 
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f fc-sui test-bin *.o

test-bin: test-main.o test.o card.o card-storage.o move.o
	$(CXX) $^ -o $@

test: test-bin
	./test-bin

.PHONY: clean all
