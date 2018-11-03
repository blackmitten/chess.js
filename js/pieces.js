import * as Drawing from "./drawing.js";
import { Square } from "./board.js";

"use strict";

export { Pawn };
export { Rook };
export { Knight };
export { Bishop };
export { Queen };
export { King };


function Pawn(square, white) {
    this.square = square;
    this.white = white;
    this.draw = Drawing.drawPawn;
    this.name = "pawn";

    this.copy = function () {
        return new Pawn(this.square, this.white);
    };

    this.getLegalMoves = function (board) {
        var moves = [];
        var pieceToTake;
        if (this.white) {
            if (this.square.y > 0) {
                if (board.getPieceOnSquare(this.square.offset(0,-1)) == undefined) {
                    moves.push(this.square.offset(0,-1));
                    if (this.square.y == 6) {
                        if (board.getPieceOnSquare(this.square.offset(0,-2)) == undefined) {
                            moves.push(this.square.offset(0,-2));
                        }
                    }
                }
                pieceToTake = board.getPieceOnSquare(this.square.offset(-1,-1));
                if (pieceToTake != undefined && pieceToTake.white != this.white) {
                    moves.push(this.square.offset(-1,-1));
                }
                pieceToTake = board.getPieceOnSquare(this.square.offset(1,-1));
                if (pieceToTake != undefined && pieceToTake.white != this.white) {
                    moves.push(this.square.offset(1,-1));
                }
            }
        }
        else {
            if (this.square.y < 7) {
                if (board.getPieceOnSquare(this.square.offset(0,1)) == undefined) {
                    moves.push(this.square.offset(0,1));
                    if (this.square.y == 1) {
                        if (board.getPieceOnSquare(this.square.offset(0,2)) == undefined) {
                            moves.push(this.square.offset(0,2));
                        }
                    }
                }
                pieceToTake = board.getPieceOnSquare(this.square.offset(-1,1));
                if (pieceToTake != undefined && pieceToTake.white != this.white) {
                    moves.push(this.square.offset(-1,1));
                }
                pieceToTake = board.getPieceOnSquare(this.square.offset(1,1));
                if (pieceToTake != undefined && pieceToTake.white != this.white) {
                    moves.push(this.square.offset(1,1));
                }
            }
        }
        return moves;
    };

}

function Rook(square, white) {
    this.square = square;
    this.white = white;
    this.draw = Drawing.drawRook;
    this.name = "rook";

    this.copy = function () {
        return new Rook(this.square, this.white);
    };

    this.getLegalMoves = function (board) {
        var moves = [];
        var x=this.square.x;
        var y=this.square.y;
        while(addMoveIfOk(this, board, moves, new Square( ++x, y )));
        x=this.square.x;
        y=this.square.y;
        while(addMoveIfOk(this, board, moves, new Square( --x, y )));
        x=this.square.x;
        y=this.square.y;
        while(addMoveIfOk(this, board, moves, new Square( x, ++y )));
        x=this.square.x;
        y=this.square.y;
        while(addMoveIfOk(this, board, moves, new Square( x, --y )));

        return moves;
    };
}

function addMoveIfOk(piece, board, moves, square) {
    if ( square.x < 0 || square.x > 7 || square.y < 0 || square.y > 7 ){
        return false;
    }
    var pieceOnSquare = board.getPieceOnSquare(square);
    if (pieceOnSquare == undefined) {
        moves.push( square );
        return true;
    }
    else if (piece.white != pieceOnSquare.white) {
        moves.push( square );
        return true;
    }
    return false;
}

function Knight(square, white) {
    this.square = square;
    this.white = white;
    this.draw = Drawing.drawKnight;
    this.name = "Knight";

    this.copy = function () {
        return new Knight(this.square, this.white);
    };

    this.getLegalMoves = function (board) {
        return [];
    };

}

function Bishop(square, white) {
    this.square = square;
    this.white = white;
    this.draw = Drawing.drawBishop;
    this.name = "Bishop";
    this.copy = function () {
        return new Bishop(this.square, this.white);
    };
    this.getLegalMoves = function (board) {
        return [];
    };

}

function Queen(square, white) {
    this.square = square;
    this.white = white;
    this.draw = Drawing.drawQueen;
    this.name = "Queen";

    this.copy = function () {
        return new Queen(this.square, this.white);
    };

    this.getLegalMoves = function (board) {
        return [];
    };
}

function King(square, white) {
    this.square = square;
    this.white = white;
    this.draw = Drawing.drawKing;
    this.name = "King";

    this.copy = function () {
        return new King(this.square, this.white);
    };

    this.getLegalMoves = function (board) {
        return [];
    };

}
