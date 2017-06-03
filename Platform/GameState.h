#pragma once

#include <memory>
#include <vector>
#include "ChessEnums.h"
#include "Board.h"
#include "Move.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "StateSubject.h"
struct Position;
class StateObserver;


class GameState : StateSubject {

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
	bool isKingInCheck() const;
	Position getKingPosition(PieceColor king_color) const;
	void makeMove(const Move &move);
	void addMoveEffect(Move &move) const;
	bool isOppPieceColor(Position pos, PieceColor color) const;
	bool inBounds(Position pos) const;
	PieceColor getCurrentPlayersTurn() const;
	const Move *getLastMove() const;
	bool canCurrentPlayerMakeMove() const;
	std::vector<Move> getAvailableMoves() const;
	void registerObserver(StateObserver *observer);

private:
	Board board;
	PieceColor current_turn;
	std::vector<Move> move_history;
	std::vector<StateObserver*> observers;

	void changePlayersTurn();
	void GameState::notifyObservers() const;

};
