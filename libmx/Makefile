.PHONY: all libmx uninstall clean reinstall

SRCS := $(wildcard src/*.c)
HDRS := $(wildcard inc/libmx.h)

all: libmx

libmx:
	@clang -c ${HDRS} ${SRCS}
	@mkdir ../obj
	@mv *.o ../obj
	@ar -rc libmx.a ../obj/*.o
	@ranlib libmx.a

uninstall: clean
	@rm -f libmx.a

clean:
	@rm -rdf ../obj
	@rm -f inc/*.gch

reinstall: uninstall libmx
