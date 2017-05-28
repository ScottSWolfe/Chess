#include "ChessDebug.h"
#include "Move.h"


Move::Move(Position start_coord, Position end_coord)
	: start(start_coord), end(end_coord)
{}

Position Move::getStart() const {
	return start;
}

Position Move::getEnd() const {
	return end;
}

bool operator==(const Move &left, const Move &right) {
	if (left.start == right.start &&
		left.end == right.end)
	{
		return true;
	}
	return false;
}
