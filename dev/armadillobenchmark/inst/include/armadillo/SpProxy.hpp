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

//! \addtogroup SpProxy
//! @{

// TODO: clarify and check which variables and functions are valid when 'use_iterator' is
// either true or false

// within each specialisation of the Proxy class:
//
// elem_type               = type of the elements obtained from object Q
// pod_type                = underlying type of elements if elem_type is std::complex
// stored_type             = type of Q object
//
// const_iterator_type     = type of iterator provided by begin() and begin_col()
// const_row_iterator_type = type of iterator provided by begin_row()
//
// use_iterator            = boolean to indicate that provided iterators must be used for
// accessing elements Q_is_generated          = boolean to indicate Q object was generated
// by SpProxy
//
// is_row                  = boolean to indicate Q object can be treated a row vector
// is_col                  = boolean to indicate Q object can be treated a column vector
// is_xvec                 = boolean to indicate Q object is a vector with unknown
// orientation
//
// Q                       = object that can be unwrapped via unwrap_spmat family of
// classes (ie. Q must be convertible to SpMat)
//
// get_n_rows()            = return number of rows in Q
// get_n_cols()            = return number of columns in Q
// get_n_elem()            = return number of elements in Q
// get_n_nonzero()         = return number of non-zero elements in Q
//
// operator[i]             = linear element accessor;       valid only if the
// 'use_iterator' boolean is false at(row,col)             = access elements via
// (row,col); valid only if the 'use_iterator' boolean is false
//
// get_values()            = return pointer to CSC          values array in Q; valid only
// if the 'use_iterator' boolean is false get_row_indices()       = return pointer to CSC
// row indices array in Q; valid only if the 'use_iterator' boolean is false
// get_col_ptrs()          = return pointer to CSC column pointers array in Q; valid only
// if the 'use_iterator' boolean is false
//
// begin()                 = column-wise iterator indicating first element in Q
// begin_col(col_num)      = column-wise iterator indicating first element in column
// 'col_num' in Q begin_row(row_num = 0)  =    row-wise iterator indicating first element
// in row    'row_num' in Q
//
// end()                   = column-wise iterator indicating "one-past-end" element in Q
// end_row()               =    row-wise iterator indicating "one-past-end" element in Q
// end_row(row_num)        =    row-wise iterator indicating "one-past-end" element in row
// 'row_num' in Q
//
// is_alias(X)             = return true/false to indicate Q object aliases matrix X

template <typename eT>
struct SpProxy<SpMat<eT> > {
  typedef eT elem_type;
  typedef typename get_pod_type<elem_type>::result pod_type;
  typedef SpMat<eT> stored_type;

  typedef typename SpMat<eT>::const_iterator const_iterator_type;
  typedef typename SpMat<eT>::const_row_iterator const_row_iterator_type;

  static constexpr bool use_iterator = false;
  static constexpr bool Q_is_generated = false;

  static constexpr bool is_row = false;
  static constexpr bool is_col = false;
  static constexpr bool is_xvec = false;

  arma_aligned const SpMat<eT>& Q;

  inline explicit SpProxy(const SpMat<eT>& A) : Q(A) {
    arma_debug_sigprint();
    Q.sync();
  }

  arma_inline uword get_n_rows() const { return Q.n_rows; }
  arma_inline uword get_n_cols() const { return Q.n_cols; }
  arma_inline uword get_n_elem() const { return Q.n_elem; }
  arma_inline uword get_n_nonzero() const { return Q.n_nonzero; }

  arma_inline elem_type operator[](const uword i) const { return Q[i]; }
  arma_inline elem_type at(const uword row, const uword col) const {
    return Q.at(row, col);
  }

  arma_inline const eT* get_values() const { return Q.values; }
  arma_inline const uword* get_row_indices() const { return Q.row_indices; }
  arma_inline const uword* get_col_ptrs() const { return Q.col_ptrs; }

  arma_inline const_iterator_type begin() const { return Q.begin(); }
  arma_inline const_iterator_type begin_col(const uword col_num) const {
    return Q.begin_col(col_num);
  }
  arma_inline const_row_iterator_type begin_row(const uword row_num = 0) const {
    return Q.begin_row(row_num);
  }

