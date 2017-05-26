#pragma once

struct SquareCoordinates {
	SquareCoordinates();
	SquareCoordinates(int x, int y);
	bool operator==(const SquareCoordinates &other_coordinates) const;
	bool empty() const;
	int x;
	int y;
};
