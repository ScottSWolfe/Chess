#include <iostream>
#include "ChessDebug.h"
#include "Board.h"
#include "HumanPlayer.h"
#include "Move.h"
#include "MoveInputParser.h"
#include "PlayerAction.h"
#include "Position.h"
using namespace std;


HumanPlayer::HumanPlayer(PieceColor color)
    : Player(color)
{}

shared_ptr<PlayerAction> HumanPlayer::getAction(const GameState &state) const {
    cout << "Enter a move: ";
    auto move = askUserForMove();
    while (move == nullptr) {
        cout << "Move not entered correctly. Try again:" << endl;
        move = askUserForMove();
    }
    return move;
}

shared_ptr<Move> HumanPlayer::askUserForMove() const {
    string input;
    getline(cin, input);
    MoveInputParser parser;
    return parser.parseMoveInput(input);
}

PieceType HumanPlayer::getPromotionPiece(const GameState &state, const Move &move) const {
    return getPromotionPiece();
}

PieceType HumanPlayer::getPromotionPiece() const {
    cout << "Choose a promotion piece (Q, R, B, N): ";
    string input;
    getline(cin, input);
    return parsePromotionPiece(input);
}

PieceType HumanPlayer::parsePromotionPiece(string input) const {
    if (input.size() != 1) {
        return getPromotionPiece();
    }
    char c = input[0];

    switch (c) {

    case 'Q':
        return PieceType::QUEEN;

    case 'R':
        return PieceType::ROOK;

    case 'B':
        return PieceType::BISHOP;

    case 'N':
        return PieceType::KNIGHT;

    default:
        return getPromotionPiece();
    }
}
