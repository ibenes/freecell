all: fc-sui

fc-sui: fc-sui.o card.o card-storage.o
	g++ $^ -o $@

%.o: %.cc 
	g++ -c $< -o $@

clean:
	rm fc-sui test-bin *.o

test-bin: test.cc card.o card-storage.o
	g++ $^ -o $@

test: test-bin
	./test-bin

.PHONY: clean all
