#include <iostream>
#include "Piece.h"
using namespace std;

int main() {
	cout << "Hello World of Chess!" << endl;
	Piece piece(Color::Black);
	cout << (int) piece.getColor() << endl;
}
