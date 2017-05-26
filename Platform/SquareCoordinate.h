#pragma once

struct SquareCoordinate {
	SquareCoordinate();
	SquareCoordinate(int x, int y);
	bool empty() const;
	int x;
	int y;
};
