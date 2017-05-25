#include <array>
#include <vector>
#include "Move.h"
#include "MoveInputParser.h"
using namespace std;


shared_ptr<const Move> MoveInputParser::parseMoveInput(string input) const {

	// find first two character pairs, space delimited
	vector<int> space_indexes;
	for (int i = 0; i < input.size(); i++) {
		char c = input[i];
		if (c == ' ') {
			space_indexes.emplace_back(i);
		}
	}
	space_indexes.emplace_back(input.size());

	vector<string> delimited_tokens;
	for (int i = 0; i < space_indexes.size(); i++) {
		int prev_index = -1;
		if (i != 0) {
			prev_index = space_indexes[i - 1];
		}
		int next_index = space_indexes[i];
		int length = next_index - prev_index - 1;
		string token = input.substr(prev_index + 1, length);
		if (!token.empty()) {
			delimited_tokens.emplace_back(token);
		}
	}

	// check for at least two coordinate pairs
	if (delimited_tokens.size() < 2) {
		return shared_ptr<const Move>(nullptr);
	}

	// turn each char pair into SquareCoordinates
	array<SquareCoordinate, 2> coords;
	for (int i = 0; i < 2; i++) {
		string token = delimited_tokens[i];
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
