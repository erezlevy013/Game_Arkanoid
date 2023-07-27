#include "mu_test.h"

#include <string>
#include <climits>

#include <iostream>

#include "Game.hpp"
#include "Board.hpp"
#include "Ball.hpp"
#include "Bar.hpp"

using namespace h72;




BEGIN_TEST(checkGame)
    Game game;
    game.Run();

	ASSERT_PASS();
END_TEST

TEST_SUITE("זִיַאדַּתּ אַלגַּום, לַא כַיר פִיהּ")
   
    TEST(checkGame)
	
END_SUITE

