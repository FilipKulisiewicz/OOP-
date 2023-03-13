#ifndef MACIERZ_HH
#define MACIERZ_HH

#include "Wektor.hh"
#include <iostream>
#include <cmath>

/**
 * @brief Implementation of matrix class
 * 
 * @tparam Size of matrix (array) - number of vectors of given Size
 */
template <int Size>
class Matrix{
private:
    std::array<Vector<Size>, Size> rows;
    Matrix<Size> operator+ (const Matrix<Size> & arg2) const;
    Matrix<Size> operator* (double arg2) const;  
public:
    /**
     * @brief construct a new matrix
     */
    Matrix();
    /**
     * @brief construct a new matrix
     * 
     * @param angleInDegree of rotation matrix
     * @param axis of rotation matrix
     */
    Matrix(double angleInDegree, Vector<Size> axis);
    /**
     * @brief getter
     * 
     * @param idx index of vector in array
     * @return vector of given index form array
     */
    const Vector<Size> & operator[] (int idx) const;
    /**
     * @brief multiplication operator
     * 
     * @param argVector second argument of multiplication
     * @return product
     */
    Vector<Size> operator* (const Vector<Size> & argVector) const;
    /**
     * @brief multiplication operator
     * 
     * @param argMatrix second argument of multiplication
     * @return product
     */
    Matrix<Size> operator* (const Matrix<Size> & argMatrix) const;
};
 
/**
 * @brief insert operator
 * 
 * @tparam Size of the matrix
 * @param Strm stream
 * @param Matrix to insert
 * @return given stream 
 */
template <int Size>
std::ostream& operator<< (std::ostream &Strm, const Matrix<Size> & Matrix);

#endif
