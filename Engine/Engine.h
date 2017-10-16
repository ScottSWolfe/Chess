#pragma once

#include <memory>
#include "PlayerAction.h"

namespace chess {

class GameState;
class Move;
enum class PieceType;


class Engine {

public:
    virtual std::shared_ptr<PlayerAction> getAction(const GameState &state) const = 0;
    virtual PieceType getPromotionPiece(const GameState &state, const Move &move) const = 0;

};


}
