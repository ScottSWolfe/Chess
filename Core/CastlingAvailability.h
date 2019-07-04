#pragma once

#include "Position.h"

namespace chess {


enum class PieceColor;

class CastlingAvailability {

private:
    bool whiteKingside;
    bool whiteQueenside;
    bool blackKingside;
    bool blackQueenside;
    Position white_kingside_rook_start_pos;
    Position white_queenside_rook_start_pos;
    Position black_kingside_rook_start_pos;
    Position black_queenside_rook_start_pos;

public:
    CastlingAvailability();
    CastlingAvailability(bool whiteKingside, bool whiteQueenside, bool blackKingside, bool blackQueenside);
    bool canCastle(const PieceColor color) const;
    bool canCastleKingside(const PieceColor color) const;
    bool canCastleQueenside(const PieceColor color) const;
    void setCanCastle(const PieceColor color, const bool canCastle);
    void setCanCastleKingside(const PieceColor color, const bool canCastleKingside);
    void setCanCastleQueenside(const PieceColor color, const bool canCastleQueenside);
    Position getKingsideRookStartPosition(const PieceColor color) const;
    Position getQueensideRookStartPosition(const PieceColor color) const;

};


}