  arma_inline const_iterator_type end() const { return Q.end(); }
  arma_inline const_row_iterator_type end_row() const { return Q.end_row(); }
  arma_inline const_row_iterator_type end_row(const uword row_num) const {
    return Q.end_row(row_num);
  }

  template <typename eT2>
  arma_inline bool is_alias(const SpMat<eT2>& X) const {
    return (is_same_type<eT, eT2>::yes) && (void_ptr(&Q) == void_ptr(&X));
  }
};

template <typename eT>
struct SpProxy<SpCol<eT> > {
  typedef eT elem_type;
  typedef typename get_pod_type<elem_type>::result pod_type;
  typedef SpCol<eT> stored_type;

  typedef typename SpCol<eT>::const_iterator const_iterator_type;
  typedef typename SpCol<eT>::const_row_iterator const_row_iterator_type;

  static constexpr bool use_iterator = false;
  static constexpr bool Q_is_generated = false;

  static constexpr bool is_row = false;
  static constexpr bool is_col = true;
  static constexpr bool is_xvec = false;

  arma_aligned const SpCol<eT>& Q;

  inline explicit SpProxy(const SpCol<eT>& A) : Q(A) {
    arma_debug_sigprint();
    Q.sync();
  }

  arma_inline uword get_n_rows() const { return Q.n_rows; }
  constexpr uword get_n_cols() const { return 1; }
  arma_inline uword get_n_elem() const { return Q.n_elem; }
  arma_inline uword get_n_nonzero() const { return Q.n_nonzero; }

  arma_inline elem_type operator[](const uword i) const { return Q[i]; }
  arma_inline elem_type at(const uword row, const uword col) const {
    return Q.at(row, col);
  }

  arma_inline const eT* get_values() const { return Q.values; }
  arma_inline const uword* get_row_indices() const { return Q.row_indices; }
  arma_inline const uword* get_col_ptrs() const { return Q.col_ptrs; }

  arma_inline const_iterator_type begin() const { return Q.begin(); }
  arma_inline const_iterator_type begin_col(const uword) const { return Q.begin(); }
  arma_inline const_row_iterator_type begin_row(const uword row_num = 0) const {
    return Q.begin_row(row_num);
  }

  arma_inline const_iterator_type end() const { return Q.end(); }
  arma_inline const_row_iterator_type end_row() const { return Q.end_row(); }
  arma_inline const_row_iterator_type end_row(const uword row_num) const {
    return Q.end_row(row_num);
  }

  template <typename eT2>
  arma_inline bool is_alias(const SpMat<eT2>& X) const {
    return (is_same_type<eT, eT2>::yes) && (void_ptr(&Q) == void_ptr(&X));
  }
};

template <typename eT>
struct SpProxy<SpRow<eT> > {
  typedef eT elem_type;
  typedef typename get_pod_type<elem_type>::result pod_type;
  typedef SpRow<eT> stored_type;

  typedef typename SpRow<eT>::const_iterator const_iterator_type;
  typedef typename SpRow<eT>::const_row_iterator const_row_iterator_type;

  static constexpr bool use_iterator = false;
  static constexpr bool Q_is_generated = false;

  static constexpr bool is_row = true;
  static constexpr bool is_col = false;
  static constexpr bool is_xvec = false;

  arma_aligned const SpRow<eT>& Q;

  inline explicit SpProxy(const SpRow<eT>& A) : Q(A) {
    arma_debug_sigprint();
    Q.sync();
  }

  constexpr uword get_n_rows() const { return 1; }
  arma_inline uword get_n_cols() const { return Q.n_cols; }
  arma_inline uword get_n_elem() const { return Q.n_elem; }
  arma_inline uword get_n_nonzero() const { return Q.n_nonzero; }

  arma_inline elem_type operator[](const uword i) const { return Q[i]; }
  arma_inline elem_type at(const uword row, const uword col) const {
    return Q.at(row, col);
  }

