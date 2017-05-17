#pragma once

class Rook : public Piece {
public:
	Rook(PieceColor color);
	std::string getSymbol() override;
};
