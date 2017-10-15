#pragma once

#include <memory>
#include <random>
#include <vector>
#include "Engine.h"
#include "Piece.h"

namespace chess {


class RandomEngine : public Engine {

public:
    RandomEngine(PieceColor color);
    std::shared_ptr<PlayerAction> getAction(const GameState &state) const;
    PieceType getPromotionPiece(const GameState &state, const Move &move) const;

private:
    PieceColor color;
    mutable std::random_device rand_int_device;

    void eliminateIllegalMoves(const GameState &state, std::vector<Move> &moves) const;
    int randomInteger(int max_int) const;

};


}
