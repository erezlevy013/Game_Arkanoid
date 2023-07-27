CXX?=g++ 
CC=$(CXX)

SRC_DIR = ../src/
INC_DIR = ../inc/

CPPFLAGS = -MMD -MP -I$(INC_DIR)
CXXFLAGS = -std=c++17
CXXFLAGS+= -g -pedantic -Wall -Werror

TARGET = utest 

check: $(TARGET)
	./$(TARGET) -v 



$(TARGET): utest.o $(SRC_DIR)Game.o $(SRC_DIR)Board.o $(SRC_DIR)Ball.o $(SRC_DIR)Bar.o $(SRC_DIR)NormalBrick.o $(SRC_DIR)HardBrick.o $(SRC_DIR)Level.o $(SRC_DIR)Score.o $(SRC_DIR)Text.o $(SRC_DIR)UnbreakableBrick.o $(SRC_DIR)Gems.o -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

utest.o: utest.cpp $(INC_DIR)Game.hpp $(INC_DIR)MoveShape.hpp $(INC_DIR)Board.hpp $(INC_DIR)Ball.hpp $(INC_DIR)Bar.hpp $(INC_DIR)Brick.hpp $(INC_DIR)NormalBrick.hpp $(INC_DIR)HardBrick.hpp $(INC_DIR)Level.hpp $(INC_DIR)Score.hpp $(INC_DIR)Text.hpp $(INC_DIR)UnbreakableBrick.hpp $(INC_DIR)Gems.hpp

$(SRC_DIR)Game.o: $(INC_DIR)Game.hpp $(SRC_DIR)Game.cpp
$(SRC_DIR)Board.o: $(INC_DIR)Board.hpp $(SRC_DIR)Board.cpp 
$(SRC_DIR)Ball.o: $(INC_DIR)Ball.hpp $(SRC_DIR)Ball.cpp
$(SRC_DIR)Bar.o: $(INC_DIR)Bar.hpp $(SRC_DIR)Bar.cpp
$(SRC_DIR)NormalBrick.o: $(INC_DIR)NormalBrick.hpp $(SRC_DIR)NormalBrick.cpp
$(SRC_DIR)HardBrick.o: $(INC_DIR)HardBrick.hpp $(SRC_DIR)HardBrick.cpp
$(SRC_DIR)UnbreakableBrick.o: $(INC_DIR)UnbreakableBrick.hpp $(SRC_DIR)UnbreakableBrick.cpp
$(SRC_DIR)Level.o: $(INC_DIR)Level.hpp $(SRC_DIR)Level.cpp
$(SRC_DIR)Score.o: $(INC_DIR)Score.hpp $(SRC_DIR)Score.cpp
$(SRC_DIR)Text.o: $(INC_DIR)Text.hpp $(SRC_DIR)Text.cpp
$(SRC_DIR)Gems.o: $(INC_DIR)Gems.hpp $(SRC_DIR)Gems.cpp


valgrind:$(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=val.txt ./$(TARGET)

clean:
	@$(RM) *.o *.d $(SRC_DIR)*.o  $(SRC_DIR)*.d $(TARGET) $(DEPENDS)*.d *.ppm

DEPENDS = $(utest.o:%.o=%.d)
	-include $(DEPENDS)
	
	
