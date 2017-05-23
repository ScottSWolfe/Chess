#pragma once

#include <memory>
#include "ChessEnums.h"
#include "Board.h"
#include "Player.h"
#include "HumanPlayer.h"


class GameState {

public:
	GameState(Board board, PlayerTurn beginning_player);
	Board getBoard() const;

private:
	Board board;
	PlayerTurn current_player;

};
