using System;
using System.Collections.Generic;
using System.Text;

namespace ChessDotNetBackend
{
    public interface IPieceVisitor
    {
        void Visit(Pawn pawn, object data);
        void Visit(Rook rook, object data);
        void Visit(Knight knight, object data);
        void Visit(Bishop bishop, object data);
        void Visit(Queen queen, object data);
        void Visit(King king, object data);
    }

    public interface IPiece
    {
        Square Square { get; }
        bool White { get; }
        string Name { get; }

        void Accept(IPieceVisitor visitor, object data);
    }

    public class Pawn : IPiece
    {
        public Square Square { get; set; }
        public bool White { get; }
        public string Name { get; }

        public Pawn(Square square, bool white)
        {
            Square = square;
            White = white;
            Name = White ? "White Pawn" : "Black Pawn";
        }

        public void Accept(IPieceVisitor visitor, object data)
        {
            visitor.Visit(this, data);
        }
    }

    public class Rook : IPiece
    {
        public Square Square { get; set; }
        public bool White { get; }
        public string Name { get; }

        public Rook(Square square, bool white)
        {
            Square = square;
            White = white;
            Name = White ? "White Rook" : "Black Rook";
        }

        public void Accept(IPieceVisitor visitor, object data)
        {
            visitor.Visit(this, data);
        }
    }
    public class Knight : IPiece
    {
        public Square Square { get; set; }
        public bool White { get; }
        public string Name { get; }

        public Knight(Square square, bool white)
        {
            Square = square;
            White = white;
            Name = White ? "White Knight" : "Black Knight";
        }

        public void Accept(IPieceVisitor visitor, object data)
        {
            visitor.Visit(this, data);
        }
    }

    public class Bishop : IPiece
    {
        public Square Square { get; set; }
        public bool White { get; }
        public string Name { get; }

        public Bishop(Square square, bool white)
        {
            Square = square;
            White = white;
            Name = White ? "White Bishop" : "Black Bishop";
        }

        public void Accept(IPieceVisitor visitor, object data)
        {
            visitor.Visit(this, data);
        }
    }

    public class Queen : IPiece
    {
        public Square Square { get; set; }
        public bool White { get; }
        public string Name { get; }

        public Queen(Square square, bool white)
        {
            Square = square;
            White = white;
            Name = White ? "White Queen" : "Black Queen";
        }

        public void Accept(IPieceVisitor visitor, object data)
        {
            visitor.Visit(this, data);
        }
    }

    public class King : IPiece
    {
        public Square Square { get; set; }
        public bool White { get; }
        public string Name { get; }

        public King(Square square, bool white)
        {
            Square = square;
            White = white;
            Name = White ? "White King" : "Black King";
        }

        public void Accept(IPieceVisitor visitor, object data)
        {
            visitor.Visit(this, data);
        }
    }

}
