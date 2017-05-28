#pragma once

#include <memory>
#include <string>
#include <vector>
#include "ChessEnums.h"
class Board;
class Move;
struct Position;


class Piece {

public:
	Piece(PieceColor color);
	PieceColor getColor() const;
	virtual const std::string getSymbol() const = 0;
	virtual std::vector<Move> getMoves(const Board &board, Position pos) const = 0;
	static const std::string getPieceSymbol(const Piece *piece);

private:
	const PieceColor color;
	const int x = 3;

protected:
	const std::string PAWN_SYMBOL = "p";
	const std::string ROOK_SYMBOL = "R";
	const std::string BISHOP_SYMBOL = "B";
	const std::string KNIGHT_SYMBOL = "N";
	const std::string QUEEN_SYMBOL = "Q";
	const std::string KING_SYMBOL = "K";

};

PieceColor getPieceColor(const Piece *piece);
std::unique_ptr<const Piece> copyPieceFactory(const Piece *piece);
