"use strict"

var board;
var selectedPiece;

function createNewBoard() {
    var board = newBoard();
    for (var p = 0; p < 8; p++) {
        board.blackPieces.push(new Pawn(p, 1, false));
        board.whitePieces.push(new Pawn(p, 6, true));
    }
    board.blackPieces.push(new Rook(0, 0, false));
    board.blackPieces.push(new Rook(7, 0, false));
    board.blackPieces.push(new Knight(1, 0, false));
    board.blackPieces.push(new Knight(6, 0, false));
    board.blackPieces.push(new Bishop(2, 0, false));
    board.blackPieces.push(new Bishop(5, 0, false));
    board.blackPieces.push(new Queen(3, 0, false));
    board.blackPieces.push(new King(4, 0, false));

    board.whitePieces.push(new Rook(0, 7, true));
    board.whitePieces.push(new Rook(7, 7, true));
    board.whitePieces.push(new Knight(1, 7, true));
    board.whitePieces.push(new Knight(6, 7, true));
    board.whitePieces.push(new Bishop(2, 7, true));
    board.whitePieces.push(new Bishop(5, 7, true));
    board.whitePieces.push(new Queen(3, 7, true));
    board.whitePieces.push(new King(4, 7, true));

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
    onSquareClicked({ x: x, y: y });
}

function onSquareClicked(clickedSquare) {
    selectedSquare.x = -1;
    selectedSquare.y = -1;
    highlightedSquares = [];
    var clickedPiece = board.getPieceOnSquare(clickedSquare);

    if (selectedPiece == undefined) {
        if (clickedPiece != undefined) {
            if (clickedPiece.white == board.whitesTurn) {
                selectedPiece = clickedPiece;
                selectedSquare.x = clickedSquare.x;
                selectedSquare.y = clickedSquare.y;
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