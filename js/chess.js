"use strict"

var board;
var selectedPiece;

function createNewBoard() {
    var board = newBoard();
    for (var p = 0; p < 8; p++) {
        board.blackPieces.push(newPawn(p, 1, false));
        board.whitePieces.push(newPawn(p, 6, true));
    }
    board.blackPieces.push(newRook(0, 0, false));
    board.blackPieces.push(newRook(7, 0, false));
    board.blackPieces.push(newKnight(1, 0, false));
    board.blackPieces.push(newKnight(6, 0, false));
    board.blackPieces.push(newBishop(2, 0, false));
    board.blackPieces.push(newBishop(5, 0, false));
    board.blackPieces.push(newQueen(3, 0, false));
    board.blackPieces.push(newKing(4, 0, false));

    board.whitePieces.push(newRook(0, 7, true));
    board.whitePieces.push(newRook(7, 7, true));
    board.whitePieces.push(newKnight(1, 7, true));
    board.whitePieces.push(newKnight(6, 7, true));
    board.whitePieces.push(newBishop(2, 7, true));
    board.whitePieces.push(newBishop(5, 7, true));
    board.whitePieces.push(newQueen(3, 7, true));
    board.whitePieces.push(newKing(4, 7, true));

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
    var clickedSquare = { x: x, y: y };
    var clickedPiece = board.getPieceOnSquare(x, y);

    if (selectedPiece == undefined) {
        if (clickedPiece != undefined) {
            if (clickedPiece.white == board.whitesTurn) {
                selectedPiece = clickedPiece;
                selectedSquare.x = x;
                selectedSquare.y = y;
                console.log("clicked on " + x + ", " + y + ": " +
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
    drawBoard(board);
}

function checkArrayForSquare(square, squares) {
    for (var i = 0; i < squares.length; i++) {
        if (square.x == squares[i].x && square.y == squares[i].y) {
            return true;
        }
    }
    return false;
}

main();