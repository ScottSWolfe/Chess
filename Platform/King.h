#pragma once

class King : public Piece {
public:
	King(PieceColor color);
	std::string getSymbol() override;
};
