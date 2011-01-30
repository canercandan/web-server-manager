### Makefile --- 
## 
## Filename: Makefile
## Description: 
## Author: Caner Candan
## Maintainer: 
## Created: Mon Feb  2 17:07:05 2009 (+0200)
## Version: 
## Last-Updated: Wed Mar  4 11:04:46 2009 (+0200)
##           By: Caner Candan
##     Update #: 18
## URL: 
## Keywords: 
## Compatibility: 
## 
######################################################################
## 
### Commentary: 
## 
## 
## 
######################################################################
## 
### Change log:
## 
## 
######################################################################
## 
## This program is free software; you can redistribute it and/or
## modify it under the terms of the GNU General Public License as
## published by the Free Software Foundation; either version 3, or
## (at your option) any later version.
## 
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
## General Public License for more details.
## 
## You should have received a copy of the GNU General Public License
## along with this program; see the file COPYING.  If not, write to
## the Free Software Foundation, Inc., 51 Franklin Street, Fifth
## Floor, Boston, MA 02110-1301, USA.
## 
######################################################################
## 
### Code:

PATTERN		=	webserver

PATH_BIN	=	bin
PATH_SRC	=	src
PATH_INCLUDE	=	include
PATH_LIBRARY	=	lib
PATH_TAR	=	tar

FILE_README	=	README
FILE_COPYRIGHT	=	COPYRIGHT
FILE_VERSION	=	VERSION

NAME		=	$(PATH_BIN)/$(PATTERN)

DOCS		=	\
			$(FILE_README)		\
			$(FILE_COPYRIGHT)	\
			$(FILE_VERSION)

HEADERS		=	\
			$(PATH_INCLUDE)/$(PATTERN).h	\
			$(PATH_INCLUDE)/loadmod.h	\
			$(PATH_INCLUDE)/select.h	\
			$(PATH_INCLUDE)/list.h

SRCS		=	\
			$(PATH_SRC)/main.c			\
			$(PATH_SRC)/recv_callback.c		\
			$(PATH_SRC)/addclient_callback.c	\
			$(PATH_SRC)/delclient_callback.c

OBJS		=	$(SRCS:.c=.o)

CC		=	gcc
RM		=	rm -f
RMDIR		=	rmdir
MKDIR		=	mkdir -p
TAR		=	tar -czf
CAT		=	cat
TOUCH		=	touch
BC		=	bc
MV		=	mv
ECHO		=	echo
ECHOE		=	$(ECHO) -e
ECHON		=	$(ECHO) -n

SUCCESS		=	$(ECHOE) "[\033[32mSUCCESS\033[0m] "
FAILED		=	$(ECHOE) "[\033[31mFAILED\033[0m] "

INCLUDES	+=	-I$(PATH_INCLUDE)
LIBRARIES	+=	-L$(PATH_LIBRARY) -lloadmod -lselect -llist

DEBUG_TRUE	=	-g -DDEBUG
COMPAT		+=	-D__BSD_VISIBLE
WARNINGS	+=	-W -Wall -Werror

CFLAGS		+=	$(INCLUDES) $(DEBUG_$(DEBUG)) $(COMPAT) $(WARNINGS)
LDFLAGS		+=	$(LIBRARIES)

.SUFFIXES	:	.c.o

$(NAME)		:	$(OBJS)
			-@$(ECHON) "*** Making directory $(PATH_BIN) "
			-@$(MKDIR) $(PATH_BIN) && $(SUCCESS) || $(FAILED)
			-@$(ECHON) "*** Compiling $(OBJS) to $@ "
			-@$(CC) -o $@ $(OBJS) $(LDFLAGS) && $(SUCCESS) || $(FAILED)

all		:	$(NAME)
			-@make -C modules/apache22
			-@make -C modules/auth
			-@make -C modules/logger
			-@make -C modules/proftpd
			-@make -C modules/mysqld

