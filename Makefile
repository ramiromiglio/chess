BUILD_DIR := build
SOURCE_DIR := src
SOURCES := $(wildcard $(SOURCE_DIR)/*.cpp)
OBJECTS := $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(notdir $(SOURCES)))
DEPENDS := $(patsubst %.cpp, $(BUILD_DIR)/%.d, $(notdir $(SOURCES)))
BIN := main.exe
CXX := C:/cygwin64/bin/g++.exe
CXX_FLAGS := \
	-std=c++17 -Iinclude -Isrc -Wall -Wextra -O0 -ggdb -w -Wl,-subsystem,console \

LNK_FLAGS := \
	-Llib \
	-lcygwin \
	-lSDL2main \
	-lSDL2 \
	-lSDL2_image \
	-lSDL2_net \
	-lncurses \

colorize = \e[0;32m$(1)\e[m

all: $(BIN)

-include $(DEPENDS)

$(BIN): $(OBJECTS)
	@$(CXX) $^ $(LNK_FLAGS) -o $(BIN)
	@echo -e "\nBinary constructed as $(call colorize, $(notdir $@))"

$(OBJECTS): $(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	@echo -e "Compiling $(call colorize, $(notdir $<)).."
	@$(CXX) $(CXX_FLAGS) -MMD -MP -c -o $@ $<

.PHONY: clean

clean:
	@rm -f $(BIN) $(OBJECTS) $(DEPENDS)
#	@if [ -d $(BUILD_DIR) ] && [ -z "$$(ls -A $(BUILD_DIR))" ]; then rm -rf $(BUILD_DIR); fi