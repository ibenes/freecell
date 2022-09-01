all: fc-sui

fc-sui: fc-sui.o card.o home-destination.o
	g++ $^ -o $@

%.o: %.cc 
	g++ -c $< -o $@

clean:
	rm fc-sui *.o

.PHONY: clean all
