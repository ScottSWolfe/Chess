#pragma once

#include <memory>
#include "ChessEnums.h"
#include "MoveEffect.h"
#include "Position.h"
class Board;
enum class MoveEffectType;


class Promotion : public MoveEffect {

public:
    Promotion(Position promotion_position, PieceType piece_type);
    std::unique_ptr<MoveEffect> getCopy() const override;
    bool operator==(const MoveEffect &other) const override;
    void applyEffect(Board &board) const override;
    MoveEffectType getType() const override;
    void setPromotionPiece(PieceType type);

private:
    Position promotion_position;
    PieceType piece_type;

};
