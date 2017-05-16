#pragma once
#include <string>

enum class Color { White, Black };

class Piece {
private:
	Color color;
public:
	Piece(Color color);
	virtual Color getColor();
	virtual std::string getSymbol() = 0;
};
