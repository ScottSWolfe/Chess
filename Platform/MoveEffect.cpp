#include "MoveEffect.h"
#include "Piece.h"
using namespace std;


MoveEffect::MoveEffect(Position pos, MoveEffectType type)
    : position(pos), piece(nullptr), type(type)
{}

MoveEffect::MoveEffect(Position pos, unique_ptr<Piece> &piece, MoveEffectType type)
    : position(pos), piece(piece.release()), type(type)
{}

MoveEffect::MoveEffect(const MoveEffect &other)
    : position(other.position), piece(other.getCopyOfPiece()), type(other.type)
{}

bool MoveEffect::operator==(const MoveEffect &other) const {
    if (position != other.position) {
        return false;
    }
    if (Piece::getPieceSymbol(piece.get()) != Piece::getPieceSymbol(other.piece.get())) {
        return false;
    }
    if (type != other.type) {
        return false;
    }
    return true;
}

Position MoveEffect::getPosition() const {
    return position;
}

unique_ptr<Piece> MoveEffect::getCopyOfPiece() const {
    return Piece::copyPiece(piece.get());
}

MoveEffectType MoveEffect::getType() const {
    return type;
}

unique_ptr<const MoveEffect> MoveEffect::getCopy() const {
    return make_unique<const MoveEffect>(position, getCopyOfPiece(), type);
}
