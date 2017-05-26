#include <array>
#include <vector>
#include "Move.h"
#include "MoveInputParser.h"
using namespace std;


shared_ptr<const Move> MoveInputParser::parseMoveInput(string input) const {
	shared_ptr<const Move> move(nullptr);

	vector<string> tokens = parseInputIntoTokens(input, ' ');
	if (tokens.size() < 2) {
		return move;
	}

	array<SquareCoordinate, 2> squares;
	for (int i = 0; i < 2; i++) {
		squares[i] = convertCharPairToCoords(tokens[i]);
		if (squares[i].empty()) {
			return move;
		}
	}

	move.reset(new Move(squares[0], squares[1]));
	return move;
}

vector<string> MoveInputParser::parseInputIntoTokens(string input, char delimiter) const {
	vector<string> tokens;
	input += delimiter;
	while (!input.empty()) {
		for (size_t i = 0; i < input.size(); i++) {
			char c = input[i];
			if (c == delimiter) {
				if (i != 0) {
					tokens.push_back(input.substr(0, i));
				}
				input = input.erase(0, i + 1);
			}
		}
	}
	return tokens;
}

SquareCoordinate MoveInputParser::convertCharPairToCoords(string input) const {
	SquareCoordinate coords;

	if (input.size() != 2) {
		return coords;
	}

	char first = input[0];
	if (first < 'A' || first > 'Z') {
		return coords;
	}
	int x_coord = first - 'A';

	char second = input[1];
	if (second < '1' || second > '9') {
		return coords;
	}
	int y_coord = second - '0' - 1;

	coords = { x_coord, y_coord };
	return coords;
}
