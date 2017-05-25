#pragma once

#include <memory>
#include <string>
#include "SquareCoordinate.h"
class Move;


class MoveInputParser {

public:
	std::shared_ptr<const Move> parseMoveInput(std::string input) const;

};