  arma_inline const eT* get_values() const { return Q.values; }
  arma_inline const uword* get_row_indices() const { return Q.row_indices; }
  arma_inline const uword* get_col_ptrs() const { return Q.col_ptrs; }

  arma_inline const_iterator_type begin() const { return Q.begin(); }
  arma_inline const_iterator_type begin_col(const uword col_num) const {
    return Q.begin_col(col_num);
  }
  arma_inline const_row_iterator_type begin_row(const uword row_num = 0) const {
    return Q.begin_row(row_num);
  }

  arma_inline const_iterator_type end() const { return Q.end(); }
  arma_inline const_row_iterator_type end_row() const { return Q.end_row(); }
  arma_inline const_row_iterator_type end_row(const uword row_num) const {
    return Q.end_row(row_num);
  }

  template <typename eT2>
  arma_inline bool is_alias(const SpMat<eT2>& X) const {
    return (is_same_type<eT, eT2>::yes) && (void_ptr(&Q) == void_ptr(&X));
  }
};

template <typename eT>
struct SpProxy<SpSubview<eT> > {
  typedef eT elem_type;
  typedef typename get_pod_type<elem_type>::result pod_type;
  typedef SpSubview<eT> stored_type;

  typedef typename SpSubview<eT>::const_iterator const_iterator_type;
  typedef typename SpSubview<eT>::const_row_iterator const_row_iterator_type;

  static constexpr bool use_iterator = true;
  static constexpr bool Q_is_generated = false;

  static constexpr bool is_row = false;
  static constexpr bool is_col = false;
  static constexpr bool is_xvec = false;

  arma_aligned const SpSubview<eT>& Q;

  inline explicit SpProxy(const SpSubview<eT>& A) : Q(A) {
    arma_debug_sigprint();
    Q.m.sync();
  }

  arma_inline uword get_n_rows() const { return Q.n_rows; }
  arma_inline uword get_n_cols() const { return Q.n_cols; }
  arma_inline uword get_n_elem() const { return Q.n_elem; }
  arma_inline uword get_n_nonzero() const { return Q.n_nonzero; }

  arma_inline elem_type operator[](const uword i) const { return Q[i]; }
  arma_inline elem_type at(const uword row, const uword col) const {
    return Q.at(row, col);
  }

  arma_inline const eT* get_values() const { return Q.m.values; }
  arma_inline const uword* get_row_indices() const { return Q.m.row_indices; }
  arma_inline const uword* get_col_ptrs() const { return Q.m.col_ptrs; }

  arma_inline const_iterator_type begin() const { return Q.begin(); }
  arma_inline const_iterator_type begin_col(const uword col_num) const {
    return Q.begin_col(col_num);
  }
  arma_inline const_row_iterator_type begin_row(const uword row_num = 0) const {
    return Q.begin_row(row_num);
  }

  arma_inline const_iterator_type end() const { return Q.end(); }
  arma_inline const_row_iterator_type end_row() const { return Q.end_row(); }
  arma_inline const_row_iterator_type end_row(const uword row_num) const {
    return Q.end_row(row_num);
  }

  template <typename eT2>
  arma_inline bool is_alias(const SpMat<eT2>& X) const {
    return (is_same_type<eT, eT2>::yes) && (void_ptr(&Q.m) == void_ptr(&X));
  }
};

template <typename eT>
struct SpProxy<SpSubview_col<eT> > {
  typedef eT elem_type;
  typedef typename get_pod_type<elem_type>::result pod_type;
  typedef SpSubview_col<eT> stored_type;

  typedef typename SpSubview<eT>::const_iterator const_iterator_type;
  typedef typename SpSubview<eT>::const_row_iterator const_row_iterator_type;

  static constexpr bool use_iterator = true;
  static constexpr bool Q_is_generated = false;

  static constexpr bool is_row = false;
  static constexpr bool is_col = true;
  static constexpr bool is_xvec = false;

  arma_aligned const SpSubview_col<eT>& Q;

  inline explicit SpProxy(const SpSubview_col<eT>& A) : Q(A) {
    arma_debug_sigprint();
    Q.m.sync();
  }

