using System;
using System.Collections.Generic;
using System.Text;

namespace ChessDotNetBackend
{
    class ZobristTable
    {
        static ZobristTable m_instance;
        const int m_numberOfPieceTypes = 12;
        public long[,,] Table { get; } = new long[8, 8, m_numberOfPieceTypes];

        private ZobristTable()
        {
            Random r = new Random();
            for (var x = 0; x < 8; x++)
            {
                for (var y = 0; y < 8; y++)
                {
                    for (var p = 0; p < m_numberOfPieceTypes; p++)
                    {
                        long l1 = r.Next();
                        long l2 = r.Next();
                        l2 <<= 32;
                        long l = l1 | l2;
                        Table[x, y, p] = l;
                    }
                }
            }
        }

        public static ZobristTable Instance
        {
            get
            {
                if (m_instance == null)
                {
                    m_instance = new ZobristTable();
                }
                return m_instance;
            }
        }
    }
}
