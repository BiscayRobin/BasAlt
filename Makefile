CXX 		:= clang++
CXXFLAGS 	:= -pedantic-errors -Wall -Wextra -Werror
LDFLAGS 	:=
BUILD		:= ./build
OBJ_DIR 	:= $(BUILD)/objects
APP_DIR		:= $(BUILD)/apps
TARGET		:= basAlt
INCLUDE		:= -Iinclude/
LIBS		:= -Ilibs/
SRC 		:= \
	$(wildcard src/*.cpp)

OBJECTS 	:= $(SRC:%.cpp=$(OBJ_DIR)/%.o)

all: build $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(LIBS) $(INCLUDE) -c $< -o $@ $(LDFLAGS)

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -o $(APP_DIR)/$(TARGET) $^ $(LDFLAGS)

.PHONY: all build clean debug release

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

debug: CXXFLAGS += -DDEBUG -g
debug: all

release: CXXFLAGS += -O2
release: all

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(APP_DIR)/*
