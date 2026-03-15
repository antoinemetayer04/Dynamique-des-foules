PROJECT_NAME := dynamique-des-foules

INCLUDE_PATH = ./include
SOURCE_PATH  = ./src
BUILD_PATH   = ./build
RESULTS_PATH = ./results

SRC  = $(shell find $(SOURCE_PATH) -type f -name "*.cpp")
OBJ  = $(patsubst $(SOURCE_PATH)/%.cpp, $(BUILD_PATH)/%.o, $(SRC))
EXE  = $(PROJECT_NAME).x

CXX = g++
CXXFLAGS = -Wall -Werror -std=c++17 -I$(INCLUDE_PATH) -MMD -MP
LDFLAGS  = 

.PHONY: all run clean realclean

all: $(EXE)

run: $(EXE)
	@mkdir -p results
	./$(EXE)

$(EXE): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Compilation des .cpp du src en .o dans build/
$(BUILD_PATH)/%.o: $(SOURCE_PATH)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@rm -f *~
	@rm -rf $(BUILD_PATH)

realclean: clean 
	@rm -f $(EXE)

-include $(OBJ:.o=.d)