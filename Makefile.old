# Makefile

# target config
TARGET		:= libflc
TARGET_SHARED	:= $(TARGET).so
TARGET_STATIC	:= $(TARGET).a

# test programs are compiled in debug mode
TEST_TARGET     :=

# global variables
INSTALL		:= /usr/bin/install
RM              := rm -rf

# compilation variables
CFLAGS		:= -I./include $(CFLAGS) -std=gnu99 -fPIC

CFLAGS		+= -Wall -Wextra -Wbad-function-cast -Wshadow \
                   -Wcast-qual -Wold-style-definition -Wmissing-noreturn \
                   -Wstrict-prototypes -Waggregate-return -Wformat=2 \
                   -Wswitch-default -Wundef -Wbad-function-cast \
                   -Wunused-parameter -Wnonnull

ifdef DEBUG
CFLAGS		+= -g
LDFLAGS		:= -L./ $(LDFLAGS)
TEST_TARGET	+= $(foreach testfile, $(wildcard tests/*.c), flct_$(notdir $(basename $(testfile))))
else
CFLAGS		+= -Os -DNDEBUG
LDFLAGS		+= -s
endif

# installation variables
prefix		:= /usr
libdir		:= $(prefix)/lib
includedir	:= $(prefix)/include

############################################################

# tgts
tgts		:= $(TARGET_SHARED) $(TARGET_STATIC)
extra_tgts	:= $(TEST_TARGET)

# list C files
sources		:= $(wildcard src/*.c)
test_sources	:= $(wildcard tests/*.c)

# get objects from C files
objects		:= $(sources:.c=.o)
test_objects	:= $(test_sources:.c=.o)

# rules
.PHONY: all
all: $(tgts) $(extra_tgts)

%.o: %.c
	@echo "  CC $<"
	@${CC} ${CFLAGS} -c $< -o $@

$(TARGET_SHARED): $(objects)
	@echo "  LD $@"
	@$(CC) $(LDFLAGS) -shared $^ $(LDLIBS) -o $@

$(TARGET_STATIC): $(objects)
	@echo "  AR $@"
	@$(AR) rcs $@ $^

flct_%: tests/%.o
	@echo "  LD $@"
	@$(CC) $^ $(LDFLAGS) $(LDLIBS) -Wl,-Bstatic -lflc -Wl,-Bdynamic -o $@

.PHONY: clean
clean:
	find -name "*.o" -delete
	$(RM) $(TARGET_SHARED) $(TARGET_STATIC) flct_*

.PHONY: mrproper
mrproper: clean

.PHONY: install
install: all
	@echo "   INSTALL $(TARGET_SHARED)"
	@$(INSTALL) -d $(libdir)/
	@$(INSTALL) -m 755 $(TARGET_SHARED) $(libdir)/$(TARGET_SHARED)
	@$(INSTALL) -m 755 $(TARGET_STATIC) $(libdir)/$(TARGET_STATIC)
	@$(INSTALL) -d $(includedir)/flc
	@$(INSTALL) -m 644 include/flc/*.h $(includedir)/flc

.PHONY: uninstall
uninstall:
	@echo "   UNINSTALL $(TARGET_SHARED)"
	$(RM) $(libdir)/$(TARGET_SHARED) $(libdir)/$(TARGET_STATIC)
