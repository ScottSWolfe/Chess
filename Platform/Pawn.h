#pragma once

class Pawn : public Piece {
public:
	Pawn(PieceColor color);
	std::string getSymbol() override;
};
