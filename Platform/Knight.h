#pragma once

class Knight : public Piece {
public:
	Knight(Color color);
	std::string getSymbol() override;
};
