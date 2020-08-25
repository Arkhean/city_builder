CC = g++
CFLAGS = -Wall -g -O0
EXEC_NAME = main
LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf
OBJ_FILES = $(BUILD_DIR)/main.o $(BUILD_DIR)/map.o $(BUILD_DIR)/timer.o $(BUILD_DIR)/building.o $(BUILD_DIR)/screen.o $(BUILD_DIR)/sprite.o $(BUILD_DIR)/menu.o $(BUILD_DIR)/interactions.o
INSTALL_DIR = install/
BUILD_DIR = build
SRC_DIR = src

all : $(EXEC_NAME)

clean :
	rm $(EXEC_NAME) $(OBJ_FILES)

$(EXEC_NAME) : $(OBJ_FILES)
	$(CC) -o $(EXEC_NAME) $(OBJ_FILES) $(LIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

install :
	cp $(EXEC_NAME) $(INSTALL_DIR)
