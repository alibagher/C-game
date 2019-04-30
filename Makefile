CXX = g++-5
CXXFLAGS = -std=c++14 -Wall -Werror=vla -MMD
EXEC = ctor
OBJECTS = main.o constructable.o address.o player.o bluePlayer.o redPlayer.o orangePlayer.o yellowPlayer.o board.o boardFactory.o path.o dicestrategy.o fairdicestrategy.o loadeddicestrategy.o tile.o brick.o glass.o heat.o park.o wifi.o energy.o subject.o observer.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm -f ${OBJECTS} ${EXEC} ${DEPENDS} &>/dev/null
.PHONY: clean
