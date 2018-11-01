"use strict"

function newBoard() {
    return {
        blackPieces: [],
        whitePieces: [],
        whitesTurn: true,

        movePiece: function (piece, destinationSquare) {
            var board = this.copy();
            var pieceCurrentlyOccupyingDestination = board.getPieceOnSquare(destinationSquare);
            if (pieceCurrentlyOccupyingDestination != undefined) {
                if (pieceCurrentlyOccupyingDestination.white != piece.white) {
                    board.removePieceOnSquare(destinationSquare);
                }
                else {
                    throw "tried to move to a square occupied by a piece on our own side";
                }
            }
            var pieceCopy = board.getPieceOnSquare({ x: piece.x, y: piece.y });

            pieceCopy.x = destinationSquare.x;
            pieceCopy.y = destinationSquare.y;
            board.whitesTurn = !board.whitesTurn;
            return board;
        },

        removePieceOnSquare: function (square) {
            for (var i = 0; i < this.blackPieces.length; i++) {
                if (square.x == this.blackPieces[i].x && square.y == this.blackPieces[i].y) {
                    this.blackPieces.splice(i, 1);
                    break;
                }
            }
            for (var i = 0; i < this.whitePieces.length; i++) {
                if (square.x == this.whitePieces[i].x && square.y == this.whitePieces[i].y) {
                    this.whitePieces.splice(i, 1);
                    break;
                }
            }
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

        getPieceOnSquare: function (square) {
            var piece = undefined;
            for (var i = 0; i < this.blackPieces.length; i++) {
                if (this.blackPieces[i].x == square.x && this.blackPieces[i].y == square.y) {
                    piece = this.blackPieces[i];
                    break;
                }
            }
            for (var i = 0; i < this.whitePieces.length; i++) {
                if (this.whitePieces[i].x == square.x && this.whitePieces[i].y == square.y) {
                    piece = this.whitePieces[i];
                    break;
                }
            }
            return piece;
        },
    };
}
