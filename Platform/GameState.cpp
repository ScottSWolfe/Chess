#include <memory>
#include "ChessDebug.h"
#include "GameState.h"
using namespace std;


GameState::GameState(Board board, PlayerTurn beginning_player) : 
	board(board),
	current_turn(beginning_player)
{}

Board GameState::getBoard() const {
	return board;
}

int GameState::getBoardDimension() const {
	return board.getDimension();
}

bool GameState::isPiece(int x, int y) const {
	return board.isPiece(x, y);
}

const Piece *GameState::getPiece(int x, int y) const {
	return board.getPiece(x, y);
}

PieceColor GameState::getPieceColor(int x, int y) const {
	return board.getPieceColor(x, y);
}

bool GameState::isMoveAvailable(const Move &move) const {
	int x = move.getStartCoords().x;
	int y = move.getStartCoords().y;
	const Piece *piece = board.getPiece(x, y);
	if (piece == nullptr) {
		throw invalid_argument("square does not contain a piece");
	}
	vector<Move> moves = piece->getMoves(board, x, y);
	for (Move curr_move : moves) {
		if (curr_move == move) {
			return true;
		}
	}
	return false;
}

void GameState::makeMove(const Move &move) {
	SquareCoordinates start = move.getStartCoords();
	SquareCoordinates end = move.getEndCoords();
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
