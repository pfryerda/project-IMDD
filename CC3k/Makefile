CXX = g++
CXXFLAGS = -Wall -MMD
EXEC = cc3k
FILES = $(wildcard *.cc) $(wildcard src/*.cc) $(wildcard src/boardClasses/*.cc) $(wildcard src/things/*.cc) $(wildcard src/things/character/*.cc) $(wildcard src/things/character/pc/*.cc) $(wildcard src/things/character/pc/decorator/*.cc) $(wildcard src/things/character/enemies/*.cc) $(wildcard src/things/item/*.cc) $(wildcard src/things/item/gold/*.cc) $(wildcard src/things/item/potion/*.cc)
OBJECTS = $(FILES:.cc=.o)
DEPENDS = ${OBJECTS:.o=.d}

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}

.PHONY: zip

zip:
	rm a5cc3k.zip
	zip -r a5cc3k.zip .
