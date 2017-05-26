#pragma once

#include <memory>
#include <vector>
#include <string>
#include "SquareCoordinate.h"
class Move;


class MoveInputParser {

public:
	std::shared_ptr<const Move> parseMoveInput(std::string input) const;

private:
	std::vector<std::string> parseInputIntoTokens(std::string input, char delimiter) const;
	SquareCoordinate convertCharPairToCoords(std::string input) const;

};
