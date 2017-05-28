#pragma once

#include <string>
#include <vector>
#include "ChessEnums.h"
#include "Piece.h"
class Board;
class Move;
struct Position;


class Pawn : public Piece {

public:
	Pawn(PieceColor color);
	const std::string getSymbol() const override;
	std::vector<Move> getMoves(const Board &board, Position pos) const override;

private:
	int step() const;
	int startRow(int dimension) const;

};
