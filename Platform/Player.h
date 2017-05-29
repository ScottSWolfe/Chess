#pragma once

#include <memory>
#include "ChessEnums.h"
class Board;
class Move;


class Player {

public:
	Player(PieceColor color);
	virtual std::shared_ptr<Move> move(Board board) const = 0;

protected:
	const PieceColor color;

};
