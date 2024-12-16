// piece/piece.hpp
#ifndef PIECE_HPP
#define PIECE_HPP
#include "src/tetris_rules.hpp"
#include <random>
#include <vector>

const std::array<Matrix, 7> TETROMINOES = {
	Matrix{
		/* cyan */
		{{ 7, 7, 7, 7 }},
		{{ 0, 0, 0, 0 }},
		{{ 7, 7, 7, 7 }},
		{{ 7, 7, 7, 7 }},
	},
	Matrix{
		/* "blue" */
		{{ 1, 7, 7 }},
		{{ 1, 1, 1 }},
		{{ 7, 7, 7 }},
	},
	Matrix{
		/* "orange" */
		{{ 7, 7, 2 }},
		{{ 2, 2, 2 }},
		{{ 7, 7, 7 }},
	},
	Matrix{
		/* "yellow" */
		{{ 3, 3 }}, 
		{{ 3, 3 }},
	},
	Matrix{
		/* "green" */
		{{ 7, 4, 4 }},
		{{ 4, 4, 7 }},
		{{ 7, 7, 7 }},
	},
	Matrix{
		/* "purple" */
		{{ 7, 5, 7 }},
		{{ 5, 5, 5 }},
		{{ 7, 7, 7 }},
	},
	Matrix{
		/* "red" */
		{{ 6, 6, 7 }},
		{{ 7, 6, 6 }},
		{{ 7, 7, 7 }},
	}
};

class Piece {

public:
	Matrix shape;
	int position[2] = {3, 0};
	int rotations = 0;
	int pieceNum;

	Piece(std::mt19937 &generator);

	void rotatePiece();
	bool canPieceFit(const TetrisBoard &board) const;
	bool movePieceDown(TetrisBoard &board);
	int  castPieceShadow(TetrisBoard &shadowBoard);
	void undoShadow(TetrisBoard &shadowBoard, const int timesDropped) const;
	void print() const;
};
#endif // PIECE_HPP