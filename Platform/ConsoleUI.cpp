#include <iostream>
#include "ConsoleUI.h"
#include "GameState.h"
using namespace std;


void ConsoleUI::stateChanged(const GameState &newState) {
	isStartOfGame(newState);
	presenter.displayBoard(newState.getBoard());
	cout << currentTurnToString(newState) << "'s Turn" << endl;
}

bool ConsoleUI::isStartOfGame(const GameState &newState) const {
	if (newState.getLastMove() == nullptr) {
		cout << "Start Game" << endl;
		return true;
	}
	return false;
}

string ConsoleUI::currentTurnToString(const GameState &newState) const {
	if (newState.getPlayersTurn() == PieceColor::BLACK) {
		return "Black";
	}
	else {
		return "White";
	}
}
