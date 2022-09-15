CXXFLAGS=-std=c++17 -Wall -Wextra

BUILD_DIR=./build

SOURCES = card.cc card-storage.cc move.cc game.cc
OBJ = $(SOURCES:%.cc=$(BUILD_DIR)/%.o)

all: $(BUILD_DIR) fc-sui

fc-sui: $(BUILD_DIR)/fc-sui.o $(OBJ)
	$(CXX) $^ -o $@

$(BUILD_DIR)/%.o:  %.cc 
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf build
	rm -f fc-sui test-bin

TEST_SOURCES = test-main.cc test.cc
TEST_OBJ = $(TEST_SOURCES:%.cc=$(BUILD_DIR)/%.o)
test-bin: $(TEST_OBJ) $(OBJ)
	$(CXX) $^ -o $@

test: $(BUILD_DIR) test-bin
	./test-bin

.PHONY: clean all