  arma_inline uword get_n_rows() const { return Q.n_rows; }
  constexpr uword get_n_cols() const { return 1; }
  arma_inline uword get_n_elem() const { return Q.n_elem; }
  arma_inline uword get_n_nonzero() const { return Q.n_nonzero; }

  arma_inline elem_type operator[](const uword i) const { return Q.at(i, 0); }
  arma_inline elem_type at(const uword row, const uword) const { return Q.at(row, 0); }

  arma_inline const eT* get_values() const { return Q.m.values; }
  arma_inline const uword* get_row_indices() const { return Q.m.row_indices; }
  arma_inline const uword* get_col_ptrs() const { return Q.m.col_ptrs; }

  arma_inline const_iterator_type begin() const { return Q.begin(); }
  arma_inline const_iterator_type begin_col(const uword col_num) const {
    return Q.begin_col(col_num);
  }
  arma_inline const_row_iterator_type begin_row(const uword row_num = 0) const {
    return Q.begin_row(row_num);
  }

  arma_inline const_iterator_type end() const { return Q.end(); }
  arma_inline const_row_iterator_type end_row() const { return Q.end_row(); }
  arma_inline const_row_iterator_type end_row(const uword row_num) const {
    return Q.end_row(row_num);
  }

  template <typename eT2>
  arma_inline bool is_alias(const SpMat<eT2>& X) const {
    return (is_same_type<eT, eT2>::yes) && (void_ptr(&Q.m) == void_ptr(&X));
  }
};

template <typename eT, typename T1>
struct SpProxy<SpSubview_col_list<eT, T1> > {
  typedef eT elem_type;
  typedef typename get_pod_type<elem_type>::result pod_type;
  typedef SpMat<eT> stored_type;

  typedef typename SpMat<eT>::const_iterator const_iterator_type;
  typedef typename SpMat<eT>::const_row_iterator const_row_iterator_type;

  static constexpr bool use_iterator = false;
  static constexpr bool Q_is_generated = true;

  static constexpr bool is_row = false;
  static constexpr bool is_col = false;
  static constexpr bool is_xvec = false;

  arma_aligned const SpMat<eT> Q;

  inline explicit SpProxy(const SpSubview_col_list<eT, T1>& A) : Q(A) {
    arma_debug_sigprint();
  }

  arma_inline uword get_n_rows() const { return Q.n_rows; }
  arma_inline uword get_n_cols() const { return Q.n_cols; }
  arma_inline uword get_n_elem() const { return Q.n_elem; }
  arma_inline uword get_n_nonzero() const { return Q.n_nonzero; }

  arma_inline elem_type operator[](const uword i) const { return Q[i]; }
  arma_inline elem_type at(const uword row, const uword col) const {
    return Q.at(row, col);
  }

  arma_inline const eT* get_values() const { return Q.values; }
  arma_inline const uword* get_row_indices() const { return Q.row_indices; }
  arma_inline const uword* get_col_ptrs() const { return Q.col_ptrs; }

  arma_inline const_iterator_type begin() const { return Q.begin(); }
  arma_inline const_iterator_type begin_col(const uword col_num) const {
    return Q.begin_col(col_num);
  }
  arma_inline const_row_iterator_type begin_row(const uword row_num = 0) const {
    return Q.begin_row(row_num);
  }

  arma_inline const_iterator_type end() const { return Q.end(); }
  arma_inline const_row_iterator_type end_row() const { return Q.end_row(); }
  arma_inline const_row_iterator_type end_row(const uword row_num) const {
    return Q.end_row(row_num);
  }

  template <typename eT2>
  constexpr bool is_alias(const SpMat<eT2>&) const {
    return false;
  }
};

template <typename eT>
struct SpProxy<SpSubview_row<eT> > {
  typedef eT elem_type;
  typedef typename get_pod_type<elem_type>::result pod_type;
  typedef SpSubview_row<eT> stored_type;

  typedef typename SpSubview<eT>::const_iterator const_iterator_type;
  typedef typename SpSubview<eT>::const_row_iterator const_row_iterator_type;

  static constexpr bool use_iterator = true;
  static constexpr bool Q_is_generated = false;

