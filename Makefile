CXXFLAGS=-std=c++17 -Wall -Wextra -pedantic -O2

BUILD_DIR=./build
DEP_DIR=./dep

SOURCES = card.cc card-storage.cc move.cc game.cc strategies-provided.cc search-interface.cc sui-solution.cc memusage.cc mem_watch.cc evaluation-type.cc
OBJ = $(SOURCES:%.cc=$(BUILD_DIR)/%.o)

all: $(BUILD_DIR) $(DEP_DIR) fc-sui

fc-sui: $(BUILD_DIR)/fc-sui.o $(OBJ)
	$(CXX) $^ -lpthread -o $@

-include $(wildcard $(DEP_DIR)/*.d)

$(BUILD_DIR)/%.o: %.cc 
	$(CXX) $(CXXFLAGS) -MT $@ -MMD -MP -MF $(DEP_DIR)/$*.d -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(DEP_DIR):
	mkdir -p $(DEP_DIR)

clean:
	rm -rf $(BUILD_DIR) $(DEP_DIR)
	rm -f fc-sui test-bin

TEST_SOURCES = test-main.cc test.cc
TEST_OBJ = $(TEST_SOURCES:%.cc=$(BUILD_DIR)/%.o)
test-bin: $(TEST_OBJ) $(OBJ)
	$(CXX) $^ -o $@

test: $(BUILD_DIR) $(DEP_DIR) test-bin
	./test-bin

.PHONY: clean all
