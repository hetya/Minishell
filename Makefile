
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
 FLAGS			+= -fsanitize=address 


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
	$(MAKE) -C $(LIBFT)
	printf "$(GREEN)[✓]$(END) \n\n\n"


# ~~~~~~~~~~~~ CLEANNING RULES ~~~~~~~~~~~~

clean:
	rm -rf $(OBJS_PATH)
	make clean -C $(LIBFT)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT)

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

# ~~~~~~~~~~~~~~~ OPEATION ~~~~~~~~~~~~~~~

END=\\x1b[0m
BOLD=\\x1b[1m
UNDER=\\x1b[4m
REV=\\x1b[7m

# ~~~~~~~~~~~~~~~~~ COLORS ~~~~~~~~~~~~~~~~~

GREY=\\x1b[30m
RED=\\x1b[31m
GREEN=\\x1b[32m
YELLOW=\\x1b[33m
BLUE=\\x1b[34m
PURPLE=\\x1b[35m
CYAN=\\x1b[36m
WHITE=\\x1b[37m

# ~~~~~~~~~~~~ BACKGROUND COLORS ~~~~~~~~~~~~

IGREY=\\x1b[40m
IRED=\\x1b[41m
IGREEN=\\x1b[42m
IYELLOW=\\x1b[43m
IBLUE=\\x1b[44m
IPURPLE=\\x1b[45m
ICYAN=\\x1b[46m
IWHITE=\\x1b[47m

.PHONY: all clean fclean re
.SILENT:
