#include <memory>
#include "ChessDebug.h"
#include "GameState.h"
#include "MoveEffect.h"
#include "Piece.h"
#include "Position.h"
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

bool GameState::isPiece(Position pos) const {
	return board.isPiece(pos);
}

const Piece *GameState::getPiece(Position pos) const {
	return board.getPiece(pos);
}

PieceColor GameState::getPieceColor(Position pos) const {
	return board.getPieceColor(pos);
}

bool GameState::isMoveAvailable(const Move &move) const {
	const Piece *piece = board.getPiece(move.getStart());
	vector<Move> moves = piece->getMoves(*this, move.getStart());
	for (Move curr_move : moves) {
		if (curr_move == move) {
			return true;
		}
	}
	return false;
}

void GameState::makeMove(const Move &move) {
	Position start = move.getStart();
	Position end = move.getEnd();
	const MoveEffect *effect = move.getEffect();
	unique_ptr<const Piece> piece = board.removePieceFromSquare(start);
	board.addPieceToSquare(end, piece);
	applyMoveEffect(effect);
	move_history.push_back(move);
	changePlayersTurn();
}

void GameState::checkForAndAddMoveEffect(Move &move) const {
	if (move.getEffect() != nullptr) {
		return;
	}
	const Piece *piece = getPiece(move.getStart());
	piece->checkForAndAddMoveEffect(*this, move);
}

void GameState::applyMoveEffect(const MoveEffect *effect) {
	if (effect == nullptr) {
		return;
	}
	Position pos = effect->getPosition();
	unique_ptr<const Piece> piece = effect->getCopyOfPiece();
	board.setPiece(pos, piece);
}

const Move *GameState::getLastMove() const {
	if (move_history.empty()) {
		return nullptr;
	}
	return &move_history.back();
}

bool GameState::isOppPieceColor(Position pos, PieceColor color) const {
	return board.isOppPieceColor(pos, color);
}

bool GameState::inBounds(Position pos) const {
	return board.inBounds(pos);
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
