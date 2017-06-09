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
    PieceType getPromotionPiece(const GameState &state, const Move &move) const override;

private:
    std::shared_ptr<Move> askUserForMove() const;
    PieceType getPromotionPiece() const;
    PieceType parsePromotionPiece(std::string input) const;

};
