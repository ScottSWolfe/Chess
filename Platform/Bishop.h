#pragma once

class Bishop : public Piece {
public:
	Bishop(PieceColor color);
	std::string getSymbol() override;
};