  static constexpr bool is_row = true;
  static constexpr bool is_col = false;
  static constexpr bool is_xvec = false;

  arma_aligned const SpSubview_row<eT>& Q;

  inline explicit SpProxy(const SpSubview_row<eT>& A) : Q(A) {
    arma_debug_sigprint();
    Q.m.sync();
  }

  constexpr uword get_n_rows() const { return 1; }
  arma_inline uword get_n_cols() const { return Q.n_cols; }
  arma_inline uword get_n_elem() const { return Q.n_elem; }
  arma_inline uword get_n_nonzero() const { return Q.n_nonzero; }

  arma_inline elem_type operator[](const uword i) const { return Q.at(0, i); }
  arma_inline elem_type at(const uword, const uword col) const { return Q.at(0, col); }

  arma_inline const eT* get_values() const { return Q.m.values; }
  arma_inline const uword* get_row_indices() const { return Q.m.row_indices; }
  arma_inline const uword* get_col_ptrs() const { return Q.m.col_ptrs; }

  arma_inline const_iterator_type begin() const { return Q.begin(); }
  arma_inline const_iterator_type begin_col(const uword col_num) const {
    return Q.begin_col(col_num);
  }
  arma_inline const_row_iterator_type begin_row(const uword row_num = 0) const {
    return Q.begin_row(row_num);
  }

  arma_inline const_iterator_type end() const { return Q.end(); }
  arma_inline const_row_iterator_type end_row() const { return Q.end_row(); }
  arma_inline const_row_iterator_type end_row(const uword row_num) const {
    return Q.end_row(row_num);
  }

  template <typename eT2>
  arma_inline bool is_alias(const SpMat<eT2>& X) const {
    return (is_same_type<eT, eT2>::yes) && (void_ptr(&Q.m) == void_ptr(&X));
  }
};

template <typename eT>
struct SpProxy<spdiagview<eT> > {
  typedef eT elem_type;
  typedef typename get_pod_type<elem_type>::result pod_type;
  typedef SpMat<eT> stored_type;

  typedef typename SpMat<eT>::const_iterator const_iterator_type;
  typedef typename SpMat<eT>::const_row_iterator const_row_iterator_type;

  static constexpr bool use_iterator = false;
  static constexpr bool Q_is_generated = true;

  static constexpr bool is_row = false;
  static constexpr bool is_col = true;
  static constexpr bool is_xvec = false;

  arma_aligned const SpMat<eT> Q;

  inline explicit SpProxy(const spdiagview<eT>& A) : Q(A) { arma_debug_sigprint(); }

  arma_inline uword get_n_rows() const { return Q.n_rows; }
  constexpr uword get_n_cols() const { return 1; }
  arma_inline uword get_n_elem() const { return Q.n_elem; }
  arma_inline uword get_n_nonzero() const { return Q.n_nonzero; }

  arma_inline elem_type operator[](const uword i) const { return Q[i]; }
  arma_inline elem_type at(const uword row, const uword col) const {
    return Q.at(row, col);
  }

  arma_inline const eT* get_values() const { return Q.values; }
  arma_inline const uword* get_row_indices() const { return Q.row_indices; }
  arma_inline const uword* get_col_ptrs() const { return Q.col_ptrs; }

  arma_inline const_iterator_type begin() const { return Q.begin(); }
  arma_inline const_iterator_type begin_col(const uword col_num) const {
    return Q.begin_col(col_num);
  }
  arma_inline const_row_iterator_type begin_row(const uword row_num = 0) const {
    return Q.begin_row(row_num);
  }

  arma_inline const_iterator_type end() const { return Q.end(); }
  arma_inline const_row_iterator_type end_row() const { return Q.end_row(); }
  arma_inline const_row_iterator_type end_row(const uword row_num) const {
    return Q.end_row(row_num);
  }

  template <typename eT2>
  constexpr bool is_alias(const SpMat<eT2>&) const {
    return false;
  }
};

template <typename T1, typename spop_type>
struct SpProxy<SpOp<T1, spop_type> > {
  typedef typename T1::elem_type elem_type;
  typedef typename T1::elem_type eT;
  typedef typename get_pod_type<elem_type>::result pod_type;
  typedef SpMat<eT> stored_type;

