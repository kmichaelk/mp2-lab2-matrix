// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TVECTOR_H__
#define __TVECTOR_H__

#define TVECTOR_STR(x) #x
#define TVECTOR_EXPAND(x) TVECTOR_STR(x)

#include <iostream>
#include <functional>

const int MAX_VECTOR_SIZE = 100000000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
    size_t sz;
    T* pMem;

    friend void req_eq_sz(const TDynamicVector& v1, const TDynamicVector& v2)
    {
        if (v1.sz != v2.sz)
            throw std::invalid_argument("Vectors have different sizes");
    }

    template<typename Operation>
    static TDynamicVector apply_t(const TDynamicVector& v, const T& val, Operation op)
    {
        TDynamicVector<T> res(v.sz);
        apply_t_to(res, v, val, op);
        return res;
    }
    template<typename Operation>
    static void apply_t_to(TDynamicVector& v, const T& val, Operation op)
    {
        apply_to(v, v, val, op);
    }
    template<typename Operation>
    static void apply_t_to(TDynamicVector& dst, const TDynamicVector& v, const T& val, Operation op)
    {
        for (size_t i = 0; i < dst.sz; i++)
        {
            dst[i] = op(v[i], val);
        }
    }
    //
    template<typename Operation>
    static TDynamicVector apply(const TDynamicVector& v1, const TDynamicVector& v2, Operation op)
    {
        TDynamicVector<T> res(v1.sz);
        apply_to(res, v1, v2, op);
        return res;
    }
    template<typename Operation>
    static void apply_to(TDynamicVector& v, const TDynamicVector& v_val, Operation op)
    {
        apply_to(v, v, v_val, op);
    }
    template<typename Operation>
    static void apply_to(TDynamicVector& dst, const TDynamicVector& v, const TDynamicVector& v_val, Operation op)
    {
        for (size_t i = 0; i < dst.sz; i++)
        {
            dst[i] += op(v[i], v_val[i]);
        }
    }
public:
    typedef std::function<T (size_t)> TDynamicVectorAllocatorFunction;

    explicit TDynamicVector(size_t size = 1, TDynamicVectorAllocatorFunction fnAlloc = nullptr)
        : sz(size)
    {
        if (sz == 0 || sz > MAX_VECTOR_SIZE)
        {
            throw std::out_of_range("Vector size should be between 0 and " TVECTOR_EXPAND(MAX_VECTOR_SIZE));
        }

        pMem = fnAlloc ? new T[sz] : new T[sz]();
        if (fnAlloc)
        {
            for (size_t i = 0; i < sz; i++)
            {
                pMem[i] = fnAlloc(i);
            }
        }
    }
    TDynamicVector(T* arr, size_t size)
        : sz(size)
    {
        assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");

        pMem = new T[sz];
        std::copy(arr, arr + sz, pMem);
    }
    TDynamicVector(const TDynamicVector& v)
        : sz(v.sz)
        , pMem(new T[sz])
    {
        std::copy(v.pMem, v.pMem + sz, pMem);
    }
    TDynamicVector(TDynamicVector&& v) noexcept
        : pMem(nullptr)
    {
        swap(*this, v);
    }

    ~TDynamicVector()
    {
        delete[] pMem;
    }

    TDynamicVector& operator=(const TDynamicVector& v)
    {
        if (this == &v)
        {
            return *this;
        }

        TDynamicVector<T> tmp(v);
        swap(*this, tmp);
        return *this;
    }
    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
        swap(*this, v);
        return *this;
    }

    size_t size() const noexcept
    {
        return sz;
    }

    // индексация
    T& operator[](size_t ind)
    {
        return const_cast<T&>(std::as_const(*this)[ind]);
    }
    const T& operator[](size_t ind) const
    {
        return pMem[ind];
    }
    // индексация с контролем
    T& at(size_t ind)
    {
        return const_cast<T&>(std::as_const(*this).at(ind));
    }
    const T& at(size_t ind) const
    {
        if (ind >= sz)
        {
            throw std::out_of_range("Index is out of range");
        }
        return pMem[ind];
    }

    // сравнение
    bool operator==(const TDynamicVector& v) const noexcept
    {
        if (sz != v.sz)
        {
            return false;
        }
        for (size_t i = 0; i < sz; i++)
        {
            if ((*this)[i] != v[i])
            {
                return false;
            }
        }
        return true;
    }
    bool operator!=(const TDynamicVector& v) const noexcept
    {
        return !(*this == v);
    }

    // скалярные операции
    TDynamicVector operator+(const T val) const
    {
        return apply_t(*this, val, std::plus<>{});
    }
    TDynamicVector& operator+=(const T val)
    {
        apply_t_to(*this, val, std::plus<>{});
        return *this;
    }
    TDynamicVector operator-(const T val) const
    {
        //return *this + (-val);
        return apply_t(*this, val, std::minus<>{});
    }
    TDynamicVector& operator-=(const T val)
    {
        apply_t_to(*this, val, std::minus<>{});
        return *this;
    }
    TDynamicVector operator*(const T val) const
    {
        return apply_t(*this, val, std::multiplies<>{});
    }
    TDynamicVector& operator*=(const T val)
    {
        apply_t_to(*this, val, std::multiplies<>{});
        return *this;
    }

    // векторные операции
    TDynamicVector operator+(const TDynamicVector& v) const
    {
        req_eq_sz(*this, v);
        return apply(*this, v, std::plus<>{});
    }
    TDynamicVector operator+=(const TDynamicVector& v)
    {
        req_eq_sz(*this, v);
        apply_to(*this, v, std::plus<>{});
        return *this;
    }
    TDynamicVector operator-(const TDynamicVector& v) const
    {
        //return *this + (-v);
        req_eq_sz(*this, v);
        return apply(*this, v, std::minus<>{});
    }
    TDynamicVector operator-=(const TDynamicVector& v)
    {
        req_eq_sz(*this, v);
        apply_to(*this, v, std::minus<>{});
        return *this;
    }
    T operator*(const TDynamicVector& v) const
    {
        req_eq_sz(*this, v);

        T result{};
        for (size_t i = 0; i < v.sz; i++)
        {
            result += (*this)[i] * v[i];
        }
        return result;
    }

    TDynamicVector operator-() const
    {
        return apply(*this, -1, std::multiplies<>());
    }

    friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
    {
        std::swap(lhs.sz, rhs.sz);
        std::swap(lhs.pMem, rhs.pMem);
    }

    // ввод/вывод
    friend std::istream& operator>>(std::istream& istr, TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
        {
            istr >> v.pMem[i]; // требуется оператор>> для типа T
        }
        return istr;
    }
    friend std::ostream& operator<<(std::ostream& ostr, const TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
        {
            ostr << v.pMem[i];
            if (i < (v.sz - 1))
                ostr << ' ';
        }
        return ostr;
    }
};

#undef TVECTOR_EXPAND
#undef TVECTOR_STR

#endif // __TVECTOR_H__
