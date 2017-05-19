#pragma once

#include "Board.h"
#include "Player.h"


enum class PlayerTurn { WHITE, BLACK };

class GameState {

public:
	Board *getBoard();
	Player *getCurrentPlayer();

private:
	Board board;
	Player white_player;
	Player black_player;
	PlayerTurn current_player;

};
