#pragma once

#include <memory>
#include <string>
#include "ChessEnums.h"
#include "Player.h"
class Board;
class Move;


class HumanPlayer : public Player {

public:
	HumanPlayer(PieceColor color);
	std::shared_ptr<Move> makeMove(const GameState &state) const override;

private:
	std::shared_ptr<Move> askUserForMove() const;

};
