import {highlightedSquares} from "./chess.js";
import {selectedSquare} from "./chess.js";

"use strict";

export {drawBoard};
export {drawBishop};
export {drawQueen};
export {drawRook};
export {drawKing};
export {drawKnight};
export {drawPawn};



function drawBoard(board) {
    var c = document.getElementById("boardCanvas");
    var ctx = c.getContext("2d");
    ctx.clearRect(0, 0, c.clientWidth, c.clientHeight);
    var width = c.clientWidth;

    var dark = false;
    ctx.lineWidth = 1;

    for (var x = 0; x < 8; x++) {
        dark = !dark;
        for (var y = 0; y < 8; y++) {
            dark = !dark;
            if (dark) {
                ctx.fillStyle = "#777";
            }
            else {
                ctx.fillStyle = "#aaa";
            }
            ctx.fillRect(x * width / 8, y * width / 8, width / 8, width / 8);
        }
    }
    for (var i = 0; i < board.blackPieces.length; i++) {
        board.blackPieces[i].draw(ctx, width / 8);
    }
    for (i = 0; i < board.whitePieces.length; i++) {
        board.whitePieces[i].draw(ctx, width / 8);
    }

    if (selectedSquare.x >= 0 && selectedSquare.y >= 0) {
        ctx.beginPath();
        ctx.strokeStyle = "red";
        ctx.lineWidth = 3;
        ctx.rect(selectedSquare.x * width / 8, selectedSquare.y * width / 8, width / 8, width / 8);
        ctx.stroke();
    }
    for (i = 0; i < highlightedSquares.length; i++) {
        var square = highlightedSquares[i];
        ctx.beginPath();
        ctx.strokeStyle = "white";
        ctx.lineWidth = 2;
        ctx.rect(square.x * width / 8, square.y * width / 8, width / 8, width / 8);
        ctx.stroke();
    }

}

function drawBishop(ctx, width) {
    var pos = drawPiecePreamble(ctx, this, width);
    ctx.beginPath();
    ctx.moveTo(pos.x - width / 5, pos.y + width / 4);
    ctx.lineTo(pos.x + width / 5, pos.y + width / 4);
    ctx.lineTo(pos.x, pos.y - width / 4);
    ctx.closePath();
    ctx.fill();
}

function drawQueen(ctx, width) {
    var pos = drawPiecePreamble(ctx, this, width);
    ctx.beginPath();
    ctx.moveTo(pos.x - width / 3.5, pos.y + width / 7);
    ctx.lineTo(pos.x + width / 3.5, pos.y + width / 7);
    ctx.lineTo(pos.x, pos.y - width / 3);
    ctx.closePath();
    ctx.fill();
    ctx.beginPath();
    ctx.moveTo(pos.x - width / 3.5, pos.y - width / 7);
    ctx.lineTo(pos.x + width / 3.5, pos.y - width / 7);
    ctx.lineTo(pos.x, pos.y + width / 3);
    ctx.closePath();
    ctx.fill();
}

function drawRook(ctx, width) {
    var pos = drawPiecePreamble(ctx, this, width);
    ctx.fillRect(pos.x - width / 7, pos.y - width / 4, 2 * width / 7, 2 * width / 4);
    ctx.fillRect(pos.x - width / 5, pos.y - width / 4, 2 * width / 5, width / 8);
    ctx.fillRect(pos.x - width / 5, pos.y + width / 4 - width / 8, 2 * width / 5, width / 8);
}

function drawKing(ctx, width) {
    var pos = drawPiecePreamble(ctx, this, width);
    ctx.fillRect(pos.x - width / 7, pos.y - width / 3.5, 2 * width / 7, 2 * width / 3.5);
    ctx.fillRect(pos.x - width / 3.5, pos.y - width / 7, 2 * width / 3.5, 2 * width / 7);
}

function drawKnight(ctx, width) {
    var pos = drawPiecePreamble(ctx, this, width);
    ctx.fillRect(pos.x - width / 5, pos.y - width / 4, 2 * width / 7, 2 * width / 4);
    ctx.fillRect(pos.x - width / 5, pos.y - width / 4, 2 * width / 5, width / 8);
}

function drawPawn(ctx, width) {
    var pos = drawPiecePreamble(ctx, this, width);
    ctx.beginPath();
    ctx.arc(pos.x, pos.y, width / 5, 0, 2 * Math.PI, false);
    ctx.fill();
}

function drawPiecePreamble(ctx, piece, width) {
    ctx.fillStyle = piece.white ? "#fff" : "#000";
    var x = piece.square.x * width + width / 2;
    var y = piece.square.y * width + width / 2;
    return { x:x, y:y };
}
