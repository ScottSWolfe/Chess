#pragma once

#include <memory>
#include "ChessEnums.h"
#include "Board.h"
#include "Move.h"
#include "Player.h"
#include "HumanPlayer.h"
struct Position;


class GameState {

public:
	GameState(Board board, PieceColor beginning_player);
	GameState(const GameState &other);
	std::shared_ptr<GameState> getCopy() const;
	const Board &getBoard() const;
	int getBoardDimension() const;
	bool isPiece(Position pos) const;
	const Piece *getPiece(Position pos) const;
	PieceColor getPieceColor(Position pos) const;
	bool isMoveAvailable(const Move &move) const;
	bool willKingBeInCheck(const Move &move) const;
	void makeMove(const Move &move);
	void checkForAndAddMoveEffect(Move &move) const;
	bool isOppPieceColor(Position pos, PieceColor color) const;
	bool inBounds(Position pos) const;
	PieceColor getPlayersTurn() const;
	const Move *getLastMove() const;

private:
	Board board;
	PieceColor current_turn;
	std::vector<Move> move_history;
	void changePlayersTurn();

};
