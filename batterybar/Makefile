NAME=batterybar
CC=cc
CFLAGS=-std=c99 -Wall -Wextra -O2 -D_GNU_SOURCE
DESTDIR = /usr/local

all: $(NAME)

$(NAME): $(NAME).c config.h
	$(CC) $(CFLAGS) -o $@ $(NAME).c

config.h: config.def.h
	cp config.def.h $@

clean:
	rm -f $(NAME) *.o

install: ${NAME}
	@echo installing executable file to ${DESTDIR}/bin
	@mkdir -p ${DESTDIR}/bin
	@cp -f ${NAME} ${DESTDIR}/bin/${NAME}
	@chmod 755 ${DESTDIR}/bin/${NAME}

.PHONY: all clean
