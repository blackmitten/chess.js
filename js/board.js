import * as Pieces from "./pieces.js";

export {Square};
export {Board};

"use strict";

function Square(x, y){
    this.x = x;
    this.y = y;
    
    this.equals = function( square ){
        return this.x==square.x&&this.y==square.y;
    };

    this.offset = function( dx, dy ){
        return new Square(this.x+dx,this.y+dy);
    }
}

function Board() {

    this.blackPieces = [];
    this.whitePieces = [];
    this.whitesTurn = true;

    this.initNewGame = function () {
        for (var p = 0; p < 8; p++) {
            this.blackPieces.push(new Pieces.Pawn(new Square(p, 1), false));
            this.whitePieces.push(new Pieces.Pawn(new Square(p, 6), true));
        }
        this.blackPieces.push(new Pieces.Rook(new Square(0, 0), false));
        this.blackPieces.push(new Pieces.Rook(new Square(7, 0), false));
        this.blackPieces.push(new Pieces.Knight(new Square(1, 0), false));
        this.blackPieces.push(new Pieces.Knight(new Square(6, 0), false));
        this.blackPieces.push(new Pieces.Bishop(new Square(2, 0), false));
        this.blackPieces.push(new Pieces.Bishop(new Square(5, 0), false));
        this.blackPieces.push(new Pieces.Queen(new Square(3, 0), false));
        this.blackPieces.push(new Pieces.King(new Square(4, 0), false));

        this.whitePieces.push(new Pieces.Rook(new Square(0, 7), true));
        this.whitePieces.push(new Pieces.Rook(new Square(7, 7), true));
        this.whitePieces.push(new Pieces.Knight(new Square(1, 7), true));
        this.whitePieces.push(new Pieces.Knight(new Square(6, 7), true));
        this.whitePieces.push(new Pieces.Bishop(new Square(2, 7), true));
        this.whitePieces.push(new Pieces.Bishop(new Square(5, 7), true));
        this.whitePieces.push(new Pieces.Queen(new Square(3, 7), true));
        this.whitePieces.push(new Pieces.King(new Square(4, 7), true));
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
        var pieceCopy = board.getPieceOnSquare(piece.square);

        pieceCopy.square = destinationSquare;
        board.whitesTurn = !board.whitesTurn;
        return board;
    };

    this.removePieceOnSquare = function (square) {
        for (var i = 0; i < this.blackPieces.length; i++) {
            if (square.equals( this.blackPieces[i].square) ) {
                this.blackPieces.splice(i, 1);
                break;
            }
        }
        for (i = 0; i < this.whitePieces.length; i++) {
            if (square.equals( this.whitePieces[i].square) ) {
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
            if (this.blackPieces[i].square.equals( square )) {
                piece = this.blackPieces[i];
                break;
            }
        }
        for (i = 0; i < this.whitePieces.length; i++) {
            if (this.whitePieces[i].square.equals(square)) {
                piece = this.whitePieces[i];
                break;
            }
        }
        return piece;
    };

}
