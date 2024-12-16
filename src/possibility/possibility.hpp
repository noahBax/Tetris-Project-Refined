// possibility/possibility.hpp
#ifndef POSSIBILITY_HPP
#define POSSIBILITY_HPP

#include "piece.hpp"

class Possibility {

public:
	int pieceX;
	int pieceY;
	int pieceRots;

	double score;
	int linesCleared;
	bool hasTetris;

	Possibility(const Piece &pieceRef, const double score, const int linesCleared, const bool hasTetris);
	void resetTo(Piece &pieceRef, const double score, const int linesCleared, const bool hasTetris);
};

#endif // POSSIBILITY_HPP