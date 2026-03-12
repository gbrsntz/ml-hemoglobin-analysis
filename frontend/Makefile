# Makefile para compilação do Frontend C
# Sistema MED IA - Análise de Hemograma

# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -Wextra -std=c99 -O2

# Flags de linkagem (Windows)
LDFLAGS_WIN = -lraylib -lopengl32 -lgdi32 -lwinmm -lws2_32

# Diretórios
SRC_DIR = src
BUILD_DIR = build

# Nome do executável
TARGET = hemograma_app

# Arquivos fonte
SOURCES = $(SRC_DIR)/main.c \
          $(SRC_DIR)/ui.c \
		  $(SRC_DIR)/gui.c \
          $(SRC_DIR)/communication.c \
          $(SRC_DIR)/validators.c

# Arquivos objeto
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))

# Detecta sistema operacional
ifeq ($(OS),Windows_NT)
    TARGET_EXT = .exe
    LDFLAGS = $(LDFLAGS_WIN)
    MKDIR = if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
    RM = del /Q
    RMDIR = rmdir /S /Q
else
    TARGET_EXT =
    LDFLAGS =
    MKDIR = mkdir -p $(BUILD_DIR)
    RM = rm -f
    RMDIR = rm -rf
endif

# Alvo padrão
all: $(BUILD_DIR) $(TARGET)$(TARGET_EXT)

# Cria diretório de build
$(BUILD_DIR):
	$(MKDIR)

# Compila o executável
$(TARGET)$(TARGET_EXT): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@echo Compilacao concluida: $(TARGET)$(TARGET_EXT)

# Compila arquivos objeto
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Limpa arquivos compilados
clean:
	$(RM) $(BUILD_DIR)\*.o 2>nul || true
	$(RM) $(TARGET)$(TARGET_EXT) 2>nul || true

# Limpa tudo
cleanall: clean
	$(RMDIR) $(BUILD_DIR) 2>nul || true

# Recompila tudo
rebuild: clean all

# Executa o programa
run: all
	./$(TARGET)$(TARGET_EXT)

# Mostra ajuda
help:
	@echo Comandos disponiveis:
	@echo   make        - Compila o projeto
	@echo   make clean  - Remove arquivos compilados
	@echo   make rebuild - Recompila tudo
	@echo   make run    - Compila e executa
	@echo   make help   - Mostra esta ajuda

.PHONY: all clean cleanall rebuild run help
