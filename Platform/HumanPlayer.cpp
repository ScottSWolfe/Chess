#include <iostream>
#include "Board.h"
#include "HumanPlayer.h"
#include "Move.h"
#include "SquareCoordinates.h"
using namespace std;


HumanPlayer::HumanPlayer(PieceColor color) : Player(color) {}

shared_ptr<const Move> HumanPlayer::move(Board board) const {	
	return askUserForMove();
}

shared_ptr<const Move> HumanPlayer::askUserForMove() const {

	cout << "Enter start x coord: ";
	int start_x;
	cin >> start_x;

	cout << "Enter start y coord: ";
	int start_y;
	cin >> start_y;

	cout << "Enter end x coord: ";
	int end_x;
	cin >> end_x;

	cout << "Enter end y coord: ";
	int end_y;
	cin >> end_y;

	cout << endl;

	SquareCoordinates start = { start_x, start_y };
	SquareCoordinates end = { end_x, end_y };
	return make_shared<const Move>(start, end);
}
