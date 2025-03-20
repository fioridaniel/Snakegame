# Nome do executável
TARGET = fifers

# Nome dos arquivos fonte
SRC = snakegame.c lista.c recorde.c main.c

# Gerar a lista de objetos a partir dos arquivos fonte
OBJ = $(SRC:.c=.o)

# Flags para o compilador
CFLAGS = -lncurses

# Comando padrão que é executado quando você executa 'make'
all: $(TARGET)

# Regra para compilar o jogo
$(TARGET): $(OBJ)
	gcc -o $(TARGET) $(OBJ) $(CFLAGS)

# Regra para compilar os arquivos .c em .o
%.o: %.c
	gcc -c $< -o $@

# Limpeza dos arquivos compilados
clean:
	rm -f $(TARGET) $(OBJ)

# Incluir automaticamente as dependências dos arquivos .h
-include $(SRC:.c=.d)

# Gerar as dependências automaticamente
%.d: %.c
	gcc -MM $< > $@.tmp
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.tmp > $@
	rm -f $@.tmp
