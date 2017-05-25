#pragma once

#include <memory>
#include "ChessEnums.h"
#include "Move.h"
#include "Player.h"
class Board;


class HumanPlayer : public Player {

public:
	HumanPlayer(PieceColor color);
	std::shared_ptr<const Move> move(Board board) const override;

private:
	std::shared_ptr<const Move> askUserForMove() const;

};
