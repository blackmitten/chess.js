using System;
using System.Collections.Generic;
using System.Text;

namespace ChessDotNetBackend
{
    public class TranspositionTable
    {
        Dictionary<long, double> m_leafScores = new Dictionary<long, double>();

        internal bool ContainsLeafScore(ZobristHash hash) => m_leafScores.ContainsKey(hash.Hash);
        internal double LeafScore(ZobristHash hash) => m_leafScores[hash.Hash];
        internal void UpdateLeafScore(ZobristHash hash, double whitesScore) => m_leafScores[hash.Hash] = whitesScore;
    }
}
