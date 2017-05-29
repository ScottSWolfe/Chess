#pragma once

#include <string>
#include <vector>
#include "ChessEnums.h"
#include "Piece.h"
class GameState;
class Move;
struct Position;


class Pawn : public Piece {

public:
	Pawn(PieceColor color);
	const std::string getSymbol() const override;
	std::vector<Move> getMoves(const GameState &state, Position pos) const override;
	void checkForAndAddMoveEffect(const GameState &state, Move &move) const override;

private:
	int step() const;
	int startRow(int dimension) const;
	int enPassantRow(int dimension) const;
	bool addMoveIfEnPassantAvailable(std::vector<Move> &moves, const GameState &state,
									 Position start, const Move &last_move, int delta_x) const;

};
