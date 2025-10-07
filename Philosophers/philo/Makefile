# Compiler and options
CC = cc
CFLAGS = -Wall -Wextra -Werror
# -MMD -MP -fsanitize=address,undefined -g

# Directories
SRC_DIR = srcs
PHILO_DIR = philo
OBJ_DIR = obj
INC_DIR = inc

# Source files for the main program
MAIN_SRC_FILES = $(SRC_DIR)/main.c $(SRC_DIR)/utils.c
MAIN_OBJ_FILES = $(MAIN_SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Source files for philo
PHILO_SRC_FILES = $(SRC_DIR)/init.c $(SRC_DIR)/routine.c $(SRC_DIR)/actions.c $(SRC_DIR)/memory.c $(SRC_DIR)/start.c $(SRC_DIR)/monitoring.c $(SRC_DIR)/forks.c $(SRC_DIR)/is_finished.c
PHILO_OBJ_FILES = $(PHILO_SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/philo/%.o)

# Default rule
all: philo

# Compilation rules for object files with dependency generation
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)/$(dir $@)  # Ensure obj directory structure
	$(CC) $(CFLAGS) -I$(INC_DIR) -o $@ -c $<

$(OBJ_DIR)/philo/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)/philo  # Ensure philo directory structure under obj
	$(CC) $(CFLAGS) -I$(INC_DIR) -o $@ -c $<

# Compilation rule for the program
philo: $(MAIN_OBJ_FILES) $(PHILO_OBJ_FILES)
	$(CC) $(CFLAGS) -o philo $(MAIN_OBJ_FILES) $(PHILO_OBJ_FILES) -lpthread

# Clean rule for object files
clean:
	rm -rf $(OBJ_DIR)

# Full clean rule
fclean: clean
	rm -f philo

# Full rebuild rule
re: fclean all

# Include dependencies
-include $(MAIN_OBJ_FILES:.o=.d) $(PHILO_OBJ_FILES:.o=.d)

# Phony targets
.PHONY: all clean fclean re
