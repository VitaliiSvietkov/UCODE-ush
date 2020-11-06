.PHONY: all ush uninstall clean reinstall

SRCS := $(wildcard src/*.c)
HDRS := $(wildcard inc/*.h)

all: ush

ush:
	@make -C libmx/
	@clang -std=c11 -Wall -Wextra -Werror -Wpedantic ${SRCS} ${HDRS} libmx/libmx.a
	@mv a.out ush

uninstall: clean
	@make -C libmx/ uninstall

clean:
	@make -C libmx/ clean
	@rm -rdf ush
	@rm -rdf inc/*.gch

reinstall: uninstall ush
