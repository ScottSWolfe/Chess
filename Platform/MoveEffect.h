#pragma once

#include <memory>
class Board;
struct Position;

namespace chess {


enum class MoveEffectType { EN_PASSANT, PROMOTION, CASTLE };

class MoveEffect {

public:
    virtual void applyEffect(Board &board) const = 0;
    virtual std::unique_ptr<MoveEffect> getCopy() const = 0;
    virtual MoveEffectType getType() const = 0;
    virtual bool operator==(const MoveEffect &other) const = 0;

};


}
