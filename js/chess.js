"use strict"

var board;
var whitesTurn;
var selectedPiece;

function createNewBoard() 
{
    var board = { blackPieces: [], whitePieces: [], getPieceOnSquare: getPieceOnSquare };
    for (var p = 0; p < 8; p++) {
        board.blackPieces.push({ x: p, y: 1, white: false, draw: drawPawn, name: "pawn", getLegalMoves: getLegalMovesPawn });
        board.whitePieces.push({ x: p, y: 6, white: true, draw: drawPawn, name: "pawn", getLegalMoves: getLegalMovesPawn });
    }
    board.blackPieces.push({ x: 0, y: 0, white: false, draw: drawRook, name: "rook", getLegalMoves: getLegalMovesRook });
    board.blackPieces.push({ x: 7, y: 0, white: false, draw: drawRook, name: "rook", getLegalMoves: getLegalMovesRook });
    board.blackPieces.push({ x: 1, y: 0, white: false, draw: drawKnight, name: "knight", getLegalMoves: getLegalMovesKnight });
    board.blackPieces.push({ x: 6, y: 0, white: false, draw: drawKnight, name: "knight", getLegalMoves: getLegalMovesKnight });
    board.blackPieces.push({ x: 2, y: 0, white: false, draw: drawBishop, name: "bishop", getLegalMoves: getLegalMovesBishop });
    board.blackPieces.push({ x: 5, y: 0, white: false, draw: drawBishop, name: "bishop", getLegalMoves: getLegalMovesBishop });
    board.blackPieces.push({ x: 3, y: 0, white: false, draw: drawQueen, name: "queen", getLegalMoves: getLegalMovesQueen });
    board.blackPieces.push({ x: 4, y: 0, white: false, draw: drawKing, name: "king", getLegalMoves: getLegalMovesKing });

    board.whitePieces.push({ x: 0, y: 7, white: true, draw: drawRook, name: "rook", getLegalMoves: getLegalMovesRook });
    board.whitePieces.push({ x: 7, y: 7, white: true, draw: drawRook, name: "rook", getLegalMoves: getLegalMovesRook });
    board.whitePieces.push({ x: 1, y: 7, white: true, draw: drawKnight, name: "knight", getLegalMoves: getLegalMovesKnight });
    board.whitePieces.push({ x: 6, y: 7, white: true, draw: drawKnight, name: "knight", getLegalMoves: getLegalMovesKnight });
    board.whitePieces.push({ x: 2, y: 7, white: true, draw: drawBishop, name: "bishop", getLegalMoves: getLegalMovesBishop });
    board.whitePieces.push({ x: 5, y: 7, white: true, draw: drawBishop, name: "bishop", getLegalMoves: getLegalMovesBishop });
    board.whitePieces.push({ x: 3, y: 7, white: true, draw: drawQueen, name: "queen", getLegalMoves: getLegalMovesQueen });
    board.whitePieces.push({ x: 4, y: 7, white: true, draw: drawKing, name: "king", getLegalMoves: getLegalMovesKing });
    whitesTurn=true;
    return board;
}

function main() {
    board = createNewBoard();
    drawBoard(board);

    var canvas = document.getElementById("boardCanvas");
    canvas.addEventListener("click", onBoardClicked);

}

function onBoardClicked(eventInfo) {
    var c = document.getElementById("boardCanvas");
    var width = c.clientWidth / 8;
    var x = Math.floor(eventInfo.offsetX / width);
    var y = Math.floor(eventInfo.offsetY / width);
    onSquareClicked(x, y);
}

function onSquareClicked(x, y) {
    selectedSquare.x = -1;
    selectedSquare.y = -1;
    highlightedSquares = [];

    if ( selectedPiece == undefined)
    {
        selectedPiece = board.getPieceOnSquare(x, y);
        if ( selectedPiece != undefined && selectedPiece.white == whitesTurn ){
            selectedSquare.x = x;
            selectedSquare.y = y;
            console.log("clicked on " + x + ", " + y + ": " +
                (selectedPiece != undefined ? ((selectedPiece.white ? "white " : "black ") + selectedPiece.name) : "empty"));
        
            if (selectedPiece != undefined) 
            {
                highlightedSquares = selectedPiece.getLegalMoves(board);
            }

        }
    }
    else{
        selectedPiece=null;
    }
    drawBoard(board);
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

main();