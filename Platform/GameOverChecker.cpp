#include <string>
#include "GameOverChecker.h"
#include "GameState.h"
#include "Move.h"
using namespace std;


string GameOverChecker::isGameOver(const GameState &state) const {
	if (isCheckMate(state) == true) {
		return "Check Mate";
	}
	return "";
}

bool GameOverChecker::isCheckMate(const GameState &state) const {
	if (state.canCurrentPlayerMakeMove() == true) {
		return false;
	}
	if (state.isKingInCheck() == false) {
		return false;
	}
	return true;
}
