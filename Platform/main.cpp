#include <iostream>
#include "Piece.h"
#include "Rook.h"
using namespace std;

int main() {
	cout << "Hello World of Chess!" << endl;
	Rook piece(Color::Black);
	cout << (int) piece.getColor() << endl;
	int input;
	cin >> input;
}
