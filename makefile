SOURCES = program.c argscheck.c sortall.c sparta.c shell.c

PROGRAM = sortall.com

ifdef CC65_TARGET
CC      = $(CC65_HOME)/bin/cl65.exe
CFLAGS  = -t $(CC65_TARGET) --create-dep -O -Or
LDFLAGS = -t $(CC65_TARGET) -m $(PROGRAM).map
RM      = rm
else
CC      = gcc
CFLAGS  = -MMD -MP -O
LDFLAGS = -Wl,-Map,$(PROGRAM).map
endif
 
########################################

ifdef CC65_TARGET
define MAKEDEPEND
sed -e"s!$(<:.c=.s)!$@!p" -e"s![^:]*:.\(.*\)!\1:!" < $(<:.c=.u) > $(@:.o=.d)
$(RM) $(<:.c=.u)
endef
endif

.SUFFIXES:
.PHONY: all clean
all: $(PROGRAM)

ifneq ($(MAKECMDGOALS),clean)
-include $(SOURCES:.c=.d)
endif

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<
	@$(MAKEDEPEND)

$(PROGRAM): $(SOURCES:.c=.o)
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	$(RM) $(SOURCES:.c=.o) $(SOURCES:.c=.d) $(PROGRAM) $(PROGRAM).map
	