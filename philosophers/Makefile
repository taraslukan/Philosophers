# Nome dell'eseguibile
NAME = philosophers

# Compilatore e flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude

# File sorgenti e oggetto
SRCS = src/main.c src/routin.c src/utils.c src/monitoring.c src/start.c
OBJS = $(SRCS:src/%.c=obj/%.o)

# Regola principale
all: $(NAME)

# Regola per creare l'eseguibile
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

# Regola per creare i file oggetto
obj/%.o: src/%.c | obj
	$(CC) $(CFLAGS) -c $< -o $@

# Regola per creare la directory dei file oggetto
obj:
	mkdir -p obj

# Pulizia dei file oggetto
clean:
	rm -rf obj

# Pulizia completa (incluso l'eseguibile)
fclean: clean
	rm -f $(NAME)

# Ricompilazione completa
re: fclean all

# Dichiarazione delle regole "phony"
.PHONY: all clean fclean re
