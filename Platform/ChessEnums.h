#pragma once

enum class PieceColor { WHITE, BLACK };
enum class SquareColor { LIGHT, DARK };
enum class PlayerTurn { WHITE, BLACK };

bool operator==(const PieceColor &piece_color, const PlayerTurn &player_turn);
bool operator==(const PlayerTurn &player_turn, const PieceColor &piece_color);
