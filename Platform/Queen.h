#pragma once

class Queen : public Piece {
public:
	Queen(PieceColor color);
	std::string getSymbol() override;
};
