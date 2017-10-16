#pragma once

#include "Engine.h"
#include "Player.h"

namespace chess {



class ComputerPlayer : public Player {

public:
    ComputerPlayer(PieceColor color, Engine *engine);
    std::shared_ptr<PlayerAction> getAction(const GameState &state) const override;
    PieceType getPromotionPiece(const GameState &state, const Move &move) const override;

private:
    std::unique_ptr<Engine> engine;

};


}
