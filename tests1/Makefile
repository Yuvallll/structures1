GPP=g++
PROJ_FILES_PATH=.
TESTS_DIR=./WorldCupTests
O_FILES_DIR=$(TESTS_DIR)/OFiles
EXEC=WorldCupUnitTester
TESTS_INCLUDED_FILE=worldcup23a1.h $(TESTS_DIR)/catch.hpp
OBJS=$(O_FILES_DIR)/UnitTests.o $(O_FILES_DIR)/Team.o $(O_FILES_DIR)/Player.o $(O_FILES_DIR)/worldcup23a1.o $(O_FILES_DIR)/AVLTree.o $(O_FILES_DIR)/Functors.o \
 $(O_FILES_DIR)/LTeam.o




 # UPDATE HERE ALL THE O FILES YOU CREATED BELOW
DEBUG_FLAG= -g # can add -g
COMP_FLAG=--std=c++11 -Wall -Werror -pedantic-errors $(DEBUG_FLAG)

$(EXEC) : $(OBJS)
	$(GPP) $(COMP_FLAG) $(OBJS) -o $@


$(O_FILES_DIR)/UnitTests.o : $(TESTS_DIR)/WorldCupTests.cpp
	@mkdir -p $(O_FILES_DIR)
	$(GPP) -c $(COMP_FLAG) $(TESTS_DIR)/WorldCupTests.cpp -o $@

 # UPDATE FROM HERE



$(O_FILES_DIR)/AVLTree.o: AVLTree.cpp AVLTree.h
	@mkdir -p $(O_FILES_DIR)
	$(GPP) -c $(COMP_FLAG) AVLTree.cpp -o $@


$(O_FILES_DIR)/Functors.o: Functors.cpp Player.h Team.h Functors.h
	@mkdir -p $(O_FILES_DIR)
	$(GPP) -c $(COMP_FLAG) ComparePlayerById.cpp -o $@

$(O_FILES_DIR)/LTeam.o: LTeam.cpp LTeam.h
	@mkdir -p $(O_FILES_DIR)
	$(GPP) -c $(COMP_FLAG) SimulationTeam.cpp -o $@


$(O_FILES_DIR)/Player.o : Player.cpp Team.h AVLTree.h Functors.h \
  Player.h
	@mkdir -p $(O_FILES_DIR)
	$(GPP) -c $(COMP_FLAG) Player.cpp -o $@


$(O_FILES_DIR)/Team.o: Team.cpp Team.h AVLTree.h Functors.h \
  Player.h
	@mkdir -p $(O_FILES_DIR)
	$(GPP) -c $(COMP_FLAG) Team.cpp -o $@



$(O_FILES_DIR)/worldcup23a1.o : worldcup23a1.cpp worldcup23a1.h wet1util.h Player.h \
 Team.h AVLTree.h Functors.h LTeam.h
	@mkdir -p $(O_FILES_DIR)
	$(GPP) -c $(COMP_FLAG) worldcup23a1.cpp -o $@
	
 # UNTIL HERE
	

.PHONY: clean
clean:
	rm -f $(OBJS) $(EXEC)
