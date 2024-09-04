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

//! \addtogroup op_stddev
//! @{

class op_stddev : public traits_op_xvec {
 public:
  template <typename T1>
  inline static void apply(Mat<typename T1::pod_type>& out,
                           const mtOp<typename T1::pod_type, T1, op_stddev>& in);

  template <typename in_eT>
  inline static void apply_noalias(Mat<typename get_pod_type<in_eT>::result>& out,
                                   const Mat<in_eT>& X, const uword norm_type,
                                   const uword dim);

  //

  template <typename eT>
  inline static typename get_pod_type<eT>::result stddev_vec(const subview_col<eT>& X,
                                                             const uword norm_type = 0);

  template <typename eT>
  inline static typename get_pod_type<eT>::result stddev_vec(const subview_row<eT>& X,
                                                             const uword norm_type = 0);

  template <typename T1>
  inline static typename T1::pod_type stddev_vec(
      const Base<typename T1::elem_type, T1>& X, const uword norm_type = 0);
};

//! @}
