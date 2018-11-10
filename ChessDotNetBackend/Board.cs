using System;
using System.Collections.Generic;
using System.Text;

namespace ChessDotNetBackend
{
    public class Board
    {
        IList<IPiece> m_pieces = new List<IPiece>();

        public Board(Board board)
        {
            this.WhitesTurn = board.WhitesTurn;
            foreach (var piece in board.Pieces)
            {
                this.m_pieces.Add(piece.Copy());
            }
        }

        public Board()
        {
        }

        public IList<IPiece> Pieces => m_pieces;

        public bool WhitesTurn { get; set; }

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
            b.WhitesTurn = true;
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

        public Board MovePiece(IPiece piece, Square destinationSquare)
        {
            Board board = new Board(this);
            var capturedPiece = GetPieceOnSquare(destinationSquare);
            if(capturedPiece!=null)
            {
                if (capturedPiece.White != piece.White)
                {
                    board.RemovePiece(capturedPiece);
                }
                else
                {
                    throw new InvalidOperationException("tried to move to a square occupied by a piece on our own side");
                }
            }
            var pieceCopy = board.GetPieceOnSquare(piece.CurrentPosition);
            pieceCopy.CurrentPosition = destinationSquare;
            board.WhitesTurn = !WhitesTurn;
            return board;
        }

        private void RemovePiece(IPiece capturedPiece)
        {
            for(int i=0; i<m_pieces.Count;i++)
            {
                if(m_pieces[i].CurrentPosition==capturedPiece.CurrentPosition)
                {
                    m_pieces.RemoveAt(i);
                    break;
                }
            }
        }

        public override bool Equals(object obj)
        {
            if (obj == null || GetType() != obj.GetType())
            {
                return false;
            }
            Board b = (Board)obj;
            if (WhitesTurn != b.WhitesTurn)
            {
                return false;
            }
            if (Pieces.Count != b.Pieces.Count)
            {
                return false;
            }
            for (int x = 0; x < 8; x++)
            {
                for (int y = 0; y < 8; y++)
                {
                    Square s = new Square(x, y);
                    IPiece piece1 = GetPieceOnSquare(s);
                    IPiece piece2 = b.GetPieceOnSquare(s);
                    if (piece1 == null && piece2 != null)
                    {
                        return false;
                    }
                    if (piece1 != null && piece2 == null)
                    {
                        return false;
                    }
                    if (piece1 != null && piece2 != null)
                    {
                        if (!piece1.Equals(piece2))
                        {
                            return false;
                        }
                    }
                }
            }
            return true;
        }

    }
}
