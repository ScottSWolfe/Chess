#pragma once

#include <memory>
#include "MoveEffect.h"
#include "Piece.h"
#include "Position.h"

namespace chess {

class Board;
enum class MoveEffectType;
class Piece;


class Promotion : public MoveEffect {

public:
    Promotion(Position promotion_position, PieceType piece_type);
    std::unique_ptr<MoveEffect> getCopy() const override;
    bool operator==(const MoveEffect &other) const override;
    std::unique_ptr<Piece> applyEffect(Board &board) const override;
    void undoEffect(Board &board, std::unique_ptr<Piece> &piece) const override;
    MoveEffectType getType() const override;
    void setPromotionPiece(PieceType type);
    PieceType getPromotionPieceType() const;

private:
    Position promotion_position;
    PieceType piece_type;

    std::unique_ptr<Piece> createNewPiece(const std::unique_ptr<Piece> &old_piece) const;

};


}
