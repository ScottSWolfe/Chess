#include "Board.h"
#include "ChessDebug.h"
#include "EnPassant.h"

namespace chess {


EnPassant::EnPassant(Position remove_position)
    : remove_position(remove_position)
{}

std::unique_ptr<MoveEffect> EnPassant::getCopy() const {
    return std::make_unique<EnPassant>(*this);
}

bool EnPassant::operator==(const MoveEffect &other) const {
    try {
        auto other_casted = dynamic_cast<const EnPassant&>(other);
        if (remove_position == other_casted.remove_position) {
            return true;
        }
        return false;
    }
    catch (std::bad_cast) {
        return false;
    }
}

void EnPassant::applyEffect(Board &board) const {
    board.removePieceFromSquare(remove_position);
}

MoveEffectType EnPassant::getType() const {
    return MoveEffectType::EN_PASSANT;
}


}
