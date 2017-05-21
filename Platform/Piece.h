#pragma once

#include <memory>
#include <string>
#include "ChessEnums.h"


class Piece {

public:
	Piece(PieceColor color);
	virtual PieceColor getColor() const;
	virtual const std::string getSymbol() const = 0;
		
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

const std::string getPieceSymbol(const Piece *piece);
PieceColor getPieceColor(const Piece *piece);
std::unique_ptr<const Piece> copyPieceFactory(const Piece *piece);
