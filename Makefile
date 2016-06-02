#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2016/05/17 16:07:18 by fpasquer          #+#    #+#             *#
#*   Updated: 2016/05/22 19:17:01 by fpasquer         ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#



NAME 		= corewar
FLAGS		= -Wall -Werror -Wextra -g
SRC 		= main.c util.c init_vm.c virtual_machin.c print_info.c save_player.c

OTHERS		= libft Makefile auteur minilibx_macos exemple

OBJ			= $(SRC:.c=.o)
INC			= virtual_machine.h
LIBFLAGS	= -L./libft/ -lft -lncurses
SRCDIR		= ./srcs/
OBJDIR		= ./objs/
INCDIRLIB	= ./libft/incs/
INCDIR		= ./incs/
SRCS		= $(addprefix $(SRCDIR), $(SRC))
OBJS		= $(addprefix $(OBJDIR), $(OBJ))
DATE		= `date +'%d/%m/%y %H:%M:%S'`
.SILENT:

all : 		$(NAME)

$(NAME) :
	echo "\\033[1;31mCompilation with -Wall -Wextra -Werror...\\033[0;39m"
	echo "\\033[1;34mGenerating objects... Please wait.\\033[0;39m"
	Make -C libft/
	gcc $(FLAGS) -c $(SRCS) -I $(INCDIR) -I $(INCDIRLIB)
	echo "compiling $(NAME)..."
	mkdir -p $(OBJDIR)
	mv $(OBJ) $(OBJDIR)
#	gcc $(FLAGS) -o $(NAME) -I /usr/X11/include -g -L/usr/X11/lib -lX11 -lmlx -lXext -framework OpenGL -framework AppKit $(OBJS) $(LIBFLAGS)
	gcc $(FLAGS) -o $(NAME) $(OBJS) $(LIBFLAGS)
	echo "$(NAME) has been created !"

.PHONY:		clean fclean re push exe

clean :
			Make -C ./libft/ clear
			rm -rf $(OBJS)
			rm -rf $(OBJDIR)
			echo "objects files has been removed !"

fclean :	clean
			Make -C ./libft/ fclear
			rm -rf $(NAME)
			echo "$(NAME) has been removed !"

re		:	fclean all

exe		:	re
	./$(NAME) 

push	:	fclean
			git add $(SRCDIR) $(INCDIR) $(OTHERS) ./libft
			git commit -m "$(DATE)"
#			echo "Enter Your Commit : "
#			read root_path ; git commit -m "$$root_path"
			git push
