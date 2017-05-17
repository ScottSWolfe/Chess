#pragma once

class Knight : public Piece {
public:
	Knight(PieceColor color);
	std::string getSymbol() override;
};