  typedef typename SpMat<eT>::const_iterator const_iterator_type;
  typedef typename SpMat<eT>::const_row_iterator const_row_iterator_type;

  static constexpr bool use_iterator = false;
  static constexpr bool Q_is_generated = true;

  static constexpr bool is_row = SpOp<T1, spop_type>::is_row;
  static constexpr bool is_col = SpOp<T1, spop_type>::is_col;
  static constexpr bool is_xvec = SpOp<T1, spop_type>::is_xvec;

  arma_aligned const SpMat<eT> Q;

  inline explicit SpProxy(const SpOp<T1, spop_type>& A) : Q(A) { arma_debug_sigprint(); }

  arma_inline uword get_n_rows() const { return is_row ? 1 : Q.n_rows; }
  arma_inline uword get_n_cols() const { return is_col ? 1 : Q.n_cols; }
  arma_inline uword get_n_elem() const { return Q.n_elem; }
  arma_inline uword get_n_nonzero() const { return Q.n_nonzero; }

  arma_inline elem_type operator[](const uword i) const { return Q[i]; }
  arma_inline elem_type at(const uword row, const uword col) const {
    return Q.at(row, col);
  }

  arma_inline const eT* get_values() const { return Q.values; }
  arma_inline const uword* get_row_indices() const { return Q.row_indices; }
  arma_inline const uword* get_col_ptrs() const { return Q.col_ptrs; }

  arma_inline const_iterator_type begin() const { return Q.begin(); }
  arma_inline const_iterator_type begin_col(const uword col_num) const {
    return Q.begin_col(col_num);
  }
  arma_inline const_row_iterator_type begin_row(const uword row_num = 0) const {
    return Q.begin_row(row_num);
  }

  arma_inline const_iterator_type end() const { return Q.end(); }
  arma_inline const_row_iterator_type end_row() const { return Q.end_row(); }
  arma_inline const_row_iterator_type end_row(const uword row_num) const {
    return Q.end_row(row_num);
  }

  template <typename eT2>
  constexpr bool is_alias(const SpMat<eT2>&) const {
    return false;
  }
};

template <typename T1, typename T2, typename spglue_type>
struct SpProxy<SpGlue<T1, T2, spglue_type> > {
  typedef typename T1::elem_type elem_type;
  typedef typename T1::elem_type eT;
  typedef typename get_pod_type<elem_type>::result pod_type;
  typedef SpMat<eT> stored_type;

  typedef typename SpMat<eT>::const_iterator const_iterator_type;
  typedef typename SpMat<eT>::const_row_iterator const_row_iterator_type;

  static constexpr bool use_iterator = false;
  static constexpr bool Q_is_generated = true;

  static constexpr bool is_row = SpGlue<T1, T2, spglue_type>::is_row;
  static constexpr bool is_col = SpGlue<T1, T2, spglue_type>::is_col;
  static constexpr bool is_xvec = SpGlue<T1, T2, spglue_type>::is_xvec;

  arma_aligned const SpMat<eT> Q;

  inline explicit SpProxy(const SpGlue<T1, T2, spglue_type>& A) : Q(A) {
    arma_debug_sigprint();
  }

  arma_inline uword get_n_rows() const { return is_row ? 1 : Q.n_rows; }
  arma_inline uword get_n_cols() const { return is_col ? 1 : Q.n_cols; }
  arma_inline uword get_n_elem() const { return Q.n_elem; }
  arma_inline uword get_n_nonzero() const { return Q.n_nonzero; }

  arma_inline elem_type operator[](const uword i) const { return Q[i]; }
  arma_inline elem_type at(const uword row, const uword col) const {
    return Q.at(row, col);
  }

  arma_inline const eT* get_values() const { return Q.values; }
  arma_inline const uword* get_row_indices() const { return Q.row_indices; }
  arma_inline const uword* get_col_ptrs() const { return Q.col_ptrs; }

