#include "ChessEnums.h"

bool operator==(const PieceColor &piece_color, const PlayerTurn &player_turn) {
	if (piece_color == PieceColor::BLACK && player_turn == PlayerTurn::BLACK) {
		return true;
	}
	if (piece_color == PieceColor::WHITE && player_turn == PlayerTurn::WHITE) {
		return true;
	}
	return false;
}

bool operator==(const PlayerTurn &player_turn, const PieceColor &piece_color) {
	return piece_color == player_turn;
}
