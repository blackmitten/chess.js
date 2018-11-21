using System;
using System.Collections.Generic;
using System.Text;

namespace ChessDotNetBackend
{
    class PieceCode : IPieceVisitor
    {
        public string Code { get; private set; }

        public void Visit( Pawn pawn, object data ) => Code = pawn.White ? "P" : "p";
        public void Visit( Rook rook, object data ) => Code = rook.White ? "R" : "r";
        public void Visit( Knight knight, object data ) => Code = knight.White ? "N" : "n";
        public void Visit( Bishop bishop, object data ) => Code = bishop.White ? "B" : "b";
        public void Visit( Queen queen, object data ) => Code = queen.White ? "Q" : "q";
        public void Visit( King king, object data ) => Code = king.White ? "K" : "k";
    }
}
