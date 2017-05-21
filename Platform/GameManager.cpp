#include <iostream>
#include "ConsoleBoardPresenter.h"
#include "GameManager.h"
using namespace std;


GameManager::GameManager() : presenter(new ConsoleBoardPresenter) {}

void GameManager::startGame() {
	setup();
	runGameLoop();
	cleanup();
}

void GameManager::setup() {

}

void GameManager::runGameLoop() {
	cout << "Game Loop Started";
	presenter->displayBoard(current_state.getBoard());
}

void GameManager::cleanup() {

}
