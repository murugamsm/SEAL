﻿using Microsoft.VisualStudio.TestTools.UnitTesting;
using Microsoft.Research.SEAL;
using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace SEALNetTest
{
    [TestClass]
    public class SmallModulusTests
    {
        [TestMethod]
        public void EmptyConstructorTest()
        {
            SmallModulus sm = new SmallModulus();

            Assert.IsNotNull(sm);
            Assert.IsTrue(sm.IsZero);
            Assert.AreEqual(0ul, sm.Value);
            Assert.AreEqual(0, sm.BitCount);
            Assert.AreEqual(1, sm.UInt64Count);
        }

        [TestMethod]
        public void ValueConstructorTest()
        {
            SmallModulus sm = new SmallModulus(5);

            Assert.IsNotNull(sm);
            Assert.IsFalse(sm.IsZero);
            Assert.AreEqual(5ul, sm.Value);
            Assert.AreEqual(3, sm.BitCount);

            // Value is exactly 62 bits
            SmallModulus sm2 = new SmallModulus(0x3FFFFFFFFFFFFFFFul);

            Assert.IsNotNull(sm2);
            Assert.IsFalse(sm2.IsZero);
            Assert.AreEqual(0x3FFFFFFFFFFFFFFFul, sm2.Value);
            Assert.AreEqual(62, sm2.BitCount);
            Assert.AreEqual(1, sm2.UInt64Count);
        }

        [TestMethod]
        public void CopyConstructorTest()
        {
            SmallModulus sm = new SmallModulus(10);
            SmallModulus copy = new SmallModulus(sm);

            Assert.IsNotNull(copy);
            Assert.IsFalse(copy.IsZero);
            Assert.AreEqual(10ul, copy.Value);
        }

        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void ConstructorFail1Test()
        {
            // Should fail if value is 1
            SmallModulus sm = new SmallModulus(1);
        }

        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void ConstructorFail2Test()
        {
            // Should fail if value is larger than 62 bits
            SmallModulus sm = new SmallModulus(0x7FFFFFFFFFFFFFFFul);
        }

        [TestMethod]
        public void SetTest()
        {
            SmallModulus sm1 = new SmallModulus(456);
            SmallModulus sm2 = new SmallModulus();

            Assert.IsFalse(sm1.IsZero);
            Assert.AreEqual(456ul, sm1.Value);
            Assert.IsTrue(sm2.IsZero);
            Assert.AreEqual(0ul, sm2.Value);

            sm2.Set(sm1);

            Assert.IsFalse(sm2.IsZero);
            Assert.AreEqual(456ul, sm2.Value);

            sm2.Set(value: 123);

            Assert.IsFalse(sm2.IsZero);
            Assert.AreEqual(123ul, sm2.Value);
        }

        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void SetFail1Test()
        {
            // Should faile if set to 1
            SmallModulus sm = new SmallModulus();
            sm.Set(1);
        }

        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void SetFail2Test()
        {
            // Should fail if set to bigger than 62 bits
            SmallModulus sm = new SmallModulus();
            sm.Set(0x7FFFFFFFFFFFFFFFul);
        }
       
        [TestMethod]
        public void ConstRatioTest()
        {
            SmallModulus sm = new SmallModulus();
            sm.Set(0x1234567890ABCDEFul);

            Tuple<ulong, ulong, ulong> ratio = sm.ConstRatio;

            Assert.IsNotNull(ratio);
            Assert.AreNotEqual(0ul, ratio.Item1);
            Assert.AreNotEqual(0ul, ratio.Item2);
            Assert.AreNotEqual(0ul, ratio.Item3);
        }

        [TestMethod]
        public void EqualsTest()
        {
            SmallModulus sm1 = new SmallModulus(0x12345ul);
            SmallModulus sm2 = new SmallModulus(0x12345ul);

            Assert.AreEqual(sm1, sm2);
            Assert.IsTrue(sm1.Equals(0x12345ul));
            Assert.IsFalse(sm1.Equals(0x1234ul));
        }

        [TestMethod]
        public void SaveLoadTest()
        {
            SmallModulus sm1 = new SmallModulus(0x12345ul);
            SmallModulus sm2 = new SmallModulus();

            Assert.AreNotSame(sm1, sm2);
            Assert.AreNotEqual(sm1, sm2);

            using (MemoryStream stream = new MemoryStream())
            {
                sm1.Save(stream);

                stream.Seek(offset: 0, loc: SeekOrigin.Begin);

                sm2.Load(stream);
            }

            Assert.AreNotSame(sm1, sm2);
            Assert.AreEqual(sm1, sm2);
            Assert.AreEqual(sm1.BitCount, sm2.BitCount);
            Assert.AreEqual(sm1.UInt64Count, sm2.UInt64Count);
            Assert.AreEqual(sm1.ConstRatio.Item1, sm2.ConstRatio.Item1);
            Assert.AreEqual(sm1.ConstRatio.Item2, sm2.ConstRatio.Item2);
            Assert.AreEqual(sm1.ConstRatio.Item3, sm2.ConstRatio.Item3);
        }
    }
}
