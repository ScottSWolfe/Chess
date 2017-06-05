#pragma once

enum class PieceType { PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING };
enum class PieceColor { WHITE, BLACK, NO_PIECE };
enum class SquareColor { LIGHT, DARK };
enum class GameEndType { WHITE_CHECKMATE, BLACK_CHECKMATE, WHITE_RESIGN, BLACK_RESIGN,
                         DRAW_AGREEMENT, DRAW_50_MOVES, DRAW_3_REPITITIONS, STALEMATE,
                         NOT_OVER };
