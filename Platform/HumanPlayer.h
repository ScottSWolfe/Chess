#pragma once

#include "ChessEnums.h"
#include "Player.h"
class Board;
class Move;


class HumanPlayer : public Player {

public:
	HumanPlayer(PieceColor color);
	Move move(Board board) const override;

};
