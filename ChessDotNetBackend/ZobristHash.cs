using System;
using System.Collections.Generic;
using System.Text;

namespace ChessDotNetBackend
{
    public struct ZobristHash
    {
        public long Hash;

        public ZobristHash(Board board)
        {
            Hash = 0;
            board.DebugOutput();
            foreach (var piece in board.Pieces)
            {
                Square s = piece.CurrentPosition;
                Hash ^= ZobristTable.Instance.Table[s.x, s.y, (int)piece.PieceType];
            }
//            Console.WriteLine( Hash );
        }

        public override string ToString() => Hash.ToString();
    }
}