  arma_inline const_iterator_type begin() const { return Q.begin(); }
  arma_inline const_iterator_type begin_col(const uword col_num) const {
    return Q.begin_col(col_num);
  }
  arma_inline const_row_iterator_type begin_row(const uword row_num = 0) const {
    return Q.begin_row(row_num);
  }

  arma_inline const_iterator_type end() const { return Q.end(); }
  arma_inline const_row_iterator_type end_row() const { return Q.end_row(); }
  arma_inline const_row_iterator_type end_row(const uword row_num) const {
    return Q.end_row(row_num);
  }

  template <typename eT2>
  constexpr bool is_alias(const SpMat<eT2>&) const {
    return false;
  }
};

template <typename out_eT, typename T1, typename spop_type>
struct SpProxy<mtSpOp<out_eT, T1, spop_type> > {
  typedef out_eT elem_type;
  typedef typename get_pod_type<elem_type>::result pod_type;
  typedef SpMat<out_eT> stored_type;

  typedef typename SpMat<out_eT>::const_iterator const_iterator_type;
  typedef typename SpMat<out_eT>::const_row_iterator const_row_iterator_type;

  static constexpr bool use_iterator = false;
  static constexpr bool Q_is_generated = true;

  static constexpr bool is_row = mtSpOp<out_eT, T1, spop_type>::is_row;
  static constexpr bool is_col = mtSpOp<out_eT, T1, spop_type>::is_col;
  static constexpr bool is_xvec = mtSpOp<out_eT, T1, spop_type>::is_xvec;

  arma_aligned const SpMat<out_eT> Q;

  inline explicit SpProxy(const mtSpOp<out_eT, T1, spop_type>& A) : Q(A) {
    arma_debug_sigprint();
  }

  arma_inline uword get_n_rows() const { return is_row ? 1 : Q.n_rows; }
  arma_inline uword get_n_cols() const { return is_col ? 1 : Q.n_cols; }
  arma_inline uword get_n_elem() const { return Q.n_elem; }
  arma_inline uword get_n_nonzero() const { return Q.n_nonzero; }

  arma_inline elem_type operator[](const uword i) const { return Q[i]; }
  arma_inline elem_type at(const uword row, const uword col) const {
    return Q.at(row, col);
  }

  arma_inline const out_eT* get_values() const { return Q.values; }
  arma_inline const uword* get_row_indices() const { return Q.row_indices; }
  arma_inline const uword* get_col_ptrs() const { return Q.col_ptrs; }

  arma_inline const_iterator_type begin() const { return Q.begin(); }
  arma_inline const_iterator_type begin_col(const uword col_num) const {
    return Q.begin_col(col_num);
  }
  arma_inline const_row_iterator_type begin_row(const uword row_num = 0) const {
    return Q.begin_row(row_num);
  }

  arma_inline const_iterator_type end() const { return Q.end(); }
  arma_inline const_row_iterator_type end_row() const { return Q.end_row(); }
  arma_inline const_row_iterator_type end_row(const uword row_num) const {
    return Q.end_row(row_num);
  }

  template <typename eT2>
  constexpr bool is_alias(const SpMat<eT2>&) const {
    return false;
  }
};

template <typename out_eT, typename T1, typename T2, typename spglue_type>
struct SpProxy<mtSpGlue<out_eT, T1, T2, spglue_type> > {
  typedef out_eT elem_type;
  typedef typename get_pod_type<elem_type>::result pod_type;
  typedef SpMat<out_eT> stored_type;

  typedef typename SpMat<out_eT>::const_iterator const_iterator_type;
  typedef typename SpMat<out_eT>::const_row_iterator const_row_iterator_type;

  static constexpr bool use_iterator = false;
  static constexpr bool Q_is_generated = true;

  static constexpr bool is_row = mtSpGlue<out_eT, T1, T2, spglue_type>::is_row;
  static constexpr bool is_col = mtSpGlue<out_eT, T1, T2, spglue_type>::is_col;
  static constexpr bool is_xvec = mtSpGlue<out_eT, T1, T2, spglue_type>::is_xvec;

  arma_aligned const SpMat<out_eT> Q;

