#pragma once

#include <memory>
#include <random>
#include <vector>
#include "Engine.h"
#include "Piece.h"

namespace chess {


class RandomEngine : public Engine {

public:
    RandomEngine();
    std::shared_ptr<PlayerAction> getAction(const GameState &state) const override;
    PieceType getPromotionPiece(const GameState &state, const Move &move) const override;

private:
    mutable std::random_device rand_int_device;

    int randomInteger(int max_int) const;

};


}
