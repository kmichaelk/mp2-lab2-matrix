// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#define TMATRIX_STR(x) #x
#define TMATRIX_EXPAND(x) TMATRIX_STR(x)

#include "tvector.h"

const int MAX_MATRIX_SIZE = 10000;

template<typename T>
using TDynamicMatrixBase = TDynamicVector<TDynamicVector<T>>;

// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : public TDynamicMatrixBase<T>
{
  using TDynamicMatrixBase<T>::pMem;
  using TDynamicMatrixBase<T>::sz;
private:
    template<typename Operation>
    static TDynamicMatrix apply_t(const TDynamicMatrix& m, const T& val, Operation op)
    {
        return apply_t_to(TDynamicMatrix<T>(m.sz), m, val, op);
    }
    template<typename Operation>
    static TDynamicMatrix apply(const TDynamicMatrix& m1, const TDynamicMatrix& m2, Operation op)
    {
        TDynamicMatrix<T> dst(m1.sz);
        apply_to(dst, m1, m2, op);
        return dst;
    }
public:
  explicit TDynamicMatrix(size_t size = 1)
    : TDynamicMatrixBase<T>(size, [size](size_t ind){ return TDynamicVector<T>(size); })
  {
      if (sz == 0 || sz > MAX_MATRIX_SIZE)
      {
          throw std::out_of_range("Vector size should be between 0 and " TMATRIX_EXPAND(MAX_MATRIX_SIZE));
      }
  }

  explicit TDynamicMatrix(const TDynamicMatrixBase<T> v)
    : TDynamicMatrixBase<T>(v)
  {}

  using TDynamicMatrixBase<T>::operator[];
  using TDynamicMatrixBase<T>::operator==;

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val) const
  {
      return apply_t(*this, val, std::multiplies<>{});
  }
  TDynamicMatrix operator*=(const T& val)
  {
      apply_t_to(*this, val, std::multiplies<>{});
      return *this;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v) const
  {
      if (sz != v.sz)
      {
          throw std::invalid_argument("Matrix columns count should be equal to the count of Vector rows");
      }

      TDynamicVector<T> result(sz);
      for (size_t row = 0; row < sz; row++)
      {
          for (size_t col = 0; col < sz; col++)
          {
              result[row] += (*this)[row][col] * v[row];
          }
      }
      return result;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m) const
  {
      req_eq_sz(*this, m);
      return apply(*this, m, std::plus<>{});
  }
  TDynamicMatrix operator+=(const TDynamicMatrix& m)
  {
      req_eq_sz(*this, m);
      apply_to(*this, m, std::plus<>{});
      return *this;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m) const
  {
      req_eq_sz(*this, m);
      return apply(*this, m, std::minus<>{});
  }
  TDynamicMatrix operator-=(const TDynamicMatrix& m)
  {
      req_eq_sz(*this, m);
      apply_to(*this, m, std::minus<>{});
      return *this;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m) const
  {
      req_eq_sz(*this, m);
      return apply(*this, m, std::multiplies<>{});
  }
  TDynamicMatrix operator*=(const TDynamicMatrix& m)
  {
      req_eq_sz(*this, m);
      apply_to(*this, m, std::multiplies<>{});
      return *this;
  }

  // ввод/вывод
  friend std::istream& operator>>(std::istream& istr, TDynamicMatrix& v)
  {
      const int size = v.sz * v.sz;
      for (size_t i = 0; i < size; i++)
      {
          istr >> v.pMem[i];
      }
  }
  friend std::ostream& operator<<(std::ostream& ostr, const TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz - 1; i++)
      {
          ostr << v.pMem[i];
          if (v.sz > 1)
              ostr << '\n';
      }
      if (v.sz > 1)
      {
          ostr << v.pMem[v.sz - 1];
      }
      return ostr;
  }
};

#undef TMATRIX_EXPAND
#undef TMATRIX_STR

#endif // __TMATRIX_H__
