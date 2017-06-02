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
	std::unique_ptr<const Piece> getCopy() const override;
	const std::string getSymbol() const override;
	std::vector<Move> getAvailableMoves(const GameState &state, Position start) const override;
	void addMoveEffect(const GameState &state, Move &move) const override;

private:
	int step() const;
	int startRow(int dimension) const;
	int enPassantRow(int dimension) const;
	int promotionRow(int dimension) const;
	bool isEnPassantAvailable(const GameState &state, Position start, int &dst_delta_x) const;
	void addEnPassantMove(std::vector<Move> &moves, Position start, int delta_x) const;
	void modifyEnPassantMove(Move &move, int delta_x) const;

};
