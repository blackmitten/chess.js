import {Board} from "./board.js";
import {Square} from "./board.js";
import * as Drawing from "./drawing.js";

"use strict";


var board;
var selectedPiece;
var selectedSquare = new Square( -1, -1 );
var highlightedSquares = [];

export {selectedSquare};
export {highlightedSquares};

function main() {
    board = new Board();
    board.initNewGame();
    Drawing.drawBoard(board);

    var canvas = document.getElementById("boardCanvas");
    canvas.addEventListener("click", onBoardClicked);

}

function onBoardClicked(eventInfo) {
    var c = document.getElementById("boardCanvas");
    var width = c.clientWidth / 8;
    var x = Math.floor(eventInfo.offsetX / width);
    var y = Math.floor(eventInfo.offsetY / width);
    onSquareClicked(new Square( x, y));
}

function onSquareClicked(clickedSquare) {
    selectedSquare= new Square( -1, -1 );
    highlightedSquares = [];
    var clickedPiece = board.getPieceOnSquare(clickedSquare);

    if (selectedPiece == undefined) {
        if (clickedPiece != undefined) {
            if (clickedPiece.white == board.whitesTurn) {
                selectedPiece = clickedPiece;
                selectedSquare = clickedSquare;
                console.log("clicked on " + clickedSquare.x + ", " + clickedSquare.y + ": " +
                    (selectedPiece != undefined ? ((selectedPiece.white ? "white " : "black ") + selectedPiece.name) : "empty"));

                if (selectedPiece != undefined) {
                    highlightedSquares = selectedPiece.getLegalMoves(board);
                }

            }
        }

    }
    else {
        var legalMoves = selectedPiece.getLegalMoves(board);
        if (checkArrayForSquare(clickedSquare, legalMoves)) {
            board = board.movePiece(selectedPiece, clickedSquare);
            console.log("legal");
        }
        else {
            console.log("not legal");
        }
        selectedPiece = null;
    }
    Drawing.drawBoard(board);
}

function checkArrayForSquare(square, squares) {
    for (var i = 0; i < squares.length; i++) {
        if (square.equals(squares[i])) {
            return true;
        }
    }
    return false;
}

main();