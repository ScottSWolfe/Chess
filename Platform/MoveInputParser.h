#pragma once

#include <memory>
#include <vector>
#include <string>
#include "SquareCoordinates.h"
class Move;


class MoveInputParser {

public:
	std::shared_ptr<const Move> parseMoveInput(std::string input) const;

private:
	std::vector<std::string> parseInputIntoTokens(std::string input, char delimiter) const;
	SquareCoordinates convertCharPairToCoords(std::string input) const;

};
