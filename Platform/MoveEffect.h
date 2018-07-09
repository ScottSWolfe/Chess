#pragma once

#include <memory>

namespace chess {

class Board;
class Piece;
struct Position;


enum class MoveEffectType { EN_PASSANT, PROMOTION, CASTLE };

class MoveEffect {

public:
    virtual std::unique_ptr<Piece> applyEffect(Board &board) const = 0;
    virtual void undoEffect(Board &board, std::unique_ptr<Piece> &piece) const = 0;
    virtual std::unique_ptr<MoveEffect> getCopy() const = 0;
    virtual MoveEffectType getType() const = 0;
    virtual bool operator==(const MoveEffect &other) const = 0;

};


}
