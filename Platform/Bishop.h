#pragma once

class Bishop : public Piece {
public:
	Bishop(Color color);
	std::string getSymbol() override;
};
