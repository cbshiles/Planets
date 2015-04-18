COMPILE = g++
DEPEND = -lGL -lGLU -lGLEW -lglut -lm -Wno-write-strings -o
MAIN = NAME_OF_FILE_GOES_HERE

all:
	${COMPILE} ${MAIN}.cpp getbmp.cpp ${DEPEND} ${MAIN}

clean:
	rm -rf ${MAIN}
