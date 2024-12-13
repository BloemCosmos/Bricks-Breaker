# Directorios de Origen y Destino
SrcDir := src
BinDir := bin

Sfml := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Obtener Todos Los Archivos .cpp en el Directorio de Origen
CppFiles := $(wildcard $(SrcDir)/*.cpp)

# Generar Los Nombres de Los Archivos .exe en el Directorio de Destino
ExeFiles := $(patsubst $(SrcDir)/%.cpp,$(BinDir)/%.exe,$(CppFiles))

# Regla Para Compilar Cada Archivo .cpp y Generar el Archivo .exe Correspondiente
$(BinDir)/%.exe: $(SrcDir)/%.cpp $(wildcard include/*.hpp)
	g++ $< -o $@ $(Sfml) -Iinclude

# Regla Por Defecto Para Compilar Todos Los Archivos .cpp
All: $(ExeFiles)

# Regla Para Ejecutar Cada Archivo .exe
Run%: $(BinDir)/%.exe
	./$<

# Regla Para Limpiar Los Archivos Generados
Clean:
	rm -f $(ExeFiles)

.PHONY: All Clean
.PHONY: Run-%     #