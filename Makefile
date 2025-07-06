# Nome do executável
TARGET = countofwords

# Compilador e flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

# Link com a Boost (apenas se necessário)
LDFLAGS = -lboost_locale

# Diretórios de código-fonte e headers
SRC_DIR := src
INC_DIR := include

# Encontre todos os arquivos .cpp no projeto
CPP_FILES := $(shell find $(SRC_DIR) . -name "*.cpp")
OBJ_FILES := $(CPP_FILES:.cpp=.o)

# Encontre todos os arquivos .hpp (para dependências)
DEP_FILES := $(OBJ_FILES:.o=.d)

# Regra padrão
all: $(TARGET)

# Compilar o executável
$(TARGET): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Compilar cada .cpp em .o com dependência de .hpp
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

# Inclui os arquivos de dependência (.d)
-include $(DEP_FILES)

# Limpa os binários
clean:
	rm -f $(TARGET) $(OBJ_FILES) $(DEP_FILES)

.PHONY: all clean
