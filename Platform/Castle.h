#pragma once

#include <memory>
#include "MoveEffect.h"
#include "Position.h"
class Board;
enum class MoveEffectType;


class Castle : public MoveEffect {

public:
    Castle(Position rook_start, Position rook_end);
    void applyEffect(Board &board) const override;
    std::unique_ptr<const MoveEffect> getCopy() const override;
    bool operator==(const MoveEffect &other) const override;
    MoveEffectType getType() const override;

private:
    Position rook_start;
    Position rook_end;

};
