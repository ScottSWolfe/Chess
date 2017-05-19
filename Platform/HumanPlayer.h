#pragma once

#include "Player.h"
#include "Board.h"


class HumanPlayer : public Player {

public:
	Board move(Board board) override;

};
