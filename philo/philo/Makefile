NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread -g
SRCS = philo.c\
		philo_utils.c\
		philo_utils2.c\
		philo_routine.c\

OBJ = ${SRCS:.c=.o}

all : ${NAME}

%.o:%.c
	@cc ${CFLAGS} -c $< -o $@
	@echo "$@ \r\t\t\t is compiled"

${NAME} : ${OBJ}
	@cc ${CFLAGS} ${OBJ} -o ${NAME}

clean :
	@rm -f ${OBJ}
	@echo object files deleted !

fclean : clean
	@rm -f ${NAME}
	@echo program file deleted !

re : fclean all

.PHONY : fclean clean all re