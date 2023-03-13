#include "Wektor.hh"

template<int Size>
Vector<Size>::Vector(){
    for(int i = 0; i < Size; ++i){
        coordinates[i] = 0;
    }
    ++numberOfExisting; 
    ++numberOfCreated;
}

template<int Size>
const double & Vector<Size>::operator[] (int idx) const{
    if(idx < 0 || idx >= Size){
        std::cerr << "Proba odwolania sie do nieistniejacego pola";
        exit(0);
    }
    return coordinates[idx];
}

template<int Size>
double & Vector<Size>::operator[] (int idx){
    if(idx < 0 || idx >= Size){
        std::cerr << "Proba odwolania sie do nieistniejacego pola";
        exit(0);
    }
    return coordinates[idx];
}

template<int Size>
Vector<Size> Vector<Size>::operator+ (const Vector<Size> & arg2) const{
    Vector<Size> Result = *this;
    for(int i = 0; i < Size; ++i){
        Result.coordinates[i] += arg2.coordinates[i];
    }
    return Result;
}

template<int Size>
Vector<Size> Vector<Size>::operator- (const Vector<Size> & arg2) const{
    Vector<Size> Result = *this;
    for(int i = 0; i < Size; ++i){
        Result.coordinates[i] -= arg2.coordinates[i];
    }
    return Result;
}

template<int Size>
Vector<Size> Vector<Size>::operator* (double arg2) const{
    Vector<Size> Result = *this;
    for(double& coord: Result.coordinates){
        coord *= arg2;
    }
    return Result;
}

template<int Size>
double Vector<Size>::operator* (const Vector<Size> & arg2) const{
    double Result = 0;
    for(int i = 0; i < Size; ++i){
        Result +=  coordinates[i] * arg2.coordinates[i];
    }
    return Result;
}

template<int Size>
Vector<Size> & Vector<Size>::operator+= (const Vector<Size> & arg2){
    for(int i = 0; i < Size; ++i){
        coordinates[i] += arg2.coordinates[i];
    }
    return *this;
}

template<int Size>
double Vector<Size>::length() const{
    double Result = 0;
    for(double coord: coordinates){
        Result += std::pow(coord, 2);
    }
    return std::pow(Result, 1.0 / 2.0);
}

template<int Size>
std::istream& operator >> (std::istream &Stream, Vector<Size> &Vec){
    for(int i = 0; i < Size; ++i){
        Stream >> Vec[i];
    }
    return Stream;
}

template<int Size>
std::ostream& operator << (std::ostream &Stream, const Vector<Size> &Vec){
    for(int i = 0; i < Size; ++i){
        Stream << std::fixed << Vec[i] << ' ';
    }
    Stream << ' ';
    return Stream;
}

template <int Size>
Vector<Size> normalise(const Vector<Size> & Vec){
    Vector<Size> Result;
    double length = 0;
    for(int i = 0; i < Size; ++i){
        length += Vec[i] * Vec[i];
    }
    length = pow(length, (1.0 / 2.0));
    Result = Vec * (1.0 / length);
    return Result;
}

template class Vector<2>;
template class Vector<3>;
template class Vector<6>;
template Vector<3> normalise(const Vector<3> & Vec);
template std::istream& operator >> (std::istream &Strm, Vector<2> &Wek);
template std::ostream& operator << (std::ostream &Strm, const Vector<2> &Wek);
template std::istream& operator >> (std::istream &Strm, Vector<3> &Wek);
template std::ostream& operator << (std::ostream &Strm, const Vector<3> &Wek);
template std::istream& operator >> (std::istream &Strm, Vector<6> &Wek);
template std::ostream& operator << (std::ostream &Strm, const Vector<6> &Wek);