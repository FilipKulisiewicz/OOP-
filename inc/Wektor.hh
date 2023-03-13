#ifndef Vector_HH
#define Vector_HH

#include <iostream>
#include <array>
#include <cmath>

/**
 * @brief Implementation of vector class
 * 
 * @tparam Size of the vector (array) - dimensions of vector
 */
template <int Size>
class Vector{
private:
    std::array<double, Size> coordinates;
    inline static uint numberOfCreated = 0;
    inline static uint numberOfExisting = 0;
public:
    /**
     * @brief construct a new vector
     */
    Vector();
    /**
     * @brief construct a new vector
     * 
     * @param argArray array of numbers
     */
    Vector(std::array<double, Size> argArray): coordinates(argArray) {++numberOfCreated; ++numberOfExisting;}
    /**
     * @brief construct a new vector
     * 
     * @param Vec vector to copy
     */
    Vector(const Vector & Vec){coordinates = Vec.coordinates; ++numberOfCreated; ++numberOfExisting;}
    /**
     * @brief destroy the vector
     */
    ~Vector() {--numberOfExisting;}
    /**
     * @brief getter
     * 
     * @param idx index of number in array
     * @return number of given index form array
     */
    const double & operator[] (int idx) const;  
    /**
     * @brief setter
     * 
     * @param idx index of number in array
     * @return setted number
     */
    double & operator[] (int idx);
    /**
     * @brief get the number of created vectors
     * 
     * @return number of created vectors
     */
    static int getNumOfCreated() {return numberOfCreated;}
    /**
     * @brief get the number of currentlly existing vectors
     * 
     * @return number of currentlly existing vectors 
     */
    static int getNumOfExisting() {return numberOfExisting;} 
    /**
     * @brief addition operator
     * 
     * @param arg2 second argument of addition 
     * @return sum
     */
    Vector<Size> operator+ (const Vector<Size> & arg2) const;
    /**
     * @brief subraction operator
     * 
     * @param arg2 second argument of subraction 
     * @return difference
     */
    Vector<Size> operator- (const Vector<Size> & arg2) const;
    /**
     * @brief multiplication operator
     * 
     * @param arg2 second argument of multiplication
     * @return product 
     */
    Vector<Size> operator* (double arg2) const;
    /**
     * @brief cross product operator
     * 
     * @param arg2 second argument of multiplication
     * @return cross product 
     */
    double operator* (const Vector<Size> & arg2) const;
    /**
     * @brief addition operator
     * 
     * @param arg2 second argument of addition 
     * @return sum
     */
    Vector<Size> & operator+= (const Vector<Size> & arg2);
    /**
     * @brief calculate length of the vector
     * 
     * @return length of the vector 
     */
    double length() const;
};

/**
 * @brief convert vector to unit vectors 
 * 
 * @tparam Size of vector
 * @param Vec vector to convert
 * @return normalised vector 
 */
template <int Size>
Vector<Size> normalise(const Vector<Size> &Vec);

/**
 * @brief extract operator
 * 
 * @tparam Size of the vector
 * @param Strm stream
 * @param Vec vector to extract
 * @return given stream
 */
template <int Size>
std::istream& operator >> (std::istream &Strm, Vector<Size> &Vec);

/**
 * @brief insert operator
 * 
 * @tparam Size of the vector
 * @param Strm stream
 * @param Vec vector to insert
 * @return given stream
 */
template <int Size>
std::ostream& operator << (std::ostream &Strm, const Vector<Size> &Vec);

#endif
