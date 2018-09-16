#include "ChessDebug.h"
#include "Piece.h"
#include "Promotion.h"
#include "Board.h"

namespace chess {


Promotion::Promotion(Position promotion_position, PieceType piece_type)
    : promotion_position(promotion_position), piece_type(piece_type)
{}

std::unique_ptr<MoveEffect> Promotion::getCopy() const {
    return std::make_unique<Promotion>(*this);
}

bool Promotion::operator==(const MoveEffect &other) const {
    try {
        auto other_casted = dynamic_cast<const Promotion&>(other);
        if (promotion_position == other_casted.promotion_position) {
            return true;
        }
        return false;
    }
    catch (std::bad_cast) {
        return false;
    }
}

std::unique_ptr<Piece> Promotion::applyEffect(Board &board) const {
    auto old_piece = board.removePieceFromSquare(promotion_position);
    auto new_piece = createNewPiece(old_piece);
    board.addPieceToSquare(promotion_position, new_piece);
    return old_piece;
}

void Promotion::undoEffect(Board &board, std::unique_ptr<Piece> &piece) const {
    board.removePieceFromSquare(promotion_position);
    board.addPieceToSquare(promotion_position, piece);
}

std::unique_ptr<Piece> Promotion::createNewPiece(const std::unique_ptr<Piece> &old_piece) const {
    auto new_piece = Piece::createPiece(piece_type, old_piece->getColor());
    new_piece->setTurnFirstMoved(old_piece->getTurnFirstMoved());
    new_piece->setHasMoved(true);
    return std::move(new_piece);
}

MoveEffectType Promotion::getType() const {
    return MoveEffectType::PROMOTION;
}

void Promotion::setPromotionPiece(PieceType type) {
    piece_type = type;
}

PieceType Promotion::getPromotionPieceType() const {
    return piece_type;
}


}
