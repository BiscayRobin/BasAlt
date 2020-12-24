CXX 		:= clang++
CXXFLAGS 	:= -Wall -Wextra
LDFLAGS 	:= 
BUILD		:= ./build
OBJ_DIR 	:= $(BUILD)/objects
APP_DIR		:= $(BUILD)/apps
SRC_DIR		:= ./src
TARGET		:= basAlt
LIBS		:= -Ilibs/
SRC 		:= \
	$(wildcard $(SRC_DIR)/*.cpp)
OBJECTS 	:= $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

all: build $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(SRC_DIR)/%.hpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(LIBS) -c $< -o $@ $(LDFLAGS)

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -o $(APP_DIR)/$(TARGET) $^ $(LDFLAGS)

.PHONY: all build clean debug release

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

debug: CXXFLAGS += -DDEBUG -ggdb
debug: all

release: CXXFLAGS += -O3
release: all

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(APP_DIR)/*
