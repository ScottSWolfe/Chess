#include <memory>
#include "GameState.h"
using namespace std;


GameState::GameState(Board board, PlayerTurn beginning_player) : 
	board(board),
	current_turn(beginning_player)
{}

Board GameState::getBoard() const {
	return board;
}

void GameState::makeMove(Move move) {
	SquareCoordinate start = move.getStartSquareCoord();
	SquareCoordinate end = move.getEndSquareCoord();
	unique_ptr<const Piece> piece = board.removePieceFromSquare(start.x, start.y);
	if (piece == nullptr) {
		throw invalid_argument("Start square does not contain a piece.");
	}
	board.addPieceToSquare(end.x, end.y, piece);
	changePlayersTurn();
}

PlayerTurn GameState::getPlayersTurn() const {
	return current_turn;
}

void GameState::changePlayersTurn() {
	if (current_turn == PlayerTurn::WHITE) {
		current_turn = PlayerTurn::BLACK;
	}
	else {
		current_turn = PlayerTurn::WHITE;
	}
}
