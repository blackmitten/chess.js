using System;
using System.Collections.Generic;
using System.Text;

namespace ChessDotNetBackend
{
    public struct Square
    {
        public int x;
        public int y;

        public bool InBounds => x >= 0 && x <= 7 && y >= 0 && y <= 7;

        public Square(int x, int y)
        {
            this.x = x;
            this.y = y;
        }

        public override bool Equals(Object obj)
        {
            return obj is Square && this == (Square)obj;
        }

        public override int GetHashCode()
        {
            return x.GetHashCode() ^ y.GetHashCode();
        }

        public static bool operator ==(Square s1, Square s2)
        {
            return s1.x == s2.x && s1.y == s2.y;
        }

        public static bool operator !=(Square s1, Square s2)
        {
            return s1.x != s2.x || s1.y != s2.y;
        }

        public Square Offset(int dx, int dy)
        {
            return new Square(x + dx, y + dy);
        }

        public override string ToString()
        {
            return x + ", " + y;
        }
    }
}
