APP_TITLE	:= Chesto Testo
APP_AUTHOR 	:= Compucat

SOURCES		+=	.

APP_VERSION	:=	0.0.3
CFLAGS += -Wall -Wextra -Werror

# if you remove these two lines, the fallback icon image will be used instead
CFLAGS		+=	-DNETWORK
LDFLAGS		+=  -lcurl

include libs/chesto/Makefile
