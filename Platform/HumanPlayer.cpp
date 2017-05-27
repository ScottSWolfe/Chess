#include <iostream>
#include "ChessDebug.h"
#include "Board.h"
#include "HumanPlayer.h"
#include "Move.h"
#include "MoveInputParser.h"
#include "SquareCoordinates.h"
using namespace std;


HumanPlayer::HumanPlayer(PieceColor color)
	: Player(color)
{}

shared_ptr<const Move> HumanPlayer::move(Board board) const {
	shared_ptr<const Move> move;
	while(move == nullptr) {
		move = askUserForMove();
	}
	return move;
}

shared_ptr<const Move> HumanPlayer::askUserForMove() const {
	string input;
	cout << "Enter a move (e.g., 'D2 D4'): " << endl;
	getline(cin, input);
	MoveInputParser parser;
	return parser.parseMoveInput(input);;
}
