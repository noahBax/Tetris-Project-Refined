#include <vector>
#include <iostream>
#include "piece.hpp"
#include "tetris_rules.hpp"

Piece::Piece(std::mt19937 &generator) {
	pieceNum = generator() % NUMBER_PIECES;
	shape = TETROMINOES[pieceNum];
}

/**
 * Pieces will always rotate clockwise
 */
void Piece::rotatePiece() {

	// Square tetromino doesn't change when rotated
	if (pieceNum == 3) return;

	const int size = shape.size();
	const Matrix backup = shape;

	rotations = (rotations + 1) % 4;

	for (int j = 0; j < size; j++) {
		for (int i = 0; i < size; i++) {
			shape[i][size - 1 - j] = backup[j][i];
		}
	}
}

bool Piece::canPieceFit(const TetrisBoard &board) const {

	const int size = shape.size();

	// Loop through rows in board and check to see if either or both are BLANK_SPACE
	for (int j = 0; j < size; j++) {

		// belowBoard pertains to the square on the TetrisBoard itself
		const bool belowBoard = position[1] + j >= BOARD_HEIGHT;
		for (int i = 0; i < size; i++) {

			const bool shapeIsBlock = shape[j][i] != BLANK_SPACE;
			
			if (shapeIsBlock) {
				const bool boardIsBlock = board[position[1] + j][position[0] + i] != BLANK_SPACE;
				const bool leftOfBoard  = position[0] + i < 0;
				const bool rightOfBoard = position[0] + i >= BOARD_WIDTH;

				if (leftOfBoard || rightOfBoard || boardIsBlock || belowBoard)
					return false;
			}
		}
	}

	return true;
	
}

bool Piece::movePieceDown(TetrisBoard &board) {

	if (!canPieceFit(board)) return false;

	position[1]++;

	if (canPieceFit(board))
		return true;
	
	// Undo changes if that failed
	position[1]--;
	return false;

}

int Piece::castPieceShadow(TetrisBoard &shadowBoard) {

	// Most of the time the board will be mostly empty right?
	// So let's try moving it up from the bottom instead of down from the top

	// We set it's position to 20, then move it up until it hits a place it can fit.
	// Additionally, I think it would be beneficial to try moving the piece up 4 blocks at a time
	// instead of just the 1. If we get to a place where the piece fits, try moving it down as normal
	// Bubble up instead of falling down, y'know

	// Moving down 4 blocks at a time does less comparisons if we can at least move it down twice.
	// Moving something down 4 then back up 3 blocks is 4 comparisons vs 1 comparisons
	// Moving something down 8 then up 3 times is 5 comparisons vs 5 comparisons
	// Moving something down 12 then up 3 times is 6 comparisons vs 9 comparisons
	// It looks like most configurations converge to having at least the bottom 8 rows full
	// so this'll most likely save comparisons

	const int originalY = position[1];

	position[1] = BOARD_HEIGHT;
	int movedDown = BOARD_HEIGHT;

	// Bubble up in chunks of 4 rows until the piece can fit
	while (!canPieceFit(shadowBoard)) {
		position[1] -= 4;
		movedDown -= 4;
	}

	// Fall down slowly
	while (movePieceDown(shadowBoard))
		movedDown++;

	// Draw the shadow onto the shadow board
	for (int j = 0; j < shape.size() && position[1] + j < BOARD_HEIGHT; j++) {

		for (int i = 0; i < shape.size() && position[0] + i < BOARD_WIDTH; i++) {

			if (shape[j][i] != BLANK_SPACE) {
				shadowBoard[position[1] + j][position[0] + i] = shape[j][i];
			}
		}
	}

	position[1] = originalY; // Restore the original position
	return movedDown;
}

void Piece::undoShadow(TetrisBoard &shadowBoard, const int timesDropped) const {
	
	int tempHeight = position[1] + timesDropped;
	
	// Un-draw the shadow onto the shadow board
	for (int j = 0; j < shape.size() && tempHeight + j < BOARD_HEIGHT; j++) {

		for (int i = 0; i < shape.size() && position[0] + i < BOARD_WIDTH; i++) {

			if (shape[j][i] != BLANK_SPACE) {
				shadowBoard[tempHeight + j][position[0] + i] = BLANK_SPACE;
			}
		}
	}

}

void Piece::print() const {
	for (int j = 0; j < shape.size(); j++) {
		for (int i = 0; i < shape.size(); i++) {
			if (shape[j][i] == BLANK_SPACE) std::cout << ".  ";
			else std::cout << shape[j][i] << ", ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}