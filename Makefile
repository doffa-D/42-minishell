# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/03 12:19:16 by nouakhro          #+#    #+#              #
#    Updated: 2023/05/09 15:20:59 by nouakhro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(DEBUG),1)
	OPTS = -fsanitize=address -g
endif

CC = cc

CCFLAGS = -Wall -Werror -Wextra $(OPTS)

SRC =   main.c                          \
	builtins/builtins_in_chiled.c\
	builtins/builtins_in_parent.c\
	builtins/builtins_is_exist.c\
	builtins/bultins_execut_in_parent.c\
	commande/cd_commande.c\
	commande/commande.c\
	commande/echo_command.c\
	commande/env_commd.c\
	commande/exit.c\
	commande/export_command.c\
	commande/partition_commande_by_commande.c\
	commande/pwd_command.c\
	commande/split_commande_rederaction.c\
	commande/unset_command.c\
	excution/calculate_how_many_rederaction_input.c\
	excution/calculate_how_many_rederaction_output.c\
	excution/check_rediraction.c\
	excution/close_and_free.c\
	excution/environment_creat_linked_list.c\
	excution/excution_errors.c\
	excution/get_enviroment.c\
	excution/init_and_rediraction_is_exist.c\
	excution/manage_pipe_and_rederaction.c\
	excution/path_is_exist_or_not.c\
	excution/pipe_is_exist_or_its_not_builtins.c\
	excution/readline_return_somthing.c\
	excution/split_each_argemnt_whithout_parccing.c\
	excution/split_path.c\
	excution/syntax_error.c\
	expande/expand_exit_status_and_some_caracters_after_dolar.c\
	expande/expande_varbles.c\
	expande/manage_expand_variables.c\
	expande/parccing_expande_variabls_in_commande.c\
	parccing/her_doc_manipulate.c\
	parccing/parccen.c\
	parccing/parccing_part_remve_double_and_single_quotes.c\
	parccing/parccing_rederaction_input_part.c\
	parccing/parccing_rediraction_output_part.c\
	parccing/parccing_represent_pipe_and_rediraction.c\
	parccing/parccing_utils.c\
	parccing/parccing_whith_just_represent.c\
	parccing/remove_quotes_in_rederaction_parccing_part.c\
	utils/utils.c\
	utils/utils_cd_command.c\
	utils/utils_check_rediractions_chiled.c\
	utils/utils_check_rediractions_parent.c\
	utils/utils_check_rediractions_parent_2.c\
	utils/utils_exit_commande.c\
	utils/utils_export_command_1.c\
	utils/utils_export_command_2.c\
	utils/utils_export_command_3.c\

OBJ_DIR = object   

OBJE = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))   

NAME = minishell

LIBFT = libft

# all : $(NAME)

# $(NAME) : $(OBJE)
# 	make -C $(LIBFT)
# 	$(CC) $(CCFLAGS) $(OBJE) libft/libft.a -lreadline  -o $(NAME)

# $(OBJ_DIR)/%.o : %.c
# 	$(CC) $(CCFLAGS) -c $< -o $@

# clean :
# 	rm -f $(OBJE)
# 	make clean -C $(LIBFT)

# fclean : clean
# 	make fclean -C $(LIBFT)
# 	rm -f $(NAME)

# re:fclean $(NAME)

# run : all
# 	mv $(OBJE) object && ./minishell

CC = cc
CCFLAGS = -Wall -Wextra

SRC_DIR = expande
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
