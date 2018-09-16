#pragma once

#include <memory>
#include "MoveEffect.h"
#include "Position.h"

namespace chess {

class Board;
enum class MoveEffectType;
class Pawn;


class EnPassant : public MoveEffect {

public:
    EnPassant(Position remove_position);
    std::unique_ptr<MoveEffect> getCopy() const override;
    bool operator==(const MoveEffect &other) const override;
    std::unique_ptr<Piece> applyEffect(Board &board) const override;
    void undoEffect(Board &board, std::unique_ptr<Piece> &piece) const override;
    MoveEffectType getType() const override;

private:
    Position remove_position;

};


}
