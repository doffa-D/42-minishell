
CC = cc
CCFLAGS = -Wall -Wextra

SRC_DIR = main
OBJ_DIR = object   

SRC = $(wildcard $(SRC_DIR)/*.c)

OBJE = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o, $(SRC))

NAME = program

LDLIBS = 

all: $(NAME)

$(NAME): $(OBJE) 
	$(CC) $(CCFLAGS) $(OBJE) $(LDLIBS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	 $(CC) $(CCFLAGS) -c $< -o $@

clean:
	 rm -f $(OBJE) 
	 rm -f $(NAME)

.PHONY: clean all    