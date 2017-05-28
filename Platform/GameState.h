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
	GameState(Board board, PlayerTurn beginning_player);
	Board getBoard() const;
	int getBoardDimension() const;
	bool isPiece(Position pos) const;
	const Piece *getPiece(Position pos) const;
	PieceColor getPieceColor(Position pos) const;
	bool isMoveAvailable(const Move &move) const;
	void makeMove(const Move &move);
	PlayerTurn getPlayersTurn() const;

private:
	Board board;
	PlayerTurn current_turn;
	void GameState::changePlayersTurn();

};
