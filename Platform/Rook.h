#pragma once

class Rook : public Piece {
public:
	Rook(Color color);
	std::string getSymbol() override;
};
