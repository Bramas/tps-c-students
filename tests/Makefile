CC := gcc
CFLAGS ?= -Wall
LDLIBS ?= -lm

CFLAGS :=  -ggdb3 -std=c11 -Wall -Werror -Wextra -Wno-sign-compare -Wshadow -O0 -fprofile-arcs --coverage

INCLUDE_PATH = ../include

TARGET   = tests

SRCDIR   = ../src
OBJDIR   = ../obj
BINDIR   = ../bin

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(INCLUDE_PATH)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

OBJECTS := $(filter-out $(OBJDIR)/students.o,$(OBJECTS))

$(TARGET): $(OBJECTS) $(OBJDIR)/tests.o
	mkdir -p $(BINDIR)
	$(CC) -o $@ $^ $(CFLAGS) $(LDLIBS)
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INCLUDE_PATH)

$(OBJDIR)/tests.o: tests.c
	mkdir -p $(OBJDIR)
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INCLUDE_PATH)


.PHONY: clean
clean:
	rm -rf ../obj/*.o
	rm -f ../bin/tests