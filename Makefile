CC ?= gcc
CFLAGS := -std=c99 -pedantic -Wall -Wextra -Wshadow -Werror

TARGET := grandish
PREFIX ?= /usr/local


default: $(TARGET)

$(TARGET):
	$(CC) main.c -o $(TARGET) $(CFLAGS)

.PHONY: install
install:
	chmod 755 $(TARGET)
	mkdir -p $(PREFIX)/bin
	cp -f $(TARGET) $(PREFIX)/bin

.PHONY: uninstall
uninstall:
	rm -f $(PREFIX)/bin/$(TARGET)
