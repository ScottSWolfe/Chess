#include "ChessDebug.h"
#include "Piece.h"
#include "Promotion.h"
#include "Board.h"
using namespace std;


Promotion::Promotion(Position promotion_position, PieceType piece_type)
    : promotion_position(promotion_position), piece_type(piece_type)
{}

unique_ptr<MoveEffect> Promotion::getCopy() const {
    return make_unique<Promotion>(*this);
}

bool Promotion::operator==(const MoveEffect &other) const {
    try {
        auto other_casted = dynamic_cast<const Promotion&>(other);
        if (promotion_position == other_casted.promotion_position) {
            return true;
        }
        return false;
    }
    catch (bad_cast) {
        return false;
    }
}

void Promotion::applyEffect(Board &board) const {
    auto old_piece = board.removePieceFromSquare(promotion_position);
    auto new_piece = Piece::createPiece(piece_type, old_piece->getColor());
    board.addPieceToSquare(promotion_position, new_piece);
}

MoveEffectType Promotion::getType() const {
    return MoveEffectType::PROMOTION;
}

void Promotion::setPromotionPiece(PieceType type) {
    piece_type = type;
}
