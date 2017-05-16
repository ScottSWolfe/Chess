#pragma once

class Pawn : public Piece {
public:
	Pawn(Color color);
	std::string getSymbol() override;
};
