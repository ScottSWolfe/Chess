#include <array>
#include <vector>
#include "Move.h"
#include "MoveInputParser.h"
using namespace std;


shared_ptr<const Move> MoveInputParser::parseMoveInput(string input) const {

	// parse input into tokens
	vector<string> tokens;
	input.append(" ");
	while (!input.empty()) {
		for (int i = 0; i < input.size(); i++) {
			char c = input[i];
			if (c == ' ') {
				if (i != 0) {
					tokens.emplace_back(input.substr(0, i));
				}
				input = input.erase(0, i + 1);
			}
		}
	}

	// check that there are at least two coordinate pairs
	if (tokens.size() < 2) {
		return shared_ptr<const Move>(nullptr);
	}

	// turn each char pair into SquareCoordinates
	array<SquareCoordinate, 2> coords;
	for (int i = 0; i < 2; i++) {
		string token = tokens[i];
		if (token.size() != 2) {
			return shared_ptr<const Move>(nullptr);
		}
		char first = token[0];
		if (first < 65 || first > 90) {
			return shared_ptr<const Move>(nullptr);
		}
		int x_coord = first - 65;

		char second = token[1];
		if (second < 49 || second > 57) {
			return shared_ptr<const Move>(nullptr);
		}
		int y_coord = second - 48 - 1;

		SquareCoordinate coord = { x_coord, y_coord };
		coords[i] = coord;
	}

	// create move from SquareCoordinates
	return make_shared<const Move>(coords[0], coords[1]);
}