clean		:
			-@$(ECHON) "*** Removing $(PATH_SRC)/*~ "
			-@$(RM) $(PATH_SRC)/*~ && $(SUCCESS) || $(FAILED)
			-@$(ECHON) "*** Removing $(PATH_SRC)/*.o "
			-@$(RM) $(PATH_SRC)/*.o && $(SUCCESS) || $(FAILED)
			-@$(ECHON) "*** Removing $(PATH_BIN)/*.core "
			-@$(RM) $(PATH_BIN)/*.core && $(SUCCESS) || $(FAILED)

fclean		:	clean
			-@$(ECHON) "*** Removing $(NAME) "
			-@$(RM) $(NAME) && $(SUCCESS) || $(FAILED)
			-@$(ECHON) "*** Removing $(PATH_BIN) "
			-@$(RMDIR) $(PATH_BIN) && $(SUCCESS) || $(FAILED)
			-@make fclean -C modules/apache22
			-@make fclean -C modules/auth
			-@make fclean -C modules/logger
			-@make fclean -C modules/proftpd
			-@make fclean -C modules/mysqld

re		:	fclean all

tar		:
			-@$(ECHON) "*** Making directory $(PATH_TAR) "
			-@$(MKDIR) $(PATH_TAR) && $(SUCCESS) || $(FAILED)
			-@$(ECHON) "*** Creating $(DOCS) if not exist "
			-@$(TOUCH) $(DOCS) && $(SUCCESS) || $(FAILED)
			-@$(ECHON) "*** Updating $(FILE_VERSION) step 1/2 "
			-@$(ECHO) "0`$(CAT) $(FILE_VERSION)` + 0.1" | $(BC) > $(FILE_VERSION)_NEW && $(SUCCESS) || $(FAILED)
			-@$(ECHON) "*** Updating $(FILE_VERSION) step 2/2 "
			-@$(MV) $(FILE_VERSION)_NEW $(FILE_VERSION) && $(SUCCESS) || $(FAILED)
			-@$(ECHON) "*** Compressing sources "
			-@$(TAR) $(PATH_TAR)/$(PATTERN)-`$(CAT) $(FILE_VERSION)`.tgz Makefile $(DOCS) $(HEADERS) $(SRCS) && $(SUCCESS) || $(FAILED)
			-@$(ECHO) "*** New version `$(CAT) $(FILE_VERSION)` is available "

.PHONY		:	all clean fclean re tar shared

.c.o		:
			-@$(ECHON) "*** Compiling $< to $@ "
			-@$(CC) $(CFLAGS) -c $< -o $@ && $(SUCCESS) || $(FAILED)

$(PATH_SRC)/main.o	:	\
				$(PATH_SRC)/main.c	\
				$(HEADERS)
				-@$(ECHON) "*** Compiling $(PATH_SRC)/main.c to $@ "
				-@$(CC) $(CFLAGS) -c $(PATH_SRC)/main.c -o $@ && $(SUCCESS) || $(FAILED)

$(PATH_SRC)/recv_callback.o	:	\
				$(PATH_SRC)/recv_callback.c	\
				$(HEADERS)
				-@$(ECHON) "*** Compiling $(PATH_SRC)/recv_callback.c to $@ "
				-@$(CC) $(CFLAGS) -c $(PATH_SRC)/recv_callback.c -o $@ && $(SUCCESS) || $(FAILED)

$(PATH_SRC)/addclient_callback.o	:	\
				$(PATH_SRC)/addclient_callback.c	\
				$(HEADERS)
				-@$(ECHON) "*** Compiling $(PATH_SRC)/addclient_callback.c to $@ "
				-@$(CC) $(CFLAGS) -c $(PATH_SRC)/addclient_callback.c -o $@ && $(SUCCESS) || $(FAILED)

$(PATH_SRC)/delclient_callback.o	:	\
				$(PATH_SRC)/delclient_callback.c	\
				$(HEADERS)
				-@$(ECHON) "*** Compiling $(PATH_SRC)/delclient_callback.c to $@ "
				-@$(CC) $(CFLAGS) -c $(PATH_SRC)/delclient_callback.c -o $@ && $(SUCCESS) || $(FAILED)

######################################################################
### Makefile ends here
