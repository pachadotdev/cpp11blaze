// cpp11blaze version: 0.2.0
// vendored on: 2024-09-03
//=================================================================================================
/*!
//  \file blaze/math/lapack/clapack/gesdd.h
//  \brief Header file for the CLAPACK gesdd wrapper functions
//
//  Copyright (C) 2012-2020 Klaus Iglberger - All Rights Reserved
//
//  This file is part of the Blaze library. You can redistribute it and/or modify it under
//  the terms of the New (Revised) BSD License. Redistribution and use in source and binary
//  forms, with or without modification, are permitted provided that the following conditions
//  are met:
//
//  1. Redistributions of source code must retain the above copyright notice, this list of
//     conditions and the following disclaimer.
//  2. Redistributions in binary form must reproduce the above copyright notice, this list
//     of conditions and the following disclaimer in the documentation and/or other materials
//     provided with the distribution.
//  3. Neither the names of the Blaze development group nor the names of its contributors
//     may be used to endorse or promote products derived from this software without specific
//     prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
//  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
//  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
//  SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
//  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
//  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
//  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
//  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
//  DAMAGE.
*/
//=================================================================================================

#ifndef _BLAZE_MATH_LAPACK_CLAPACK_GESDD_H_
#define _BLAZE_MATH_LAPACK_CLAPACK_GESDD_H_


//*************************************************************************************************
// Includes
//*************************************************************************************************

#include <blaze/math/blas/Types.h>
#include <blaze/util/Complex.h>
#include <blaze/util/StaticAssert.h>
#include <blaze/util/Types.h>


//=================================================================================================
//
//  LAPACK FORWARD DECLARATIONS
//
//=================================================================================================

//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
#if !defined(INTEL_MKL_VERSION)
extern "C" {

void sgesdd_( char* jobz, blaze::blas_int_t* m, blaze::blas_int_t* n, float* A,
              blaze::blas_int_t* lda, float* s, float* U, blaze::blas_int_t* ldu,
              float* V, blaze::blas_int_t* ldv, float* work, blaze::blas_int_t* lwork,
              blaze::blas_int_t* iwork, blaze::blas_int_t* info,
              blaze::fortran_charlen_t njobz );
void dgesdd_( char* jobz, blaze::blas_int_t* m, blaze::blas_int_t* n, double* A,
              blaze::blas_int_t* lda, double* s, double* U, blaze::blas_int_t* ldu,
              double* V, blaze::blas_int_t* ldv, double* work, blaze::blas_int_t* lwork,
              blaze::blas_int_t* iwork, blaze::blas_int_t* info,
              blaze::fortran_charlen_t njobz );
void cgesdd_( char* jobz, blaze::blas_int_t* m, blaze::blas_int_t* n, float* A,
              blaze::blas_int_t* lda, float* s, float* U, blaze::blas_int_t* ldu,
              float* V, blaze::blas_int_t* ldv, float* work, blaze::blas_int_t* lwork,
              float* rwork, blaze::blas_int_t* iwork, blaze::blas_int_t* info,
              blaze::fortran_charlen_t njobz );
void zgesdd_( char* jobz, blaze::blas_int_t* m, blaze::blas_int_t* n, double* A,
              blaze::blas_int_t* lda, double* s, double* U, blaze::blas_int_t* ldu,
              double* V, blaze::blas_int_t* ldv, double* work, blaze::blas_int_t* lwork,
              double* rwork, blaze::blas_int_t* iwork, blaze::blas_int_t* info,
              blaze::fortran_charlen_t njobz );

}
#endif
/*! \endcond */
//*************************************************************************************************




