using System;
using System.Collections.Generic;
using System.Text;

namespace ChessDotNetBackend
{
    public class Board
    {
        IList<IPiece> m_pieces = new List<IPiece>();
        bool m_whitesTurn = true;

        public IList<IPiece> Pieces => m_pieces;

        public static Board InitNewGame()
        {
            Board b = new Board();
            for (int i = 0; i < 8; i++)
            {
                b.m_pieces.Add(new Pawn(new Square(i, 1), false));
                b.m_pieces.Add(new Pawn(new Square(i, 6), true));
            }
            b.m_pieces.Add(new Rook(new Square(0, 0), false));
            b.m_pieces.Add(new Rook(new Square(7, 0), false));
            b.m_pieces.Add(new Knight(new Square(1, 0), false));
            b.m_pieces.Add(new Knight(new Square(6, 0), false));
            b.m_pieces.Add(new Bishop(new Square(2, 0), false));
            b.m_pieces.Add(new Bishop(new Square(5, 0), false));
            b.m_pieces.Add(new Queen(new Square(3, 0), false));
            b.m_pieces.Add(new King(new Square(4, 0), false));

            b.m_pieces.Add(new Rook(new Square(0, 7), true));
            b.m_pieces.Add(new Rook(new Square(7, 7), true));
            b.m_pieces.Add(new Knight(new Square(1, 7), true));
            b.m_pieces.Add(new Knight(new Square(6, 7), true));
            b.m_pieces.Add(new Bishop(new Square(2, 7), true));
            b.m_pieces.Add(new Bishop(new Square(5, 7), true));
            b.m_pieces.Add(new Queen(new Square(3, 7), true));
            b.m_pieces.Add(new King(new Square(4, 7), true));
            return b;
        }

        public IPiece GetPieceOnSquare(Square square)
        {
            foreach (var piece in m_pieces)
            {
                if (square == piece.CurrentPosition)
                {
                    return piece;
                }
            }
            return null;
        }

        /// <summary>
        /// Walk the piece up to the given square and see if anyone gets in the way
        /// </summary>
        /// <param name="piece"></param>
        /// <param name="square"></param>
        /// <returns></returns>
        public bool IsNothingInTheWay(IPiece piece, Square square)
        {
            int dx = piece.CurrentPosition.x - square.x;
            int dy = piece.CurrentPosition.y - square.y;
            int xinc = (dx == 0) ? 0 : ((dx < 0) ? 1 : -1);  // ie. either no horizontal move or left / right
            int yinc = (dy == 0) ? 0 : ((dy < 0) ? 1 : -1);  // ie. either no vertical move or up / down

            if (xinc == 0 && yinc == 0)
            {
                throw new InvalidOperationException();  // if this happens, we're stuffed - it shouldn't ever happen
            }

            Square s = piece.CurrentPosition;
            for (; ; )
            {
                s = s.Offset(xinc, yinc);
                if (square == s)
                {
                    return true;
                }
                if (GetPieceOnSquare(s) != null)
                {
                    return false;
                }
            }
        }


    }
}
