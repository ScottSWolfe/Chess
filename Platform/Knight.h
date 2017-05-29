#pragma once

#include <string>
#include <vector>
#include "ChessEnums.h"
#include "Piece.h"
class GameState;
struct Position;


class Knight : public Piece {

public:
	Knight(PieceColor color);
	const std::string getSymbol() const override;
	std::vector<Move> getMoves(const GameState &state, Position pos) const override;
	void checkForAndAddMoveEffect(const GameState &state, Move &move) const override;

};
