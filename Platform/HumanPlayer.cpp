#include <iostream>
#include "Board.h"
#include "HumanPlayer.h"
#include "Move.h"
#include "SquareCoordinate.h"
using namespace std;


HumanPlayer::HumanPlayer(PieceColor color) : Player(color) {}

Move HumanPlayer::move(Board board) const {
	// temporary
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

	SquareCoordinate start = {start_x, start_y};
	SquareCoordinate end = { end_x, end_y };
	Move move(start, end);

	return move;
}
