#include <memory>
#include "ChessDebug.h"
#include "GameState.h"
#include "MoveEffect.h"
#include "Piece.h"
#include "Position.h"
#include "GameObserver.h"
using namespace std;


GameState::GameState(Board board, PieceColor beginning_player) : 
	board(board),
	current_turn(beginning_player)
{}

GameState::GameState(const GameState &other)
	: board(other.board), current_turn(other.current_turn)
{
	for (Move move : other.move_history) {
		move_history.push_back(move);
	}
}

shared_ptr<GameState> GameState::getCopy() const {
	return make_shared<GameState>(*this);
}

const Board &GameState::getBoard() const {
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
	vector<Move> moves = piece->getAvailableMoves(*this, move.getStart());
	for (Move curr_move : moves) {
		if (curr_move == move) {
			return true;
		}
	}
	return false;
}

bool GameState::willKingBeInCheck(const Move &move) const {
	shared_ptr<GameState> copy_of_state = this->getCopy();
	return copy_of_state->board.willKingBeInCheck(*copy_of_state, move);
}

bool GameState::isKingInCheck() const {
	return board.isKingInCheck(*this);
}

Position GameState::getKingPosition(PieceColor king_color) const {
	return board.getKingPosition(king_color);
}

void GameState::makeMove(const Move &move) {
	board.makeMove(move);
	move_history.push_back(move);
	changePlayersTurn();
}

void GameState::addMoveEffect(Move &move) const {
	if (move.getEffect() != nullptr) {
		return;
	}
	const Piece *piece = getPiece(move.getStart());
	piece->addMoveEffect(*this, move);
}

const Move *GameState::getLastMove() const {
	if (move_history.empty()) {
		return nullptr;
	}
	return &move_history.back();
}

vector<Move> GameState::getAvailableMoves() const {
	vector<Move> moves;
	PieceColor current_color = getCurrentPlayersTurn();
	int dimension = getBoardDimension();
	for (int j = 0; j < dimension; j++) {
		for (int i = 0; i < dimension; i++) {
			Position pos(i, j);
			if (board.isPiece(pos) && board.getPieceColor(pos) == current_color) {
				board.getPiece(pos)->getAvailableMoves(*this, pos);
			}
		}
	}
	return moves;
}

bool GameState::canCurrentPlayerMakeMove() const {
	int dimension = getBoardDimension();
	for (int j = 0; j < dimension; j++) {
		for (int i = 0; i < dimension; i++) {
			Position pos(i, j);
			if (board.isPiece(pos) && board.getPieceColor(pos) == current_turn) {
				if (board.getPiece(pos)->canPieceMakeMove(*this, pos) == true) {
					return true;
				}
			}
		}
	}
	return false;
}

bool GameState::isOppPieceColor(Position pos, PieceColor color) const {
	return board.isOppPieceColor(pos, color);
}

bool GameState::inBounds(Position pos) const {
	return board.inBounds(pos);
}

PieceColor GameState::getCurrentPlayersTurn() const {
	return current_turn;
}

void GameState::changePlayersTurn() {
	if (current_turn == PieceColor::WHITE) {
		current_turn = PieceColor::BLACK;
	}
	else {
		current_turn = PieceColor::WHITE;
	}
	notifyObserversTurnEnded();
}

void GameState::registerObserver(GameObserver *observer) {
	observers.push_back(observer);
}

void GameState::notifyObserversGameStarted() const {
	for (auto observer : observers) {
		observer->gameStarted(*this);
	}
}

void GameState::notifyObserversGameEnded(GameEndType end_type) const {
	for (auto observer : observers) {
		observer->gameEnded(*this, end_type);
	}
}

void GameState::notifyObserversTurnStarted() const {
	for (auto observer : observers) {
		observer->turnStarted(*this);
	}
}

void GameState::notifyObserversTurnEnded() const {
	for (auto observer : observers) {
		observer->turnEnded(*this);
	}
}
