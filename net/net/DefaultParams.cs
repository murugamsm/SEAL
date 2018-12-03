﻿using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Text;
using Microsoft.Research.SEAL.Tools;

namespace Microsoft.Research.SEAL
{
    public static class DefaultParams
    {
        /// <summary>
        /// Returns the default coefficients modulus for a given polynomial modulus 
        /// degree.
        /// </summary>
        /// 
        /// <remarks>
        /// Returns the default coefficients modulus for a given polynomial modulus degree.
        /// The polynomial modulus and the coefficient modulus obtained in this way should
        /// provide approdimately 128 bits of security against the best known attacks,
        /// assuming the standard deviation of the noise distribution is left to its default
        /// value.
        /// </remarks>
        /// <param name="polyModulusDegree">The degree of the polynomial modulus</param>
        /// <exception cref="System.ArgumentOutOfRangeException">if poly_modulus_degree is
        /// not 1024, 2048, 4096, 8192, 16384, or 32768</exception>
        public static IEnumerable<SmallModulus> CoeffModulus128(int polyModulusDegree)
        {
            List<SmallModulus> result = null;

            try
            {
                int length = 0;
                NativeMethods.DefParams_CoeffModulus128(polyModulusDegree, ref length, null);

                IntPtr[] coeff_array = new IntPtr[length];
                NativeMethods.DefParams_CoeffModulus128(polyModulusDegree, ref length, coeff_array);

                result = new List<SmallModulus>(length);
                foreach (IntPtr sm in coeff_array)
                {
                    result.Add(new SmallModulus(sm));
                }
            }
            catch(COMException ex)
            {
                if ((uint)ex.HResult == NativeMethods.Errors.HRInvalidIndex)
                    throw new ArgumentOutOfRangeException(nameof(polyModulusDegree), ex);
                throw;
            }

            return result;
        }

        /// <summary>
        /// Returns the default coefficients modulus for a given polynomial modulus
        /// degree.
        /// </summary>
        /// 
        /// <remarks>
        /// Returns the default coefficients modulus for a given polynomial modulus degree.
        /// The polynomial modulus and the coefficient modulus obtained in this way should
        /// provide approdimately 192 bits of security against the best known attacks,
        /// assuming the standard deviation of the noise distribution is left to its default
        /// value.
        /// </remarks>
        /// <param name="polyModulusDegree">The degree of the polynomial modulus</param>
        /// <exception cref="System.ArgumentOutOfRangeException">if poly_modulus_degree is
        /// not 1024, 2048, 4096, 8192, 16384, or 32768</exception>
        public static IEnumerable<SmallModulus> CoeffModulus192(int polyModulusDegree)
        {
            List<SmallModulus> result = null;

            try
            {
                int length = 0;
                NativeMethods.DefParams_CoeffModulus192(polyModulusDegree, ref length, null);

                IntPtr[] coeff_array = new IntPtr[length];
                NativeMethods.DefParams_CoeffModulus192(polyModulusDegree, ref length, coeff_array);

                result = new List<SmallModulus>(length);
                foreach (IntPtr sm in coeff_array)
                {
                    result.Add(new SmallModulus(sm));
                }
            }
            catch (COMException ex)
            {
                if ((uint)ex.HResult == NativeMethods.Errors.HRInvalidIndex)
                    throw new ArgumentOutOfRangeException(nameof(polyModulusDegree), ex);
                throw;
            }

            return result;
        }

        /// <summary>
        /// Returns the default coefficients modulus for a given polynomial modulus
        /// degree.
        /// </summary>
        /// 
        /// <remarks>
        /// Returns the default coefficients modulus for a given polynomial modulus degree.
        /// The polynomial modulus and the coefficient modulus obtained in this way should
        /// provide approdimately 256 bits of security against the best known attacks,
        /// assuming the standard deviation of the noise distribution is left to its default
        /// value.
        /// </remarks>
        /// <param name="polyModulusDegree">The degree of the polynomial modulus</param>
        /// <exception cref="System.ArgumentOutOfRangeException">if poly_modulus_degree is
        /// not 1024, 2048, 4096, 8192, 16384, or 32768</exception>
        public static IEnumerable<SmallModulus> CoeffModulus256(int polyModulusDegree)
        {
            List<SmallModulus> result = null;

            try
            {
                int length = 0;
                NativeMethods.DefParams_CoeffModulus256(polyModulusDegree, ref length, null);

                IntPtr[] coeff_array = new IntPtr[length];
                NativeMethods.DefParams_CoeffModulus256(polyModulusDegree, ref length, coeff_array);

                result = new List<SmallModulus>(length);
                foreach (IntPtr sm in coeff_array)
                {
                    result.Add(new SmallModulus(sm));
                }
            }
            catch (COMException ex)
            {
                if ((uint)ex.HResult == NativeMethods.Errors.HRInvalidIndex)
                    throw new ArgumentOutOfRangeException(nameof(polyModulusDegree), ex);
                throw;
            }

            return result;
        }

