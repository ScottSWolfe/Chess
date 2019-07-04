#include "CastlingAvailability.h"
#include "Piece.h"

namespace chess {


CastlingAvailability::CastlingAvailability() : 
    whiteKingside(true),
    whiteQueenside(true), 
    blackKingside(true), 
    blackQueenside(true)
{}

CastlingAvailability::CastlingAvailability(bool whiteKingside, bool whiteQueenside, bool blackKingside, bool blackQueenside) :
    whiteKingside(whiteKingside),
    whiteQueenside(whiteQueenside),
    blackKingside(blackKingside),
    blackQueenside(blackQueenside)
{}

bool CastlingAvailability::canCastle(const PieceColor color) const {
    return canCastleKingside(color) || canCastleQueenside(color);
}

bool CastlingAvailability::canCastleKingside(const PieceColor color) const {
    if (color == PieceColor::WHITE) {
        return whiteKingside;
    }
    else {
        return blackKingside;
    }
}

bool CastlingAvailability::canCastleQueenside(const PieceColor color) const {
    if (color == PieceColor::WHITE) {
        return whiteQueenside;
    }
    else {
        return blackQueenside;
    }
}

void CastlingAvailability::setCanCastle(const PieceColor color, const bool canCastle) {
    if (color == PieceColor::WHITE) {
        whiteKingside = canCastle;
        whiteQueenside = canCastle;
    }
    else if (color == PieceColor::BLACK) {
        blackKingside = canCastle;
        blackQueenside = canCastle;
    }
}

void CastlingAvailability::setCanCastleKingside(const PieceColor color, const bool canCastleKingside) {
    if (color == PieceColor::WHITE) {
        whiteKingside = canCastleKingside;
    }
    else if (color == PieceColor::BLACK) {
        blackKingside = canCastleKingside;
    }
}

void CastlingAvailability::setCanCastleQueenside(const PieceColor color, const bool canCastleQueenside) {
    if (color == PieceColor::WHITE) {
        whiteQueenside = canCastleQueenside;
    }
    else if (color == PieceColor::BLACK) {
        blackQueenside = canCastleQueenside;
    }
}

Position CastlingAvailability::getKingsideRookStartPosition(const PieceColor color) const {
    if (color == PieceColor::WHITE) {
        return white_kingside_rook_start_pos;
    }
    else {
        return black_kingside_rook_start_pos;
    }
}

Position CastlingAvailability::getQueensideRookStartPosition(const PieceColor color) const {
    if (color == PieceColor::WHITE) {
        return white_queenside_rook_start_pos;
    }
    else {
        return black_queenside_rook_start_pos;
    }
}


}
