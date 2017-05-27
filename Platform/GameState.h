#pragma once

#include <memory>
#include "ChessEnums.h"
#include "Board.h"
#include "Move.h"
#include "Player.h"
#include "HumanPlayer.h"


class GameState {

public:
	GameState(Board board, PlayerTurn beginning_player);
	Board getBoard() const;
	int getBoardDimension() const;
	bool isPiece(int x, int y) const;
	PieceColor getPieceColor(int x, int y) const;
	void makeMove(const Move &move);
	PlayerTurn getPlayersTurn() const;

private:
	Board board;
	PlayerTurn current_turn;
	void GameState::changePlayersTurn();

};
