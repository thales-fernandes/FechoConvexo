# Makefile para o projeto TP

# Diretórios
SRC_DIR := src
INCLUDE_DIR := include
OBJ_DIR := obj
BIN_DIR := bin

# Compilador e flags
CXX := g++
#CXXFLAGS := -Wall -Wextra

# Nome do executável
EXEC := $(BIN_DIR)/TP

# Objetos
OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(wildcard $(SRC_DIR)/*.c)) \
        $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(wildcard $(SRC_DIR)/*.cpp)) \
        $(patsubst $(SRC_DIR)/%.cc, $(OBJ_DIR)/%.o, $(wildcard $(SRC_DIR)/*.cc))

# Regra padrão
#all: dirs $(EXEC)
all: $(EXEC)
	$(EXEC) $(fecho) 

# Regra para criar os diretórios necessários
dirs:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)

# Regra para criar o executável
$(EXEC): $(OBJS)
	$(CXX) -o $@ $^

# Regra para compilar os arquivos C
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Regra para compilar os arquivos C++
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Regra para compilar os arquivos C++
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Regra para executar o TP com o arquivo fornecido
#run: $(EXEC)
#	$(EXEC) $(fecho)

# Limpar os arquivos objetos e o executável
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Ignorar regras com nomes de arquivos
.PHONY: all dirs clean run
