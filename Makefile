
# --> PROGRAM --------------------------------------------------------------------

# ~~~~~~~~~~~~~~~~ SOURCES ~~~~~~~~~~~~~~~~

NAME = minishell
SRCS        	=	main.c \
					parsingutils.c \
					parsing_utils2.c \
					parsing_word.c \
					parsingcalcul.c \
					parsing.c \
					struct_initialisation.c \
					env.c \
					env_functions.c \
					builtin.c \
					execution.c \
					exec_utils.c \
					cd.c \
					unset.c \
					export.c \
					export_utils.c \
					echo.c \
					pwd.c \
					handler.c \
					exit.c



# SRC_PATH = src/
SRCS_PATH    	=    src

# ~~~~~~~~~~~~~~~~ OBJECTS ~~~~~~~~~~~~~~~~

#OBJ_PATH = obj/
OBJS_PATH    	=    objs

OBJS        	=    $(addprefix $(OBJS_PATH)/, $(SRCS:.c=.o))
# ~~~~~~~~~~~~~~~~ INCLUDES ~~~~~~~~~~~~~~~~

INCLUDES= minishell.h
INCLUDES_PATH = includes

# # --> COMPILER AND FLAGS ---------------------------------------------------------

CC				= cc

FLAGS			= -Wall -Wextra -Werror -I./$(INCLUDES_PATH)
#  FLAGS			+= -fsanitize=address -g3


# # --> LIBFT ----------------------------------------------------------------------

LIBFT			= libft
LIBRARY			= -L $(LIBFT) -lft -lreadline -L ./readline/lib -I ./readline/include -lncurses
LIBFT_LIBRARY	= libft/libft.a

# # --> TEST MODULE ----------------------------------------------------------------

# # --> RULES ----------------------------------------------------------------------

all:   header lib $(NAME)

# ~~~~~~~~~~~~ COMPILING IN .o ~~~~~~~~~~~~

objs/%.o:	$(SRCS_PATH)/%.c $(INCLUDES_PATH)/$(INCLUDES) $(LIBFT_LIBRARY) Makefile
	mkdir -p $(dir $@);
	printf "%-62b%b" "$(CYAN)$(BOLD)compiling $(END)$<"
	$(CC) $(FLAGS) -c $< -o $@
	printf "$(GREEN)[✓]$(END)\n"

# ~~~~~~~ COMPILING THE EXECUTABLE ~~~~~~~~

$(NAME):	$(OBJS)
	cp .inputrc ~/
	printf "%-63b%b" "\n$(BOLD)$(GREEN)creating$(END) $@"
	$(CC) $(FLAGS) $(OBJS)  $(LIBRARY) -o $(NAME)
	printf "$(GREEN)[✓]$(END)\n\n\n"

# ~~~~~~~~~~ COMPILING THE LIBFT ~~~~~~~~~~

lib:
	printf "%-62b%b" "$(BOLD)$(PURPLE)compiling$(END) the $(LIBFT)"
	$(MAKE) --no-print-directory -C $(LIBFT)
	printf "$(GREEN)[✓]$(END) \n\n\n"


# ~~~~~~~~~~~~ CLEANNING RULES ~~~~~~~~~~~~

clean:
	rm -rf $(OBJS_PATH)
	make clean --no-print-directory -C $(LIBFT)

fclean: clean
	rm -f $(NAME)
	make fclean --no-print-directory -C $(LIBFT)

# ~~~~~~~~~~~~~~ REMAKE RULE ~~~~~~~~~~~~~~
re: fclean all

# --> HEADER ---------------------------------------------------------------------

header :
	@printf "                                    __               ___    ___        \n"
	@printf " _______   __          __          /\ \             /\_ \  /\_ \      \n" 
	@printf "/\       \/\_\    ___ /\_\    ____ \ \ \___      __ \//\ \ \//\ \     \n" 
	@printf "\ \ \___\ \/\ \ /' _ '\/\ \  /',__\ \ \  _ '\  /'__'\ \ \ \  \ \ \    \n" 
	@printf " \ \ \__/\ \ \ \/\ \/\ \ \ \/\__, '\ \ \ \ \ \/\  __/  \_\ \_ \_\ \_  \n" 
	@printf "  \ \_\ \ \_\ \_\ \_\ \_\ \_\/\____/  \ \_\ \_\ \____\ /\____\/\____\ \n" 
	@printf "   \/_/  \/_/\/_/\/_/\/_/\/_/\/___/    \/_/\/_/\/____/ \/____/\/____/ \n" 
	@printf "\n\n"

# --> COLOR ----------------------------------------------------------------------


BLACK		:= ""
RED			:= ""
GREEN		:= ""
YELLOW		:= ""
BLUE		:= ""
PURPLE		:= ""
CYAN		:= ""
WHITE		:= ""
END			:= ""
UNDER		:= ""
BOLD		:= ""
rev			:= ""
END			:= ""

ifneq (,$(findstring 256color, ${TERM}))
	BLACK		:= $(shell tput -Txterm setaf 0)
	RED			:= $(shell tput -Txterm setaf 1)
	GREEN		:= $(shell tput -Txterm setaf 2)
	YELLOW		:= $(shell tput -Txterm setaf 3)
	BLUE		:= $(shell tput -Txterm setaf 4)
	PURPLE		:= $(shell tput -Txterm setaf 5)
	CYAN		:= $(shell tput -Txterm setaf 6)
	WHITE		:= $(shell tput -Txterm setaf 7)
	END			:= $(shell tput -Txterm sgr0)
	UNDER		:= $(shell tput -Txterm smul)
 	BOLD		:= $(shell tput -Txterm bold)
	rev			:= $(shell tput -Txterm rev)
endif

.PHONY: all clean fclean re
.SILENT:
