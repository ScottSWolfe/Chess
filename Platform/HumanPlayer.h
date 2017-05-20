#pragma once

#include "Player.h"
#include "Board.h"


class HumanPlayer : public Player {

public:
	HumanPlayer(PieceColor color);
	Board move(Board board) override;

};
