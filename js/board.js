import * as Pieces from "./pieces.js";

export {Board};

"use strict";


function Board() {

    this.blackPieces = [];
    this.whitePieces = [];
    this.whitesTurn = true;

    this.initNewGame = function () {
        for (var p = 0; p < 8; p++) {
            this.blackPieces.push(new Pieces.Pawn(p, 1, false));
            this.whitePieces.push(new Pieces.Pawn(p, 6, true));
        }
        this.blackPieces.push(new Pieces.Rook(0, 0, false));
        this.blackPieces.push(new Pieces.Rook(7, 0, false));
        this.blackPieces.push(new Pieces.Knight(1, 0, false));
        this.blackPieces.push(new Pieces.Knight(6, 0, false));
        this.blackPieces.push(new Pieces.Bishop(2, 0, false));
        this.blackPieces.push(new Pieces.Bishop(5, 0, false));
        this.blackPieces.push(new Pieces.Queen(3, 0, false));
        this.blackPieces.push(new Pieces.King(4, 0, false));

        this.whitePieces.push(new Pieces.Rook(0, 7, true));
        this.whitePieces.push(new Pieces.Rook(7, 7, true));
        this.whitePieces.push(new Pieces.Knight(1, 7, true));
        this.whitePieces.push(new Pieces.Knight(6, 7, true));
        this.whitePieces.push(new Pieces.Bishop(2, 7, true));
        this.whitePieces.push(new Pieces.Bishop(5, 7, true));
        this.whitePieces.push(new Pieces.Queen(3, 7, true));
        this.whitePieces.push(new Pieces.King(4, 7, true));
    };

    this.movePiece = function (piece, destinationSquare) {
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
    };

    this.removePieceOnSquare = function (square) {
        for (var i = 0; i < this.blackPieces.length; i++) {
            if (square.x == this.blackPieces[i].x && square.y == this.blackPieces[i].y) {
                this.blackPieces.splice(i, 1);
                break;
            }
        }
        for (i = 0; i < this.whitePieces.length; i++) {
            if (square.x == this.whitePieces[i].x && square.y == this.whitePieces[i].y) {
                this.whitePieces.splice(i, 1);
                break;
            }
        }
    };

    this.copy = function () {
        var board = new Board();
        for (var i = 0; i < this.blackPieces.length; i++) {
            board.blackPieces.push(this.blackPieces[i].copy());
        }
        for (i = 0; i < this.whitePieces.length; i++) {
            board.whitePieces.push(this.whitePieces[i].copy());
        }
        board.whitesTurn = this.whitesTurn;
        return board;
    };

    this.getPieceOnSquare = function (square) {
        var piece = undefined;
        for (var i = 0; i < this.blackPieces.length; i++) {
            if (this.blackPieces[i].x == square.x && this.blackPieces[i].y == square.y) {
                piece = this.blackPieces[i];
                break;
            }
        }
        for (i = 0; i < this.whitePieces.length; i++) {
            if (this.whitePieces[i].x == square.x && this.whitePieces[i].y == square.y) {
                piece = this.whitePieces[i];
                break;
            }
        }
        return piece;
    };

}
