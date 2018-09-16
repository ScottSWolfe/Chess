#pragma once

#include <memory>
#include "MoveEffect.h"
#include "Position.h"

namespace chess {

class Board;
enum class MoveEffectType;
class Piece;


class Castle : public MoveEffect {

public:
    Castle(Position rook_start, Position rook_end);
    std::unique_ptr<Piece> applyEffect(Board &board) const override;
    void undoEffect(Board &board, std::unique_ptr<Piece> &piece) const override;
    std::unique_ptr<MoveEffect> getCopy() const override;
    bool operator==(const MoveEffect &other) const override;
    MoveEffectType getType() const override;

private:
    Position rook_start;
    Position rook_end;

};


}
