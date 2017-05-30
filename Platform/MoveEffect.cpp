#include "MoveEffect.h"
#include "Piece.h"
using namespace std;


MoveEffect::MoveEffect(Position pos) 
	: position(pos), piece(nullptr)
{}

MoveEffect::MoveEffect(Position pos, unique_ptr<const Piece> &piece)
	: position(pos), piece(piece.release())
{}

MoveEffect::MoveEffect(const MoveEffect &other)
	: position(other.position), piece(other.getCopyOfPiece())
{}

bool MoveEffect::operator==(const MoveEffect &other) const {
	if (position != other.position) {
		return false;
	}
	if (Piece::getPieceSymbol(piece.get()) != Piece::getPieceSymbol(other.piece.get())) {
		return false;
	}
	return true;
}

Position MoveEffect::getPosition() const {
	return position;
}

unique_ptr<const Piece> MoveEffect::getCopyOfPiece() const {
	return Piece::copyPiece(piece.get());
}

unique_ptr<const MoveEffect> MoveEffect::getCopy() const {
	return make_unique<const MoveEffect>(position, getCopyOfPiece());
}
