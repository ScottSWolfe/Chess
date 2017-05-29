#pragma once

#include <memory>
#include <string>
#include <vector>
#include "ChessEnums.h"
class GameState;
class Move;
struct Position;


class Piece {

public:
	Piece(PieceColor color);
	PieceColor getColor() const;
	virtual const std::string getSymbol() const = 0;
	virtual std::vector<Move> getMoves(const GameState &state, Position pos) const = 0;

	static std::unique_ptr<const Piece> copyPieceFactory(const Piece *piece);
	static const std::string getPieceSymbol(const Piece *piece);
	static PieceColor getPieceColor(const Piece *piece);

protected:
	const PieceColor color;
	void getStraightMoves(std::vector<Move> &moves, const GameState &state, Position start) const;
	void getDiagonalMoves(std::vector<Move> &moves, const GameState &state, Position start) const;
	void getMovesInLine(std::vector<Move> &moves, const GameState &state, Position start, int delta_x, int delta_y) const;

	const std::string PAWN_SYMBOL = "p";
	const std::string ROOK_SYMBOL = "R";
	const std::string BISHOP_SYMBOL = "B";
	const std::string KNIGHT_SYMBOL = "N";
	const std::string QUEEN_SYMBOL = "Q";
	const std::string KING_SYMBOL = "K";

};
