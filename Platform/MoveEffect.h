#pragma once

#include <memory>
#include "Position.h"
#include "Piece.h"
struct Position;


enum class MoveEffectType { EN_PASSANT, PROMOTION, CASTLE };

class MoveEffect {

public:
    MoveEffect(Position pos, MoveEffectType type);
    MoveEffect(Position pos, std::unique_ptr<Piece> &piece, MoveEffectType type);
    MoveEffect(const MoveEffect &other);
    bool operator==(const MoveEffect &other) const;
    Position getPosition() const;
    std::unique_ptr<Piece> getCopyOfPiece() const;
    MoveEffectType getType() const;
    std::unique_ptr<const MoveEffect> getCopy() const;

private:
    const Position position;
    const std::unique_ptr<Piece> piece;
    const MoveEffectType type;

};