namespace blaze {

//=================================================================================================
//
//  LAPACK SVD FUNCTIONS (GESDD)
//
//=================================================================================================

//*************************************************************************************************
/*!\name LAPACK SVD functions (gesdd) */
//@{
void gesdd( char jobz, blas_int_t m, blas_int_t n, float* A, blas_int_t lda,
            float* s, float* U, blas_int_t ldu, float* V, blas_int_t ldv,
            float* work, blas_int_t lwork, blas_int_t* iwork, blas_int_t* info );

void gesdd( char jobz, blas_int_t m, blas_int_t n, double* A, blas_int_t lda,
            double* s, double* U, blas_int_t ldu, double* V, blas_int_t ldv,
            double* work, blas_int_t lwork, blas_int_t* iwork, blas_int_t* info );

void gesdd( char jobz, blas_int_t m, blas_int_t n, complex<float>* A, blas_int_t lda,
            float* s, complex<float>* U, blas_int_t ldu, complex<float>* V, blas_int_t ldv,
            complex<float>* work, blas_int_t lwork, float* rwork, blas_int_t* iwork,
            blas_int_t* info );

void gesdd( char jobz, blas_int_t m, blas_int_t n, complex<double>* A, blas_int_t lda,
            double* s, complex<double>* U, blas_int_t ldu, complex<double>* V, blas_int_t ldv,
            complex<double>* work, blas_int_t lwork, double* rwork, blas_int_t* iwork,
            blas_int_t* info );
//@}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief LAPACK kernel for the singular value decomposition (SVD) of the given dense general
//        single precision column-major matrix.
// \ingroup lapack_singular_value
//
// \param jobz Specifies the computation of the singular vectors (\c 'A', \c 'S', \c 'O' or \c 'N').
// \param m The number of rows of the given matrix \f$[0..\infty)\f$.
// \param n The number of columns of the given matrix \f$[0..\infty)\f$.
// \param A Pointer to the first element of the single precision column-major matrix.
// \param lda The total number of elements between two columns of the matrix A \f$[0..\infty)\f$.
// \param s Pointer to the first element of the vector for the singular values.
// \param U Pointer to the first element of the column-major matrix for the left singular vectors.
// \param ldu The total number of elements between two columns of the matrix U \f$[0..\infty)\f$.
// \param V Pointer to the first element of the column-major matrix for the right singular vectors.
// \param ldv The total number of elements between two columns of the matrix V \f$[0..\infty)\f$.
// \param work Auxiliary array; size >= max(1, \a lwork).
// \param lwork The dimension of the array \a work; see online reference for details.
// \param iwork Auxiliary array; size >= 8*min(\a m,\a n).
// \param info Return code of the function call.
// \return void
//
// This function performs the singular value decomposition of a general \a m-by-\a n single
// precision column-major matrix based on the LAPACK sgesdd() function. Optionally, it computes
// the left and/or right singular vectors using a divide-and-conquer strategy. The resulting
// decomposition has the form

