"use strict"

function Pawn(x, y, white) {
    this.x = x;
    this.y = y;
    this.white = white;
    this.draw = drawPawn;
    this.name = "pawn";

    this.copy = function () {
        return new Pawn(this.x, this.y, this.white);
    };

    this.getLegalMoves = function (board) {
        var moves = [];
        if (this.white) {
            if (this.y > 0) {
                if (board.getPieceOnSquare({x:this.x, y:this.y - 1}) == undefined) {
                    moves.push({ x: this.x, y: this.y - 1 });
                    if (this.y == 6) {
                        if (board.getPieceOnSquare({x:this.x, y:this.y - 2}) == undefined) {
                            moves.push({ x: this.x, y: this.y - 2 });
                        }
                    }
                }
                var pieceToTake = board.getPieceOnSquare({x:this.x - 1, y:this.y - 1});
                if (pieceToTake != undefined && pieceToTake.white != this.white) {
                    moves.push({ x: this.x - 1, y: this.y - 1 });
                }
                pieceToTake = board.getPieceOnSquare({x:this.x + 1, y:this.y - 1});
                if (pieceToTake != undefined && pieceToTake.white != this.white) {
                    moves.push({ x: this.x + 1, y: this.y - 1 });
                }
            }
        }
        else {
            if (this.y < 7) {
                if (board.getPieceOnSquare({x:this.x, y:this.y + 1}) == undefined) {
                    moves.push({ x: this.x, y: this.y + 1 });
                    if (this.y == 1) {
                        if (board.getPieceOnSquare({x:this.x, y:this.y + 2}) == undefined) {
                            moves.push({ x: this.x, y: this.y + 2 });
                        }
                    }
                }
                var pieceToTake = board.getPieceOnSquare({x:this.x - 1, y:this.y + 1});
                if (pieceToTake != undefined && pieceToTake.white != this.white) {
                    moves.push({ x: this.x - 1, y: this.y + 1 });
                }
                pieceToTake = board.getPieceOnSquare({x:this.x - 1, y:this.y + 1});
                if (pieceToTake != undefined && pieceToTake.white != this.white) {
                    moves.push({ x: this.x + 1, y: this.y + 1 });
                }
            }
        }
        return moves;
    };

}

function Rook(x, y, white) {
    this.x = x;
    this.y = y;
    this.white = white;
    this.draw = drawRook;
    this.name = "rook";

    this.copy = function () {
        return new Rook(this.x, this.y, this.white);
    };

    this.getLegalMoves = function (board) {
        return [];
    }
}

function Knight(x, y, white) {
    this.x = x;
    this.y = y;
    this.white = white;
    this.draw = drawKnight;
    this.name = "Knight";

    this.copy = function () {
        return new Knight(this.x, this.y, this.white);
    };

    this.getLegalMoves = function (board) {
        return [];
    }

}

function Bishop(x, y, white) {
    this.x = x;
    this.y = y;
    this.white = white;
    this.draw = drawBishop;
    this.name = "Bishop";
    this.copy = function () {
        return new Bishop(this.x, this.y, this.white);
    };
    this.getLegalMoves = function (board) {
        return [];
    }

}

function Queen(x, y, white) {
    this.x = x;
    this.y = y;
    this.white = white;
    this.draw = drawQueen;
    this.name = "Queen";

    this.copy = function () {
        return new Queen(this.x, this.y, this.white);
    };

    this.getLegalMoves = function (board) {
        return [];
    }
}

function King(x, y, white) {
    this.x = x;
    this.y = y;
    this.white = white;
    this.draw = drawKing;
    this.name = "King";

    this.copy = function () {
        return new King(this.x, this.y, this.white);
    };

    this.getLegalMoves = function (board) {
        return [];
    }

}

