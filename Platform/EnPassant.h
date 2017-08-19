#pragma once

#include <memory>
#include "MoveEffect.h"
#include "Position.h"

namespace chess {

class Board;
enum class MoveEffectType;


class EnPassant : public MoveEffect {

public:
    EnPassant(Position remove_position);
    std::unique_ptr<MoveEffect> getCopy() const override;
    bool operator==(const MoveEffect &other) const override;
    void applyEffect(Board &board) const override;
    MoveEffectType getType() const override;

private:
    Position remove_position;

};


}
