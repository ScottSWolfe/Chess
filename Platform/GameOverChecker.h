#pragma once

#include <string>
class GameState;


class GameOverChecker {

public:
	std::string isGameOver(const GameState &state) const;

private:
	bool isCheckMate(const GameState &state) const;

};
