#
# Makefile para mingw32-make no Windows
#

# cc and flags
CC = g++
CXXFLAGS = -std=c++20 -g -Wall -Wextra -Wpedantic -Wformat-security -Wconversion -Werror

# folders
INCLUDE_FOLDER = ./include/
OBJ_FOLDER = ./obj/
SRC_FOLDER = ./src/
INPUT_FOLDER = ./input/
OUTPUT_FOLDER = ./output/

# files
TARGET = tp2.exe
SRC = $(wildcard $(SRC_FOLDER)*.cpp)
OBJ = $(patsubst $(SRC_FOLDER)%.cpp, $(OBJ_FOLDER)%.o, $(SRC))
INPUT_FILES = $(wildcard $(INPUT_FOLDER)*.txt)
OUTPUT_FILES = $(patsubst $(INPUT_FOLDER)%.txt, $(OUTPUT_FOLDER)%.txt, $(INPUT_FILES))

# compile source files
$(OBJ_FOLDER)%.o: $(SRC_FOLDER)%.cpp
	@if not exist $(OBJ_FOLDER) mkdir $(OBJ_FOLDER)
	$(CC) $(CXXFLAGS) -c $< -o $@ -I$(INCLUDE_FOLDER)

# link objects and generate executable
all: $(OBJ)
	@if not "$(OBJ)" == "" $(CC) $(CXXFLAGS) -o $(TARGET) $(OBJ)

# run the executable with input files and generate output
run: all
	@if not exist $(OUTPUT_FOLDER) mkdir $(OUTPUT_FOLDER)
	@for %%I in ($(INPUT_FILES)) do ( \
		echo Processando %%I... && \
		$(TARGET) < %%I > $(OUTPUT_FOLDER)%%~nI.txt \
	)

# clean build files and outputs
clean:
	@if exist $(OBJ_FOLDER) rd /s /q $(OBJ_FOLDER)
	@if exist $(OUTPUT_FOLDER) rd /s /q $(OUTPUT_FOLDER)
	@if exist $(TARGET) del $(TARGET)
