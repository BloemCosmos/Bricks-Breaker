SRC_DIR := src
BIN_DIR := bin

# Rutas de SFML
SFML_INCLUDE := C:/Users/danie/Desktop/SFML-2.6.2/include
SFML_LIB := C:/Users/danie/Desktop/SFML-2.6.2/lib

# Bibliotecas de SFML
SFML := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

CPP_FILES := $(wildcard $(SRC_DIR)/*.cpp)
EXE_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%.exe,$(CPP_FILES))

$(BIN_DIR)/%.exe: $(SRC_DIR)/%.cpp $(wildcard include/*.hpp) | $(BIN_DIR)
	g++ $< -o $@ $(SFML) -I$(SFML_INCLUDE) -L$(SFML_LIB) -Iinclude

$(BIN_DIR):
	mkdir $(BIN_DIR)

# Nombre del compilador
CXX = g++

# Flags del compilador
CXXFLAGS = -I./sfml -std=c++11

# Librerías de SFML
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Archivos fuente
SRCS = main.cpp

# Archivo objeto
OBJS = $(SRCS:.cpp=.o)

# Nombre del ejecutable
TARGET = arcanoid

# Regla por defecto
all: $(TARGET)

# Regla para compilar el ejecutable
$(TARGET): $(OBJS)
    $(CXX) $(OBJS) -o $(TARGET) $(LIBS)

# Regla para compilar los archivos objeto
%.o: %.cpp
    $(CXX) $(CXXFLAGS) -c $< -o $@

# Regla para limpiar los archivos generados
clean:
    rm -f $(OBJS) $(TARGET)

all: $(EXE_FILES)

run%: $(BIN_DIR)/%.exe
	./$<

clean:
	rm -f $(BIN_DIR)/*.exe

.PHONY: all clean run%