  inline explicit SpProxy(const mtSpGlue<out_eT, T1, T2, spglue_type>& A) : Q(A) {
    arma_debug_sigprint();
  }

  arma_inline uword get_n_rows() const { return is_row ? 1 : Q.n_rows; }
  arma_inline uword get_n_cols() const { return is_col ? 1 : Q.n_cols; }
  arma_inline uword get_n_elem() const { return Q.n_elem; }
  arma_inline uword get_n_nonzero() const { return Q.n_nonzero; }

  arma_inline elem_type operator[](const uword i) const { return Q[i]; }
  arma_inline elem_type at(const uword row, const uword col) const {
    return Q.at(row, col);
  }

  arma_inline const out_eT* get_values() const { return Q.values; }
  arma_inline const uword* get_row_indices() const { return Q.row_indices; }
  arma_inline const uword* get_col_ptrs() const { return Q.col_ptrs; }

  arma_inline const_iterator_type begin() const { return Q.begin(); }
  arma_inline const_iterator_type begin_col(const uword col_num) const {
    return Q.begin_col(col_num);
  }
  arma_inline const_row_iterator_type begin_row(const uword row_num = 0) const {
    return Q.begin_row(row_num);
  }

  arma_inline const_iterator_type end() const { return Q.end(); }
  arma_inline const_row_iterator_type end_row() const { return Q.end_row(); }
  arma_inline const_row_iterator_type end_row(const uword row_num) const {
    return Q.end_row(row_num);
  }

  template <typename eT2>
  constexpr bool is_alias(const SpMat<eT2>&) const {
    return false;
  }
};

template <typename out_eT, typename T1, typename op_type>
struct SpProxy<mtSpReduceOp<out_eT, T1, op_type> > {
  typedef out_eT elem_type;
  typedef typename get_pod_type<elem_type>::result pod_type;
  typedef SpMat<out_eT> stored_type;

  typedef typename SpMat<out_eT>::const_iterator const_iterator_type;
  typedef typename SpMat<out_eT>::const_row_iterator const_row_iterator_type;

  static constexpr bool use_iterator = false;
  static constexpr bool Q_is_generated = true;

  static constexpr bool is_row = mtSpReduceOp<out_eT, T1, op_type>::is_row;
  static constexpr bool is_col = mtSpReduceOp<out_eT, T1, op_type>::is_col;
  static constexpr bool is_xvec = mtSpReduceOp<out_eT, T1, op_type>::is_xvec;

  arma_aligned const SpMat<out_eT> Q;

  inline explicit SpProxy(const mtSpReduceOp<out_eT, T1, op_type>& A) : Q(A) {
    arma_debug_sigprint();
  }

  arma_inline uword get_n_rows() const { return is_row ? 1 : Q.n_rows; }
  arma_inline uword get_n_cols() const { return is_col ? 1 : Q.n_cols; }
  arma_inline uword get_n_elem() const { return Q.n_elem; }
  arma_inline uword get_n_nonzero() const { return Q.n_nonzero; }

  arma_inline elem_type operator[](const uword i) const { return Q[i]; }
  arma_inline elem_type at(const uword row, const uword col) const {
    return Q.at(row, col);
  }

  arma_inline const out_eT* get_values() const { return Q.values; }
  arma_inline const uword* get_row_indices() const { return Q.row_indices; }
  arma_inline const uword* get_col_ptrs() const { return Q.col_ptrs; }

  arma_inline const_iterator_type begin() const { return Q.begin(); }
  arma_inline const_iterator_type begin_col(const uword col_num) const {
    return Q.begin_col(col_num);
  }
  arma_inline const_row_iterator_type begin_row(const uword row_num = 0) const {
    return Q.begin_row(row_num);
  }

  arma_inline const_iterator_type end() const { return Q.end(); }
  arma_inline const_row_iterator_type end_row() const { return Q.end_row(); }
  arma_inline const_row_iterator_type end_row(const uword row_num) const {
    return Q.end_row(row_num);
  }

  template <typename eT2>
  constexpr bool is_alias(const SpMat<eT2>&) const {
    return false;
  }
};

//! @}
