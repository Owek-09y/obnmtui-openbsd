PROG=	obnmtui
SRCS=	main.c
CFLAGS+=	-Wall -Wextra -O2
LDADD=	-lcurses

.include <bsd.prog.mk>
