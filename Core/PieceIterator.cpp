#include "PieceIterator.h"

namespace chess {


PieceIterator::PieceIterator(const Board &board, PieceColor color)
    : board(board), color(color), current_pos(0, 0)
{}

const Piece *PieceIterator::next() {
    for (int i = current_pos.y; i < board.getDimension(); i++) {
        for (int j = current_pos.x; j < board.getDimension(); j++) {
            if (board.isPiece(current_pos) && board.getPieceColor(current_pos) == color) {
                const Piece *piece = board.getPiece(current_pos);
                incrementCurrentPosition();
                return piece;
            }
            incrementCurrentPosition();
        }
    }
    return nullptr;
}

bool PieceIterator::hasNext() {
    for (int i = current_pos.y; i < board.getDimension(); i++) {
        for (int j = current_pos.x; j < board.getDimension(); j++) {
            if (board.isPiece(current_pos) && board.getPieceColor(current_pos) == color) {
                return true;
            }
            incrementCurrentPosition();
        }
    }
    return false;
}

void PieceIterator::incrementCurrentPosition() {
    if (current_pos.x < board.getDimension() - 1) {
        current_pos = current_pos.add(1, 0);
    }
    else {
        current_pos.x = 0;
        current_pos.y += 1;
    }
}


}
