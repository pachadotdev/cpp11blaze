// cpp11armadillo version: 0.3.2
// vendored on: 2024-09-02
// SPDX-License-Identifier: Apache-2.0
//
// Copyright 2008-2016 Conrad Sanderson (http://conradsanderson.id.au)
// Copyright 2008-2016 National ICT Australia (NICTA)
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ------------------------------------------------------------------------

//! \addtogroup fn_cross
//! @{

//! cross product (only valid for 3 dimensional vectors)
template <typename T1, typename T2>
arma_warn_unused inline typename enable_if2<
    is_arma_type<T1>::value && is_arma_type<T2>::value &&
        is_same_type<typename T1::elem_type, typename T2::elem_type>::value,
    const Glue<T1, T2, glue_cross> >::result
cross(const T1& X, const T2& Y) {
  arma_debug_sigprint();

  return Glue<T1, T2, glue_cross>(X, Y);
}

//! @}
