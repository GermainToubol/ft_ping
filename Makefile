#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/13 19:14:11 by gtoubol           #+#    #+#              #
#    Updated: 2023/02/13 19:14:11 by gtoubol          ###   ########.fr        #
#                                                                              #
#******************************************************************************#
NAME		= ft_ping

# List of all inclusions (.h and .a)
# -------------------------------------------------------------------------
INCLUDE_DIR	= includes libft/includes
INCLUDES	= $(addprefix -I,$(INCLUDE_DIR))

LIB_NAMES	= ft
LIB_FILES	= $(foreach l,$(LIB_NAMES),lib$l/lib$l.a)
EXT_LIB		= m
LIB			= $(addprefix -Llib,$(LIB_NAMES)) $(addprefix -l,$(LIB_NAMES) $(EXT_LIB))

# List of all sources (.c)
# -------------------------------------------------------------------------
SRC_DIR		= srcs
SRC_LST		= main.c ft_clock.c ft_init.c ft_loop.c ft_close.c				\
				$(addprefix socket/,ft_init_socket.c ft_resolve_socket.c	\
					ft_clean_socket.c ft_options_socket.c)					\
				$(addprefix packet/,ft_init_packet.c ft_mark_packet.c		\
					ft_send_packet.c ft_receive_packet.c 					\
					ft_isvalid_ip_packet.c ft_analyse_packet.c				\
					ft_packet_handler.c)									\
				$(addprefix utils/,ft_swap_16bits.c ft_checksum.c 			\
					ft_getdelay.c)											\
				$(addprefix statistics/,ft_statistics.c)					\
				$(addprefix options/,ft_parseopts.c ft_optusage.c			\
					ft_optflood.c ft_optcount.c ft_optmark.c ft_optpreload.c\
					ft_optinterval.c)

# List of all object files (.o)
# -------------------------------------------------------------------------
OBJ_DIR		= objs
OBJ_LST		= $(SRC_LST:.c=.o)
OBJS		= $(addprefix $(OBJ_DIR)/,$(OBJ_LST))

DEPS		= $(OBJS:.o=.d)

# Compilation options
# -------------------------------------------------------------------------
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
SHELL		= /bin/bash

# Rules
# -------------------------------------------------------------------------
.PHONY:		all
all:		$(NAME)

$(NAME):	$(LIB_FILES) $(OBJS)
			@echo ""
			@echo -e "$(_BLUE)Linkage $(NAME)$(_NO_COLOR)"
			$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(OBJS) $(LIB)
			sudo setcap cap_net_raw+ep $@

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c start_compiling
			@mkdir -p $(dir $@)
			$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(OBJ_DIR)/%.d: $(SRC_DIR)/%.c start_deps
			@mkdir -p $(dir $@)
			$(CC) -MM -MT $(@:.d=.o) $(CFLAGS) $(INCLUDES) $< > $@

.PHONY:		clean
clean:
			$(RM) $(OBJS)

.PHONY:		dclean
dclean:
			$(RM) $(DEPS)


.PHONY:		fclean
fclean:		clean dclean
			$(RM) $(NAME)
			@rmdir -p --ignore-fail-on-non-empty $(dir $(OBJS)) 2> /dev/null || exit 0

.PHONY: 	watch
watch:		start_watch all
			@while inotifywait -qr --include '(\.(c|h)|Makefile)' -e modify ./srcs ./includes Makefile; do\
				echo -ne "\033[H\033[2J"; \
				make -k all;\
			done

.PHONY:		dev
dev:		fclean
			docker compose up -d

.PHONY:		re
re:			fclean all

# Documentation
# -------------------------------------------------------------------------
.PHONY:		doc
doc:
			@mkdir -p doc
			doxygen Doxyfile

.PHONY:		docclean
docclean:
			rm -rf doc

# Libraries
# -------------------------------------------------------------------------
%.a:		build_libs
			@echo -e "$(_GREEN)$(dir $@): make$(_NO_COLOR)"
			$(MAKE) --no-print-directory -C $(dir $@)

# Parameters
# -------------------------------------------------------------------------
_GREY		= \033[30m
_RED		= \033[31m
_GREEN		= \033[32m
_YELLOW		= \033[33m
_BLUE		= \033[34m
_PURPLE		= \033[35m
_CYAN		= \033[36m
_WHITE		= \033[37m
_NO_COLOR	= \033[0m

.INTERMEDIATE:	start_deps
start_deps:
			@echo -e "$(_GREEN)Build dependencies$(_NO_COLOR)"

.INTERMEDIATE:	build_libs
build_libs:
			@echo ''
			@echo -e "$(_PURPLE)Build libraries$(_NO_COLOR)"

.INTERMEDIATE:	start_compiling
start_compiling:
			@echo ''
			@echo -e "$(_GREEN)Start Compiling $(_NO_COLOR)"

.INTERMEDIATE:	start_link
start_link:
			@echo ""
			@echo -e "$(_BLUE)Linkage $(NAME)$(_NO_COLOR)"

.INTERMEDIATE:	start_watch
start_watch:
			@echo -e "$(_PURPLE)=== Start watch mode ===$(_NO_COLOR)"

-include $(DEPS)
