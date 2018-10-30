"use strict"

var board;

function createNewBoard() {
    var board = { blackPieces: [], whitePieces: [] };
    for (var p = 0; p < 8; p++) {
        board.blackPieces.push({ x: p, y: 1, white: false, draw: drawPawn });
        board.whitePieces.push({ x: p, y: 6, white: true, draw: drawPawn });
    }
    board.blackPieces.push({ x: 0, y: 0, white: false, draw: drawRook });
    board.blackPieces.push({ x: 7, y: 0, white: false, draw: drawRook });
    board.blackPieces.push({ x: 1, y: 0, white: false, draw: drawKnight });
    board.blackPieces.push({ x: 6, y: 0, white: false, draw: drawKnight });
    board.blackPieces.push({ x: 2, y: 0, white: false, draw: drawBishop });
    board.blackPieces.push({ x: 5, y: 0, white: false, draw: drawBishop });
    board.blackPieces.push({ x: 3, y: 0, white: false, draw: drawQueen });
    board.blackPieces.push({ x: 4, y: 0, white: false, draw: drawKing });

    board.whitePieces.push({ x: 0, y: 7, white: true, draw: drawRook });
    board.whitePieces.push({ x: 7, y: 7, white: true, draw: drawRook });
    board.whitePieces.push({ x: 1, y: 7, white: true, draw: drawKnight });
    board.whitePieces.push({ x: 6, y: 7, white: true, draw: drawKnight });
    board.whitePieces.push({ x: 2, y: 7, white: true, draw: drawBishop });
    board.whitePieces.push({ x: 5, y: 7, white: true, draw: drawBishop });
    board.whitePieces.push({ x: 3, y: 7, white: true, draw: drawQueen });
    board.whitePieces.push({ x: 4, y: 7, white: true, draw: drawKing });
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
    console.log("clicked on " + x + ", " + y);
    if (selectedSquare.x == x && selectedSquare.y == y) {
        selectedSquare.x = -1;
        selectedSquare.y = -1;
    }
    else {
        selectedSquare.x = x;
        selectedSquare.y = y;
    }
    drawBoard(board);
}

main();