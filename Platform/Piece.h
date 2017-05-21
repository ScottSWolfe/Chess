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
};

const std::string getPieceSymbol(const Piece *piece);
PieceColor getPieceColor(const Piece *piece);
std::unique_ptr<const Piece> copyPieceFactory(const Piece *piece);
