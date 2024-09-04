// cpp11blaze version: 0.2.0
// vendored on: 2024-09-03
//=================================================================================================
/*!
//  \file blaze/util/algorithms/UninitializedTransfer.h
//  \brief Header file for the generic uninitialized_transfer algorithm
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

#ifndef _BLAZE_UTIL_ALGORITHMS_UNINITIALIZEDTRANSFER_H_
#define _BLAZE_UTIL_ALGORITHMS_UNINITIALIZEDTRANSFER_H_


//*************************************************************************************************
// Includes
//*************************************************************************************************

#include <algorithm>
#include <iterator>
#include <blaze/util/algorithms/UninitializedMove.h>
#include <blaze/util/typetraits/IsAssignable.h>


namespace blaze {

//=================================================================================================
//
//  UNINITIALIZED_TRANSFER ALGORITHMS
//
//=================================================================================================

//*************************************************************************************************
/*!\brief Transfers the elements from the given source range to the uninitialized destination range.
// \ingroup algorithms
//
// \param first Iterator to the first element of the source range.
// \param last Iterator to the element one past the last element of the source range.
// \param dest Iterator to the first element of the destination range.
// \return Output iterator to the element one past the last copied element.
//
// This function transfers the elements in the range \f$ [first,last) \f$ to the specified
// destination range. The destination range is assumed to be uninitialized. In case the elements
// provide a no-throw move assignment operator, the transfer operation is handled via move
// construction, else the elements are copied constructed.
*/
template< typename InputIt
        , typename ForwardIt >
ForwardIt uninitialized_transfer( InputIt first, InputIt last, ForwardIt dest )
{
   using T = typename std::iterator_traits<InputIt>::value_type;

   if( IsNothrowMoveAssignable_v<T> ) {
      return blaze::uninitialized_move( first, last, dest );
   }
   else {
      return std::uninitialized_copy( first, last, dest );
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Transfers the elements from the given source range to the uninitialized destination range.
// \ingroup algorithms
//
// \param first Iterator to the first element of the source range.
// \param n The number of elements to be moved.
// \param dest Iterator to the first element of the destination range.
// \return Output iterator to the element one past the last copied element.
//
// This function transfers the elements in the range \f$ [first,first+n) \f$ to the specified
// destination range. The destination range is assumed to be uninitialized. In case the elements
// provide a no-throw move assignment operator, the transfer operation is handled via move
// construction, else the elements are copied constructed.
*/
template< typename InputIt
        , typename ForwardIt >
ForwardIt uninitialized_transfer_n( InputIt first, size_t n, ForwardIt dest )
{
   using T = typename std::iterator_traits<InputIt>::value_type;

   if( IsNothrowMoveAssignable_v<T> ) {
      return blaze::uninitialized_move_n( first, n, dest );
   }
   else {
      return std::uninitialized_copy_n( first, n, dest );
   }
}
//*************************************************************************************************

} // namespace blaze

#endif
