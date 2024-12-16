#include "possibility.hpp"
#include "tetris_rules.hpp"

Possibility::Possibility(const Piece &pieceRef, const double score, const int linesCleared, const bool hasTetris) {
	this->pieceRots = pieceRef.rotations;
	this->pieceX = pieceRef.position[0];
	this->pieceY = pieceRef.position[1];

	this->score = score;
	this->linesCleared = linesCleared;
	this->hasTetris = hasTetris;
}

void Possibility::resetTo(Piece &pieceRef, const double score, const int linesCleared, const bool hasTetris) {
	this->pieceRots = pieceRef.rotations;
	this->pieceX = pieceRef.position[0];
	this->pieceY = pieceRef.position[1];

	this->score = score;
	this->linesCleared = linesCleared;
	this->hasTetris = hasTetris;
}