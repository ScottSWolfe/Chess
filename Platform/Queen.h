#pragma once

class Queen : public Piece {
public:
	Queen(Color color);
	std::string getSymbol() override;
};
