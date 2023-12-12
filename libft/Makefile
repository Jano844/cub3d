NAME				=	libft.a

FLAGS				=	-Wall -Wextra -Werror

COMPILE				=	cc

COLOR_RESET			=	\033[0m
COLOR_CYAN			=	\033[36m
COLOR_GREEN			=	\033[32m
COLOR_RED			=	\033[31m

SRC_F				=	srcs/

OBJ_F				=	objs/

SRCS				=	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_toupper.c ft_tolower.c ft_atoi.c ft_memset.c \
						ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c \
						ft_strnstr.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
						ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_strcmp.c

SRCS_BONUS			=	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
						ft_lstmap.c

SRCS_PRINTF			=	ft_printf.c ft_helper_csi.c ft_helper_hex.c ft_uitoa.c

SRCS_GET_NEXT_LINE	=	ft_get_next_line.c ft_get_next_line_utils.c

OBJS				=	$(addprefix $(OBJ_F),$(SRCS:%.c=%.o)) \
						$(addprefix $(OBJ_F),$(SRCS_BONUS:%.c=%.o)) \
						$(addprefix $(OBJ_F),$(SRCS_PRINTF:%.c=%.o)) \
						$(addprefix $(OBJ_F),$(SRCS_GET_NEXT_LINE:%.c=%.o))

all: 				$(NAME)

$(NAME): 			$(OBJS)
					@ar rcs $(NAME) $(OBJS)
					@echo "$(COLOR_CYAN)Kompilierung abgeschlossen: $(NAME)$(COLOR_RESET)"

$(OBJ_F)%.o:		$(SRC_F)%.c
					@mkdir -p $(OBJ_F)
					@$(COMPILE) $(FLAGS) -c $< -o $@
					@echo "$(COLOR_GREEN)Kompilierung abgeschlossen: $@$(COLOR_RESET)"

clean:
					@rm -rf $(OBJ_F)

fclean: 			clean
					@rm -f $(NAME)
					@rm -rf $(OBJ_F)

re: 				fclean all
