#pragma once

#include <memory>
#include "Board.h"
#include "Player.h"


enum class PlayerTurn { WHITE, BLACK };

class GameState {

public:
	Board *getBoard();
	Player *getCurrentPlayer();

private:
	Board board;
	std::unique_ptr<Player> white_player;
	std::unique_ptr<Player> black_player;
	PlayerTurn current_player;

};
