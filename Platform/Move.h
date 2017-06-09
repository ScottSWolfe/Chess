#pragma once

#include <memory>
#include "Position.h"
#include "MoveEffect.h"


class Move {

public:
    Move(Position start, Position end);
    Move(Position start, Position end, std::unique_ptr<MoveEffect> &effect);
    Move(const Move &other_move);
    Move &operator=(const Move &other);
    bool operator==(const Move &other) const;
    Position getStart() const;
    Position getEnd() const;
    bool hasEffect() const;
    const MoveEffect *getEffect() const;
    MoveEffectType getEffectType() const;
    void setPromotionPiece(PieceType type);
    std::unique_ptr<MoveEffect> getCopyOfEffect() const;

private:
    Position start;
    Position end;
    std::unique_ptr<MoveEffect> effect;

};
