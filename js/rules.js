"use strict"

function newPawn(x, y, white)
{
    return{
        x: x,
        y: y,
        white: white,
        draw: drawPawn,
        name: "pawn", 

        copy: function(){
            return newPawn(this.x,this.y,this.white);
        },

        getLegalMoves: function(board){
            var moves = [];
            if (this.white) {
                if (this.y > 0) {
                    if (board.getPieceOnSquare(this.x, this.y - 1) == undefined) {
                        moves.push({ x: this.x, y: this.y - 1 });
                        if (this.y == 6) {
                            if (board.getPieceOnSquare(this.x, this.y - 2) == undefined) {
                                moves.push({ x: this.x, y: this.y - 2 });
                            }
                        }
                    }
                }
            }
            else {
                if (this.y < 7) {
                    if (board.getPieceOnSquare(this.x, this.y + 1) == undefined) {
                        moves.push({ x: this.x, y: this.y + 1 });
                        if (this.y == 1) {
                            if (board.getPieceOnSquare(this.x, this.y + 2) == undefined) {
                                moves.push({ x: this.x, y: this.y + 2 });
                            }
                        }
                    }
                }
            }
            return moves;
        }
    }
}

function newRook(x,y,white)
{
    return{
        x: x, 
        y: y, 
        white: white,
        draw: drawRook,
        name: "rook",

        copy: function(){
            return newRook(this.x,this.y,this.white);
        },

        getLegalMoves: function(board){
            return [];
        } 
    };
}

function newKnight(x,y,white)
{
    return{
        x: x, 
        y: y, 
        white: white,
        draw: drawKnight,
        name: "Knight",

        copy: function(){
            return newKnight(this.x,this.y,this.white);
        },

        getLegalMoves: function(board){
            return [];
        } 
    };
}

function newBishop(x,y,white)
{
    return{
        x: x, 
        y: y, 
        white: white,
        draw: drawBishop,
        name: "Bishop",

        copy: function(){
            return newBishop(this.x,this.y,this.white);
        },

        getLegalMoves: function(board){
            return [];
        } 
    };
}

function newQueen(x,y,white)
{
    return{
        x: x, 
        y: y, 
        white: white,
        draw: drawQueen,
        name: "Queen",

        copy: function(){
            return newQueen(this.x,this.y,this.white);
        },

        getLegalMoves: function(board){
            return [];
        } 
    };
}

function newKing(x,y,white)
{
    return{
        x: x, 
        y: y, 
        white: white,
        draw: drawKing,
        name: "King",

        copy: function(){
            return newKing(this.x,this.y,this.white);
        },

        getLegalMoves: function(board){
            return [];
        } 
    };
}

