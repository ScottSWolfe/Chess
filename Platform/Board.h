#pragma once

#include <memory>
#include <string>
#include <vector>
#include "ChessEnums.h"
#include "Square.h"
class MoveEffect;
class Piece;
struct Position;


class Board {

public:
	Board(int board_dimension);
	Board(const Board &other_board);
	std::shared_ptr<Board> getCopy() const;
	Square &getSquare(Position pos);
	const Square &getSquare(Position pos) const;
	SquareColor getSquareColor(Position pos) const;
	bool inBounds(Position pos) const;
	void makeMove(const Move &move);
	void addPieceToSquare(Position pos, std::unique_ptr<const Piece> &piece);
	std::unique_ptr<const Piece> removePieceFromSquare(Position pos);
	bool isPiece(Position pos) const;
	const Piece *getPiece(Position pos) const;
	PieceColor getPieceColor(Position pos) const;
	std::string getPieceSymbol(Position pos) const;
	bool isOppPieceColor(Position pos, PieceColor color) const;
	void setPiece(Position pos, std::unique_ptr<const Piece> &piece);
	bool willKingBeInCheck(GameState &state, const Move &move) const;
	int getDimension() const;

private:
	const int dimension;
	std::vector<Square> squares;
	int getIndex(Position pos) const;
	Position getPosition(int index) const;
	SquareColor getSquareColorByIndex(int index) const;
	void checkIfPieceIsNull(const Piece *piece) const;
	void applyMoveEffect(const MoveEffect *effect);
	bool canPieceCaptureKing(const GameState state, PieceColor current_player, Position king_position) const;
	Position getKingPosition(PieceColor current_player) const;

};
