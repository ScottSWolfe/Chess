#pragma once

#include <memory>
#include <string>
#include "Player.h"
#include "BoardPresenter.h"
#include "GameState.h"

class StateObserver;


class GameManager {
	
public:
	GameManager();
	void startGame();
	void registerStateObserver(StateObserver *observer);

private:
	// variables
	GameState current_state;
	std::unique_ptr<const Player> white_player;
	std::unique_ptr<const Player> black_player;
	std::unique_ptr<BoardPresenter> presenter;

	// methods
	void runGameLoop();
	bool isGameOver() const;
	std::shared_ptr<Move> getMove() const;
	const Player *getCurrentPlayer() const;
	std::shared_ptr<Move> getCurrentPlayersMove() const;
	bool validateMoveIsLegal(const Move &move) const;
	bool validateMoveIsSafe(const Move &move) const;
	std::shared_ptr<Move> getAnotherMove() const;

};
