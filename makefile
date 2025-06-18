# Nome do executável
TARGET = fifers

# Nome dos arquivos fonte
SRC = snakegame.c lista.c recorde.c main.c

# Diretório de build
BUILD_DIR = build

# Gerar a lista de objetos dentro de build/
OBJ = $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRC))

# Flags para o compilador
CFLAGS = -Wall -lncurses

# Regra padrão
all: $(TARGET)

# Compilar o executável com objetos dentro de build/
$(TARGET): $(OBJ)
	gcc -o $@ $(OBJ) $(CFLAGS)

# Compilar cada .c em build/.o
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(BUILD_DIR)
	gcc -c $< -o $@ -MMD -MF $(BUILD_DIR)/$*.d

# Limpar tudo
clean:
	rm -f $(TARGET) $(BUILD_DIR)/*.o $(BUILD_DIR)/*.d

# Incluir dependências automaticamente
-include $(SRC:.c=.d)
-include $(patsubst %.c,$(BUILD_DIR)/%.d,$(SRC))
