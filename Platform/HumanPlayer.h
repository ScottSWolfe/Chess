#pragma once

#include <memory>
#include <string>
#include "ChessEnums.h"
#include "MoveInputParser.h"
#include "OtherActionSelector.h"
#include "Player.h"
class Board;
class Move;


class HumanPlayer : public Player {

public:
    HumanPlayer(PieceColor color);
    std::shared_ptr<PlayerAction> getAction(const GameState &state) const override;
    PieceType getPromotionPiece(const GameState &state, const Move &move) const override;

private:
    std::shared_ptr<PlayerAction> HumanPlayer::getUserAction() const;
    std::shared_ptr<PlayerAction> getOther(std::string input) const;
    std::shared_ptr<Move> getMove(std::string input) const;
    PieceType getPromotionPiece() const;
    PieceType parsePromotionPiece(std::string input) const;

    MoveInputParser parser;
    OtherActionSelector selector;

};
