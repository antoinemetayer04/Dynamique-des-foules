PROJECT_NAME := dynamique-des-foules

INCLUDE_PATH = ./include
SOURCE_PATH  = ./src
TEST_PATH    = ./test
BUILD_PATH   = ./build

SRC  = $(shell find $(SOURCE_PATH) -type f -name "*.cpp")
OBJ  = $(patsubst $(SOURCE_PATH)/%.cpp, $(BUILD_PATH)/%.o, $(SRC))
EXE  = $(PROJECT_NAME).x

TEST_SRC = $(shell find $(TEST_PATH) -type f -name "*.cpp")
TEST_OBJ = $(patsubst $(TEST_PATH)/%.cpp, $(BUILD_PATH)/%.test.o, $(TEST_SRC))
TEST = test.x

CXX = g++
CXXFLAGS = -Wall -Werror -std=c++17 -I$(INCLUDE_PATH) -MMD -MP
LDFLAGS  = 

.PHONY: all run clean test realclean

all: $(EXE)

run: $(EXE)
	./$(EXE)

$(EXE): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Compilation des .cpp du src en .o dans build/
$(BUILD_PATH)/%.o: $(SOURCE_PATH)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compilation des .cpp du test en .test.o dans build/
$(BUILD_PATH)/%.test.o: $(TEST_PATH)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(TEST)
	./$(TEST)

$(TEST): $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	@rm -f *~
	@rm -rf $(BUILD_PATH)
	@rm -f $(TEST)

realclean: clean
	@rm -f $(EXE)

-include $(OBJ:.o=.d)
-include $(TEST_OBJ:.o=.d)