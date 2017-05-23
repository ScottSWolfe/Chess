#pragma once

#include "ChessEnums.h"
class Board;


class Player {

public:
	Player(PieceColor color);
	virtual Board move(Board board) = 0;

private:
	const PieceColor color;

};
