using ChessDotNetBackend;
using Microsoft.VisualStudio.TestTools.UnitTesting;

#pragma warning disable CS1718

namespace ChessTests
{
    [TestClass]
    public class UnitTest1
    {
        [TestMethod]
        public void TestSquareEquality()
        {
            Square s1 = new Square(0, 0);
            Square s2 = new Square(0, 1);
            Square s3 = new Square(0, 1);
            Square s4 = new Square(1, 1);
            Square s5 = new Square(1, 1);

            Assert.AreEqual(s1, s1);
            Assert.AreNotEqual(s1, s2);
            Assert.AreEqual(s2, s3);
            Assert.AreNotEqual(s3, s4);
            Assert.AreEqual(s4, s5);
        }

        [TestMethod]
        public void TestSquareOffset()
        {
            Square s6 = new Square(4, 4);
            Square s7 = new Square(2, 6);
            Square s8 = s6.Offset(-2, 2);
            Assert.AreNotEqual(s6, s7);
            Assert.AreEqual(s7, s8);
        }

        [TestMethod]
        public void TestSquareCopy()
        {
            Square s1 = new Square(4, 4);
            Square s2 = s1;
            Assert.AreEqual(s1, s2);
            Assert.AreNotSame(s1, s2);
        }

    }
}
