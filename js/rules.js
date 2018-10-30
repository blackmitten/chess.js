"use strict"

function getLegalMovesPawn(board) {
    var moves = [];
    if (this.white) {
        if (this.y > 0) {
            if (board.getPieceOnSquare(this.x, this.y - 1) == undefined) {
                moves.push({ x: this.x, y: this.y - 1 });
            }
            if (this.y == 6) {
                if (board.getPieceOnSquare(this.x, this.y - 2) == undefined) {
                    moves.push({ x: this.x, y: this.y - 2 });
                }
            }
        }
    }
    else {
        if (this.y < 7) {
            if (board.getPieceOnSquare(this.x, this.y + 1) == undefined) {
                moves.push({ x: this.x, y: this.y + 1 });
            }
            if (this.y == 1) {
                if (board.getPieceOnSquare(this.x, this.y + 2) == undefined) {
                    moves.push({ x: this.x, y: this.y + 2 });
                }
            }
        }
    }
    return moves;
}

function getLegalMovesRook(board) {

}

function getLegalMovesKnight(board) {

}

function getLegalMovesBishop(board) {

}

function getLegalMovesQueen(board) {

}

function getLegalMovesKing(board) {

}
