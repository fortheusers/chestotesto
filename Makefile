APP_TITLE	:= Chesto Testo
APP_AUTHOR 	:= Compucat

SOURCES		+=	.

APP_VERSION	:=	0.0.3
CFLAGS += -Wall -Wextra -Werror

# if you remove these two lines, MainScreen won't fetch images over the network
# (it will instead use the local fallback images, see Chesto's README for more)
CFLAGS		+=	-DNETWORK
LDFLAGS		+=  -lcurl

include libs/chesto/Makefile
