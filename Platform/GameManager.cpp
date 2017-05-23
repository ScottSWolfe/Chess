#include <iostream>
#include "BoardInitializer.h"
#include "ConsoleBoardPresenter.h"
#include "GameManager.h"
using namespace std;


GameManager::GameManager() :
	presenter(new ConsoleBoardPresenter),
	current_state(BoardInitializer::initializeStandardSetup(), PlayerTurn::WHITE),
	white_player(new HumanPlayer(PieceColor::WHITE)),
	black_player(new HumanPlayer(PieceColor::BLACK))
{}

void GameManager::startGame() {
	runGameLoop();
}

void GameManager::runGameLoop() {
	cout << "Game Loop Started";
	presenter->displayBoard(current_state.getBoard());
}
