#pragma once

#include <memory>
#include "Engine.h"
#include "Piece.h"

namespace chess {


class BTREngine : public Engine {

public:
    std::shared_ptr<PlayerAction> getAction(const GameState &state) const override;
    PieceType getPromotionPiece(const GameState &state, const Move &move) const override;

};


}
