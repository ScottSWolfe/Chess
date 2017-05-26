#pragma once

struct SquareCoordinates {
	SquareCoordinates();
	SquareCoordinates(int x, int y);
	bool empty() const;
	int x;
	int y;
};
