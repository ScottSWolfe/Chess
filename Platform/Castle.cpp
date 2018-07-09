#include "Board.h"
#include "Castle.h"
#include "ChessDebug.h"

namespace chess {


Castle::Castle(Position rook_start, Position rook_end)
    : rook_start(rook_start), rook_end(rook_end)
{}

std::unique_ptr<MoveEffect> Castle::getCopy() const {
    return std::make_unique<Castle>(*this);
}

bool Castle::operator==(const MoveEffect &other) const {
    try {
        auto other_casted = dynamic_cast<const Castle&>(other);
        if (rook_start == other_casted.rook_start && rook_end == other_casted.rook_end) {
            return true;
        }
        return false;
    }
    catch (std::bad_cast) {
        return false;
    }
}

std::unique_ptr<Piece> Castle::applyEffect(Board &board) const {
    auto rook = board.removePieceFromSquare(rook_start);
    board.addPieceToSquare(rook_end, rook);
    return nullptr;
}

void Castle::undoEffect(Board &board, std::unique_ptr<Piece> & piece) const {
    auto rook = board.removePieceFromSquare(rook_end);
    board.addPieceToSquare(rook_start, rook);
}

MoveEffectType Castle::getType() const {
    return MoveEffectType::CASTLE;
}


}
