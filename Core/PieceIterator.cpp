#include "PieceIterator.h"

namespace chess {


PieceIterator::PieceIterator(const Board &board, PieceColor color)
    : board(board), color(color), current_pos(0, 0)
{}

const Piece *PieceIterator::next() {
    return nextWithPosition().first;
}

const std::pair<const Piece *, const Position> PieceIterator::nextWithPosition() {
    for (int i = current_pos.y; i < board.getDimension(); i++) {
        for (int j = current_pos.x; j < board.getDimension(); j++) {
            if (board.isPiece(current_pos) && board.getPieceColor(current_pos) == color) {
                const Piece *piece = board.getPiece(current_pos);
                const Position piece_position = current_pos;
                incrementCurrentPosition();
                return std::make_pair(piece, piece_position);
            }
            incrementCurrentPosition();
        }
    }
    throw std::runtime_error("there are no more pieces to iterate through");
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
