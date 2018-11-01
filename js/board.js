"use strict"

function newBoard() {
    return {
        blackPieces: [],
        whitePieces: [],
        whitesTurn: true,

        movePiece: function (piece, destinationSquare) {
            var board = this.copy();
            var pieceCopy = board.getPieceOnSquare(piece.x, piece.y);
            pieceCopy.x = destinationSquare.x;
            pieceCopy.y = destinationSquare.y;
            board.whitesTurn = !board.whitesTurn;
            return board;
        },
        copy: function () {
            board = newBoard();
            for (var i = 0; i < this.blackPieces.length; i++) {
                board.blackPieces.push(this.blackPieces[i].copy());
            }
            for (var i = 0; i < this.whitePieces.length; i++) {
                board.whitePieces.push(this.whitePieces[i].copy());
            }
            board.whitesTurn = this.whitesTurn;
            return board;
        },

        getPieceOnSquare: getPieceOnSquare,
    };
}

function getPieceOnSquare(x, y) {
    var piece = undefined;
    for (var i = 0; i < this.blackPieces.length; i++) {
        if (this.blackPieces[i].x == x && this.blackPieces[i].y == y) {
            piece = this.blackPieces[i];
            break;
        }
    }
    for (var i = 0; i < this.whitePieces.length; i++) {
        if (this.whitePieces[i].x == x && this.whitePieces[i].y == y) {
            piece = this.whitePieces[i];
            break;
        }
    }
    return piece;
}

