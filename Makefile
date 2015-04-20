COMPILE = g++
DEPEND = -lGL -lGLU -lGLEW -lglut -lm -Wno-write-strings -o
MAIN = PlanetsProject

all:
	${COMPILE} ${MAIN}.cpp getbmp.cpp ${DEPEND} ${MAIN}

clean:
	rm -rf ${MAIN}