                           \f[ A = U \cdot S \cdot V, \f]

// where \c S is a \a m-by-\a n matrix, which is zero except for its min(\a m,\a n) diagonal
// elements, which are stored in \a s, \a U is an \a m-by-\a m orthogonal matrix, and \a V
// is a \a n-by-\a n orthogonal matrix. The diagonal elements of \c S are the singular values
// of \a A; they are real and non-negative, and are returned in descending order. The first
// min(\a m,\a n) columns of \a U and \a rows of V are the left and right singular vectors
// of \a A.
//
// The parameter \a jobz specifies the computation of the left and right singular vectors:
//
//   - \c 'A': All \a m columns of \a U and all \a n rows of \a V are returned in \a U and
//             \a V; \a U must be a general \a m-by-\a m matrix and \a V must be a general
//             \a n-by-\a n matrix.
//   - \c 'S': The first min(\a m,\a n) columns of \a U and the first min(\a m,\a n) rows of
//             \a V are returned in \a U and \a V; \a U must be a \a m-by-min(\a m,\a n)
//             matrix and \a V must be a min(\a m,\a n)-by-\a n matrix.
//   - \c 'O': If \a m >= \a n, the first \a n columns of \a U are returned in \a A and all
//             rows of \a V are returned in \a V; matrix \a U is not referenced. Otherwise
//             all columns of \a U are returned in \a U and the first \a m rows of \a V are
//             returned in \a A; matrix \a V is not referenced.
//   - \c 'N': No columns of \a U or rows of \a V are computed; both \a U and \a V are not
//             referenced.
//
// The \a info argument provides feedback on the success of the function call:
//
//   - = 0: The decomposition finished successfully.
//   - < 0: If info = -i, the i-th argument had an illegal value.
//   - > 0: The decomposition did not converge.
//
// For more information on the sgesdd() function, see the LAPACK online documentation browser:
//
//        http://www.netlib.org/lapack/explore-html/
//
// \note This function can only be used if a fitting LAPACK library, which supports this function,
// is available and linked to the executable. Otherwise a call to this function will result in a
// linker error.
*/
inline void gesdd( char jobz, blas_int_t m, blas_int_t n, float* A, blas_int_t lda,
                   float* s, float* U, blas_int_t ldu, float* V, blas_int_t ldv, float* work,
                   blas_int_t lwork, blas_int_t* iwork, blas_int_t* info )
{
#if defined(INTEL_MKL_VERSION)
   BLAZE_STATIC_ASSERT( sizeof( MKL_INT ) == sizeof( blas_int_t ) );
#endif

   sgesdd_( &jobz, &m, &n, A, &lda, s, U, &ldu, V, &ldv, work, &lwork, iwork, info
#if !defined(INTEL_MKL_VERSION)
          , blaze::fortran_charlen_t(1)
#endif
          );
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief LAPACK kernel for the singular value decomposition (SVD) of the given dense general
//        double precision column-major matrix.
// \ingroup lapack_singular_value
//
// \param jobz Specifies the computation of the singular vectors (\c 'A', \c 'S', \c 'O' or \c 'N').
// \param m The number of rows of the given matrix \f$[0..\infty)\f$.
// \param n The number of columns of the given matrix \f$[0..\infty)\f$.
// \param A Pointer to the first element of the double precision column-major matrix.
// \param lda The total number of elements between two columns of the matrix A \f$[0..\infty)\f$.
// \param s Pointer to the first element of the vector for the singular values.
// \param U Pointer to the first element of the column-major matrix for the left singular vectors.
// \param ldu The total number of elements between two columns of the matrix U \f$[0..\infty)\f$.
// \param V Pointer to the first element of the column-major matrix for the right singular vectors.
// \param ldv The total number of elements between two columns of the matrix V \f$[0..\infty)\f$.
// \param work Auxiliary array; size >= max(1, \a lwork).
// \param lwork The dimension of the array \a work; see online reference for details.
// \param iwork Auxiliary array; size >= 8*min(\a m,\a n).
// \param info Return code of the function call.
// \return void
//
// This function performs the singular value decomposition of a general \a m-by-\a n double
// precision column-major matrix based on the LAPACK dgesdd() function. Optionally, it computes
// the left and/or right singular vectors using a divide-and-conquer strategy. The resulting
// decomposition has the form

                           \f[ A = U \cdot S \cdot V, \f]

// where \c S is a \a m-by-\a n matrix, which is zero except for its min(\a m,\a n) diagonal
// elements, which are stored in \a s, \a U is an \a m-by-\a m orthogonal matrix, and \a V
// is a \a n-by-\a n orthogonal matrix. The diagonal elements of \c S are the singular values
// of \a A; they are real and non-negative, and are returned in descending order. The first
// min(\a m,\a n) columns of \a U and \a rows of V are the left and right singular vectors
// of \a A.
//
// The parameter \a jobz specifies the computation of the left and right singular vectors:
//
//   - \c 'A': All \a m columns of \a U and all \a n rows of \a V are returned in \a U and
//             \a V; \a U must be a general \a m-by-\a m matrix and \a V must be a general
//             \a n-by-\a n matrix.
//   - \c 'S': The first min(\a m,\a n) columns of \a U and the first min(\a m,\a n) rows of
//             \a V are returned in \a U and \a V; \a U must be a \a m-by-min(\a m,\a n)
//             matrix and \a V must be a min(\a m,\a n)-by-\a n matrix.
//   - \c 'O': If \a m >= \a n, the first \a n columns of \a U are returned in \a A and all
//             rows of \a V are returned in \a V; matrix \a U is not referenced. Otherwise
//             all columns of \a U are returned in \a U and the first \a m rows of \a V are
//             returned in \a A; matrix \a V is not referenced.
//   - \c 'N': No columns of \a U or rows of \a V are computed; both \a U and \a V are not
//             referenced.
//
// The \a info argument provides feedback on the success of the function call:
//
//   - = 0: The decomposition finished successfully.
//   - < 0: If info = -i, the i-th argument had an illegal value.
//   - > 0: The decomposition did not converge.
//
// For more information on the dgesdd() function, see the LAPACK online documentation browser:
//
//        http://www.netlib.org/lapack/explore-html/
//
// \note This function can only be used if a fitting LAPACK library, which supports this function,
// is available and linked to the executable. Otherwise a call to this function will result in a
// linker error.
*/
inline void gesdd( char jobz, blas_int_t m, blas_int_t n, double* A, blas_int_t lda,
                   double* s, double* U, blas_int_t ldu, double* V, blas_int_t ldv,
                   double* work, blas_int_t lwork, blas_int_t* iwork, blas_int_t* info )
{
#if defined(INTEL_MKL_VERSION)
   BLAZE_STATIC_ASSERT( sizeof( MKL_INT ) == sizeof( blas_int_t ) );
#endif

   dgesdd_( &jobz, &m, &n, A, &lda, s, U, &ldu, V, &ldv, work, &lwork, iwork, info
#if !defined(INTEL_MKL_VERSION)
          , blaze::fortran_charlen_t(1)
#endif
          );
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief LAPACK kernel for the singular value decomposition (SVD) of the given dense general
//        single precision complex column-major matrix.
// \ingroup lapack_singular_value
//
// \param jobz Specifies the computation of the singular vectors (\c 'A', \c 'S', \c 'O' or \c 'N').
// \param m The number of rows of the given matrix \f$[0..\infty)\f$.
// \param n The number of columns of the given matrix \f$[0..\infty)\f$.
// \param A Pointer to the first element of the single precision complex column-major matrix.
// \param lda The total number of elements between two columns of the matrix A \f$[0..\infty)\f$.
// \param s Pointer to the first element of the vector for the singular values.
// \param U Pointer to the first element of the column-major matrix for the left singular vectors.
// \param ldu The total number of elements between two columns of the matrix U \f$[0..\infty)\f$.
// \param V Pointer to the first element of the column-major matrix for the right singular vectors.
// \param ldv The total number of elements between two columns of the matrix V \f$[0..\infty)\f$.
// \param work Auxiliary array; size >= max(1, \a lwork).
// \param lwork The dimension of the array \a work; see online reference for details.
// \param rwork Auxiliary array; see online reference for details.
// \param iwork Auxiliary array; size >= 8*min(\a m,\a n).
// \param info Return code of the function call.
// \return void
//
// This function performs the singular value decomposition of a general \a m-by-\a n single
// precision complex column-major matrix based on the LAPACK cgesdd() function. Optionally, it
// computes the left and/or right singular vectors using a divide-and-conquer strategy. The
// resulting decomposition has the form

                           \f[ A = U \cdot S \cdot V, \f]

// where \c S is a \a m-by-\a n matrix, which is zero except for its min(\a m,\a n) diagonal
// elements, which are stored in \a s, \a U is an \a m-by-\a m orthogonal matrix, and \a V
// is a \a n-by-\a n orthogonal matrix. The diagonal elements of \c S are the singular values
// of \a A; they are real and non-negative, and are returned in descending order. The first
// min(\a m,\a n) columns of \a U and \a rows of V are the left and right singular vectors
// of \a A.
//
// The parameter \a jobz specifies the computation of the left and right singular vectors:
//
//   - \c 'A': All \a m columns of \a U and all \a n rows of \a V are returned in \a U and
//             \a V; \a U must be a general \a m-by-\a m matrix and \a V must be a general
//             \a n-by-\a n matrix.
//   - \c 'S': The first min(\a m,\a n) columns of \a U and the first min(\a m,\a n) rows of
//             \a V are returned in \a U and \a V; \a U must be a \a m-by-min(\a m,\a n)
//             matrix and \a V must be a min(\a m,\a n)-by-\a n matrix.
//   - \c 'O': If \a m >= \a n, the first \a n columns of \a U are returned in \a A and all
//             rows of \a V are returned in \a V; matrix \a U is not referenced. Otherwise
//             all columns of \a U are returned in \a U and the first \a m rows of \a V are
//             returned in \a A; matrix \a V is not referenced.
//   - \c 'N': No columns of \a U or rows of \a V are computed; both \a U and \a V are not
//             referenced.
//
// The \a info argument provides feedback on the success of the function call:
//
//   - = 0: The decomposition finished successfully.
//   - < 0: If info = -i, the i-th argument had an illegal value.
//   - > 0: The decomposition did not converge.
//
// For more information on the cgesdd() function, see the LAPACK online documentation browser:
//
//        http://www.netlib.org/lapack/explore-html/
//
// \note This function can only be used if a fitting LAPACK library, which supports this function,
// is available and linked to the executable. Otherwise a call to this function will result in a
// linker error.
*/
inline void gesdd( char jobz, blas_int_t m, blas_int_t n, complex<float>* A, blas_int_t lda,
                   float* s, complex<float>* U, blas_int_t ldu, complex<float>* V, blas_int_t ldv,
                   complex<float>* work, blas_int_t lwork, float* rwork, blas_int_t* iwork,
                   blas_int_t* info )
{
   BLAZE_STATIC_ASSERT( sizeof( complex<float> ) == 2UL*sizeof( float ) );

#if defined(INTEL_MKL_VERSION)
   BLAZE_STATIC_ASSERT( sizeof( MKL_INT ) == sizeof( blas_int_t ) );
   BLAZE_STATIC_ASSERT( sizeof( MKL_Complex8 ) == sizeof( complex<float> ) );
   using ET = MKL_Complex8;
#else
   using ET = float;
#endif

   cgesdd_( &jobz, &m, &n, reinterpret_cast<ET*>( A ), &lda, s,
            reinterpret_cast<ET*>( U ), &ldu, reinterpret_cast<ET*>( V ), &ldv,
            reinterpret_cast<ET*>( work ), &lwork, rwork, iwork, info
#if !defined(INTEL_MKL_VERSION)
          , blaze::fortran_charlen_t(1)
#endif
          );
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief LAPACK kernel for the singular value decomposition (SVD) of the given dense general
//        double precision complex column-major matrix.
// \ingroup lapack_singular_value
//
// \param jobz Specifies the computation of the singular vectors (\c 'A', \c 'S', \c 'O' or \c 'N').
// \param m The number of rows of the given matrix \f$[0..\infty)\f$.
// \param n The number of columns of the given matrix \f$[0..\infty)\f$.
// \param A Pointer to the first element of the double precision complex column-major matrix.
// \param lda The total number of elements between two columns of the matrix A \f$[0..\infty)\f$.
// \param s Pointer to the first element of the vector for the singular values.
// \param U Pointer to the first element of the column-major matrix for the left singular vectors.
// \param ldu The total number of elements between two columns of the matrix U \f$[0..\infty)\f$.
// \param V Pointer to the first element of the column-major matrix for the right singular vectors.
// \param ldv The total number of elements between two columns of the matrix V \f$[0..\infty)\f$.
// \param work Auxiliary array; size >= max(1, \a lwork).
// \param lwork The dimension of the array \a work; see online reference for details.
// \param rwork Auxiliary array; see online reference for details.
// \param iwork Auxiliary array; size >= 8*min(\a m,\a n).
// \param info Return code of the function call.
// \return void
//
// This function performs the singular value decomposition of a general \a m-by-\a n double
// precision complex column-major matrix based on the LAPACK zgesdd() function. Optionally, it
// computes the left and/or right singular vectors using a divide-and-conquer strategy. The
// resulting decomposition has the form

                           \f[ A = U \cdot S \cdot V, \f]

// where \c S is a \a m-by-\a n matrix, which is zero except for its min(\a m,\a n) diagonal
// elements, which are stored in \a s, \a U is an \a m-by-\a m orthogonal matrix, and \a V
// is a \a n-by-\a n orthogonal matrix. The diagonal elements of \c S are the singular values
// of \a A; they are real and non-negative, and are returned in descending order. The first
// min(\a m,\a n) columns of \a U and rows of \a V are the left and right singular vectors
// of \a A.
//
// The parameter \a jobz specifies the computation of the left and right singular vectors:
//
//   - \c 'A': All \a m columns of \a U and all \a n rows of \a V are returned in \a U and
//             \a V; \a U must be a general \a m-by-\a m matrix and \a V must be a general
//             \a n-by-\a n matrix.
//   - \c 'S': The first min(\a m,\a n) columns of \a U and the first min(\a m,\a n) rows of
//             \a V are returned in \a U and \a V; \a U must be a \a m-by-min(\a m,\a n)
//             matrix and \a V must be a min(\a m,\a n)-by-\a n matrix.
//   - \c 'O': If \a m >= \a n, the first \a n columns of \a U are returned in \a A and all
//             rows of \a V are returned in \a V; matrix \a U is not referenced. Otherwise
//             all columns of \a U are returned in \a U and the first \a m rows of \a V are
//             returned in \a A; matrix \a V is not referenced.
//   - \c 'N': No columns of \a U or rows of \a V are computed; both \a U and \a V are not
//             referenced.
//
// The \a info argument provides feedback on the success of the function call:
//
//   - = 0: The decomposition finished successfully.
//   - < 0: If info = -i, the i-th argument had an illegal value.
//   - > 0: The decomposition did not converge.
//
// For more information on the zgesdd() function, see the LAPACK online documentation browser:
//
//        http://www.netlib.org/lapack/explore-html/
//
// \note This function can only be used if a fitting LAPACK library, which supports this function,
// is available and linked to the executable. Otherwise a call to this function will result in a
// linker error.
*/
inline void gesdd( char jobz, blas_int_t m, blas_int_t n, complex<double>* A, blas_int_t lda,
                   double* s, complex<double>* U, blas_int_t ldu, complex<double>* V, blas_int_t ldv,
                   complex<double>* work, blas_int_t lwork, double* rwork, blas_int_t* iwork,
                   blas_int_t* info )
{
   BLAZE_STATIC_ASSERT( sizeof( complex<double> ) == 2UL*sizeof( double ) );

#if defined(INTEL_MKL_VERSION)
   BLAZE_STATIC_ASSERT( sizeof( MKL_INT ) == sizeof( blas_int_t ) );
   BLAZE_STATIC_ASSERT( sizeof( MKL_Complex16 ) == sizeof( complex<double> ) );
   using ET = MKL_Complex16;
#else
   using ET = double;
#endif

   zgesdd_( &jobz, &m, &n, reinterpret_cast<ET*>( A ), &lda, s,
            reinterpret_cast<ET*>( U ), &ldu, reinterpret_cast<ET*>( V ), &ldv,
            reinterpret_cast<ET*>( work ), &lwork, rwork, iwork, info
#if !defined(INTEL_MKL_VERSION)
          , blaze::fortran_charlen_t(1)
#endif
          );
}
//*************************************************************************************************

} // namespace blaze

#endif