        /// <summary>
        /// Returns a 60-bit coefficient modulus prime.
        /// </summary>
        /// 
        /// <param name="index">The list index of the prime</param>
        /// <exception cref="System.ArgumentOutOfRangeException">if index is not within 
        /// [0, 64)</exception>
        public static SmallModulus SmallMods60Bit(int index)
        {
            try
            {
                IntPtr sm;
                NativeMethods.DefParams_SmallMods60Bit(index, out sm);
                return new SmallModulus(sm);
            }
            catch (COMException ex)
            {
                if ((uint)ex.HResult == NativeMethods.Errors.HRInvalidIndex)
                    throw new ArgumentOutOfRangeException(nameof(index), ex);
                throw;
            }
        }

        /// <summary>
        /// Returns a 50-bit coefficient modulus prime.
        /// </summary>
        /// 
        /// <param name="index">The list index of the prime</param>
        /// <exception cref="System.ArgumentOutOfRangeException">if index is not within
        /// [0, 64)</exception>
        public static SmallModulus SmallMods50Bit(int index)
        {
            try
            {
                IntPtr sm;
                NativeMethods.DefParams_SmallMods50Bit(index, out sm);
                return new SmallModulus(sm);
            }
            catch (COMException ex)
            {
                if ((uint)ex.HResult == NativeMethods.Errors.HRInvalidIndex)
                    throw new ArgumentOutOfRangeException(nameof(index), ex);
                throw;
            }
        }

        /// <summary>
        /// Returns a 40-bit coefficient modulus prime.
        /// </summary>
        /// 
        /// <param name="index">The list index of the prime</param>
        /// <exception cref="System.ArgumentOutOfRangeException">if index is not within
        /// [0, 64)</exception>
        public static SmallModulus SmallMods40Bit(int index)
        {
            try
            {
                IntPtr sm;
                NativeMethods.DefParams_SmallMods40Bit(index, out sm);
                return new SmallModulus(sm);
            }
            catch (COMException ex)
            {
                if ((uint)ex.HResult == NativeMethods.Errors.HRInvalidIndex)
                    throw new ArgumentOutOfRangeException(nameof(index), ex);
                throw;
            }
        }

        /// <summary>
        /// Returns a 30-bit coefficient modulus prime.
        /// </summary>
        /// 
        /// <param name="index">The list index of the prime</param>
        /// <exception cref="System.ArgumentOutOfRangeException">if index is not within
        /// [0, 64)</exception>
        public static SmallModulus SmallMods30Bit(int index)
        {
            try
            {
                IntPtr sm;
                NativeMethods.DefParams_SmallMods30Bit(index, out sm);
                return new SmallModulus(sm);
            }
            catch (COMException ex)
            {
                if ((uint)ex.HResult == NativeMethods.Errors.HRInvalidIndex)
                    throw new ArgumentOutOfRangeException(nameof(index), ex);
                throw;
            }
        }

        /// </summary>
        /// Returns the largest allowed decomposition bit count (60).
        /// </summary>
        public static int DBCmax
        {
            get
            {
                NativeMethods.DefParams_DBCMax(out int dbcMax);
                return dbcMax;
            }
        }


        /// </summary>
        /// Returns the smallest allowed decomposition bit count (1).
        /// </summary>
        public static int DBCmin
        {
            get
            {
                NativeMethods.DefParams_DBCMin(out int dbcMin);
                return dbcMin;
            }
        }
    }
}
