#pragma once

#include <memory>
#include "ChessEnums.h"
#include "Board.h"
#include "Player.h"
#include "HumanPlayer.h"


class GameState {

public:
	GameState();
	const Board &getBoard() const;
	const Player &getCurrentPlayer() const;

private:
	std::unique_ptr<Board> board;
	std::unique_ptr<Player> white_player;
	std::unique_ptr<Player> black_player;
	PlayerTurn current_player;

};
