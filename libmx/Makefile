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
	@rm -rdf ../obj

uninstall: clean
	@rm -f libmx.a

clean:
	@rm -f inc/*.gch

reinstall: uninstall libmx
