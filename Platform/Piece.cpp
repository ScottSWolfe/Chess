#include <memory>
#include <string>
#include "ChessDebug.h"
#include "Bishop.h"
#include "Knight.h"
#include "King.h"
#include "Pawn.h"
#include "Piece.h"
#include "Queen.h"
#include "Rook.h"
using namespace std;


Piece::Piece(PieceColor piece_color) : color(piece_color) {}

PieceColor Piece::getColor() const {
	return Piece::color;
}

const std::string Piece::getPieceSymbol(const Piece *piece) {
	if (piece == nullptr) {
		return " ";
	}
	else {
		return piece->getSymbol();
	}
}

PieceColor getPieceColor(const Piece *piece) {
	if (piece == nullptr) {
		return PieceColor::WHITE;
	}
	else {
		return piece->getColor();
	}
}

unique_ptr<const Piece> copyPieceFactory(const Piece *piece) {
	if (!piece) {
		return nullptr;
	}
	if (dynamic_cast<const Pawn*>(piece)) {
		return make_unique<const Pawn>(piece->getColor());
	}
	if (dynamic_cast<const Bishop*>(piece)) {
		return make_unique<const Bishop>(piece->getColor());
	}
	if (dynamic_cast<const Knight*>(piece)) {
		return make_unique<const Knight>(piece->getColor());
	}
	if (dynamic_cast<const Rook*>(piece)) {
		return make_unique<const Rook>(piece->getColor());
	}
	if (dynamic_cast<const Queen*>(piece)) {
		return make_unique<const Queen>(piece->getColor());
	}
	if (dynamic_cast<const King*>(piece)) {
		return make_unique<const King>(piece->getColor());
	}
	return nullptr;
}
