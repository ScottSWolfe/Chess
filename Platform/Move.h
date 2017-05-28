#pragma once

#include "Position.h"


class Move {

public:
	Move(Position start, Position end);
	friend bool operator==(const Move &left, const Move &right);
	Position getStart() const;
	Position getEnd() const;

private:
	Position start;
	Position end;

};

bool operator==(const Move &left, const Move &right);
