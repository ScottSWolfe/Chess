#pragma once

#include <memory>
#include <string>
#include "Player.h"
#include "BoardPresenter.h"
#include "GameState.h"


class GameManager {
	
public:
	GameManager();
	void startGame();

private:
	// variables
	GameState current_state;
	std::unique_ptr<const Player> white_player;
	std::unique_ptr<const Player> black_player;
	std::unique_ptr<BoardPresenter> presenter;

	// methods
	void runGameLoop();
	std::shared_ptr<Move> getMove() const;
	const Player *getCurrentPlayer() const;
	std::shared_ptr<Move> getCurrentPlayersMove() const;
	std::shared_ptr<Move> addMoveEffect() const;
	bool validateMoveIsLegal(const Move &move) const;
	bool validateMoveIsSafe(const Move &move) const;
	std::shared_ptr<Move> getAnotherMove() const;
	std::string playerTurnToString() const;

};
