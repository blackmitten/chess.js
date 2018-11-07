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

    this.isMoveValid = function (board, square) {
        if (!isMoveValidGeneric(this, board, square)) {
            return false;
        }
        var dir = white ? -1 : 1;
        var dx = (square.x - this.square.x);
        var dy = (square.y - this.square.y);
        if (dy * dir > 2) {
            // can never go further than two spaces
            return false;
        }
        if (dy * dir <= 0) {
            // mustn't go backwards
            return false;
        }
        if (dy * dir > 1 && this.square.y != (white ? 6 : 1)) {
            // can go two spaces if we haven't moved
            return false;
        }
        var capturedPiece = board.getPieceOnSquare(square);
        if (dx == 0 && capturedPiece != null) {
            // can't take forwards
            return false;
        }
        if (dx != 0 && (capturedPiece == null) || Math.abs(dx) > 1) {
            // can take diagonally
            return false;
        }

        return isNothingInTheWay(board, this, square);
    };

    this.getLegalMoves = function (board) {
        var moves = [];
        var dir = this.white ? -1 : 1;
        addMove(this, board, moves, this.square.offset(0, dir * 1));
        addMove(this, board, moves, this.square.offset(0, dir * 2));
        addMove(this, board, moves, this.square.offset(1, dir * 1));
        addMove(this, board, moves, this.square.offset(-1, dir * 1));

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
        var x = this.square.x;
        var y = this.square.y;
        while (addMove(this, board, moves, new Square(++x, y)));
        x = this.square.x;
        y = this.square.y;
        while (addMove(this, board, moves, new Square(--x, y)));
        x = this.square.x;
        y = this.square.y;
        while (addMove(this, board, moves, new Square(x, ++y)));
        x = this.square.x;
        y = this.square.y;
        while (addMove(this, board, moves, new Square(x, --y)));

        return moves;
    };
}

function inBounds(square) {
    return (square.x >= 0 && square.x <= 7 && square.y >= 0 && square.y <= 7);
}

function addMove(piece, board, moves, square) {
    if (square.equals(piece.square)) {
        return true;
    }
    if (inBounds(square) && piece.isMoveValid(board, square)) {
        moves.push(square);
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

function isMoveValidGeneric(piece, board, square) {
    var valid = inBounds(square);
    var pieceCaptured = board.getPieceOnSquare(square);
    if (pieceCaptured != null) {
        if (pieceCaptured.white == piece.white) {
            // can't capture our own guys
            valid = false;
        }
    }
    return valid;
}

function isNothingInTheWay(board, piece, square) {
    var dx = square.x - piece.square.x;
    var dy = square.y - piece.square.y;
    var xinc = (dx == 0) ? 0 : ((dx < 0) ? -1 : 1);  // ie. either no horizontal move or left / right
    var yinc = (dy == 0) ? 0 : ((dy < 0) ? -1 : 1);  // ie. either no vertical move or up / down

    if (xinc == 0 && yinc == 0) {
        throw ("something's way wrong here");
    }
    var s = piece.square;
    var foundSomeone = false;
    do {    // walk in the specified direction until we get there or we find a piece
        s = s.offset(xinc, yinc);
        if (s.equals(square)) {
            return true;
        }
        if (board.getPieceOnSquare(s)) {
            foundSomeone = true;
        }
    } while (!foundSomeone);

    return false;
}