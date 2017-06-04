#include <iostream>
#include "ChessDebug.h"
#include "Board.h"
#include "HumanPlayer.h"
#include "Move.h"
#include "MoveInputParser.h"
#include "Position.h"
using namespace std;


HumanPlayer::HumanPlayer(PieceColor color)
    : Player(color)
{}

shared_ptr<Move> HumanPlayer::makeMove(const GameState &state) const {
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
