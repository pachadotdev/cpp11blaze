// cpp11blaze version: 0.2.0
// vendored on: 2024-09-03
//=================================================================================================
/*!
//  \file blaze/util/constraints/Constraints.h
//  \brief Header file for compile time constraints
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

#ifndef _BLAZE_UTIL_CONSTRAINTS_CONSTRAINTS_H_
#define _BLAZE_UTIL_CONSTRAINTS_CONSTRAINTS_H_


//=================================================================================================
//
//  DOXYGEN DOCUMENTATION
//
//=================================================================================================

//*************************************************************************************************
/*!\defgroup constraints Compile time constraints
// \ingroup util
//
// Compile time constraints offer the possibility to stop the compilation process if a constraint
// that can be checked at compile time is not met. These constraints are especially useful for
// generic code, where the type of the involved objects is not known beforehands.\n
// Since C++11 the C++ standard provides the \c static_assert functionality to check compile time
// constant expressions:

   \code
   template <class T>
   class RotationMatrix
   {
      // ...
      static_assert( std::is_floating_point_v<T>, "Non-floating point type detected" );
      // ...
   };
   \endcode

// The Blaze library extends this functionality in the form of compile time constraint macros:

   \code
   template <class T>
   class RotationMatrix
   {
      // ...
      BLAZE_CONSTRAINT_MUST_BE_FLOATING_POINT_TYPE( T );
      // ...
   };
   \endcode

// The compile time constraints provided by the Blaze library built on \c static_assert, but offer
// the additional advantages ...
//
//   - ... of a more convenient and easier usage since details are abstracted;
//   - ... of a more obvious and more explicit way to express compile time constraints;
//   - ... of encapsulation of complex compile time conditions.
//
// The following example demonstrates the \c BLAZE_CONSTRAINT_MUST_BE_DERIVED_FROM time constraint
// and shows a possible error message:

   \code
   //----- Test.cpp -----
   #include <blaze/Util.h>

   class A {};
   class B : public A {};
   class C {};

   int main()
   {
      BLAZE_CONSTRAINT_MUST_BE_DERIVED_FROM( B, A );  // No compile time error, B is derived from A
      BLAZE_CONSTRAINT_MUST_BE_DERIVED_FROM( C, A );  // Compile time error, C is not derived from A
   }
   \endcode

// The resulting error message generated by the GNU g++ compiler contains the name of the
// constraint, a descriptive error message and the source code line of the constraint violation:

   \code
   ~/blaze/blaze/util/constraints/DerivedFrom.h:61:4: static assertion failed: Broken inheritance hierarchy detected
      static_assert( ::blaze::IsBaseOf_v<B,D>, "Broken inheritance hierarchy detected" )
      ^
   Test.cpp:11:4: note: in expansion of macro 'BLAZE_CONSTRAINT_MUST_BE_DERIVED_FROM'
      BLAZE_CONSTRAINT_MUST_BE_DERIVED_FROM( C, A );  // Compile time error, C is not derived from A
   \endcode
*/
//*************************************************************************************************

#endif
