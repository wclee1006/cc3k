CXX = g++
CXXFLAGS = -std=c++14 -g -MMD -Wall
OBJECTS = main.o
OBJECTS += Board.o Floor.o Chamber.o TextDisplay.o Subject.o 
OBJECTS += Cell.o CellContent.o
OBJECTS += Stair.o
OBJECTS += Potion.o Restore.o BoostAtk.o BoostDef.o Poison.o WoundAtk.o WoundDef.o 
OBJECTS += Character.o Player.o Human.o Dwarf.o Elf.o Orc.o
OBJECTS += Enemy.o Dragon.o Werewolf.o Troll.o Goblin.o Merchant.o Vampire.o Phoenix.o Decorator.o Compass.o
OBJECTS += Treasure.o Small.o Normal.o MerchantH.o DragonH.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = cc3k+

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY : clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
