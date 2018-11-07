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

        public void InitNewGame()
        {
            for (int i = 0; i < 8; i++)
            {
                m_pieces.Add(new Pawn(new Square(i, 1), false));
                m_pieces.Add(new Pawn(new Square(i, 6), true));
            }
            m_pieces.Add(new Rook(new Square(0, 0), false));
            m_pieces.Add(new Rook(new Square(7, 0), false));
            m_pieces.Add(new Knight(new Square(1, 0), false));
            m_pieces.Add(new Knight(new Square(6, 0), false));
            m_pieces.Add(new Bishop(new Square(2, 0), false));
            m_pieces.Add(new Bishop(new Square(5, 0), false));
            m_pieces.Add(new Queen(new Square(3, 0), false));
            m_pieces.Add(new King(new Square(4, 0), false));

            m_pieces.Add(new Rook(new Square(0, 7), true));
            m_pieces.Add(new Rook(new Square(7, 7), true));
            m_pieces.Add(new Knight(new Square(1, 7), true));
            m_pieces.Add(new Knight(new Square(6, 7), true));
            m_pieces.Add(new Bishop(new Square(2, 7), true));
            m_pieces.Add(new Bishop(new Square(5, 7), true));
            m_pieces.Add(new Queen(new Square(3, 7), true));
            m_pieces.Add(new King(new Square(4, 7), true));
        }
    }
}
