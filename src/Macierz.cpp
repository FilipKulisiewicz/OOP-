#include "Macierz.hh"

template <int Size>
Matrix<Size>::Matrix(double AngleInDeg, Vector<Size> axis){
    if(Size < 0 || Size > 3){
        std::cerr << "Program nie obsluguje hiperobrotow";
        exit(0);
    }
}

template <>
Matrix<2>::Matrix(double AngleInDeg, Vector<2> axis){
    double AngleInRad = (AngleInDeg * M_PI)/ 180;
    Vector<2> top({cos(AngleInRad), -sin(AngleInRad)});
    Vector<2> bot({sin(AngleInRad), cos(AngleInRad)});
    this->rows[0] = top;
    this->rows[1] = bot;
}

template <>
Matrix<3>::Matrix(double AngleInDeg, Vector<3> axis){
    double AngleInRad = (AngleInDeg * M_PI)/ 180;
    axis = normalise(axis);
    Matrix<3> CroossProdOfAxis, Identity;
    CroossProdOfAxis.rows[0] = {{0.0, -axis[2], axis[1]}};
    CroossProdOfAxis.rows[1] = {{axis[2], 0.0, -axis[0]}};
    CroossProdOfAxis.rows[2] = {{-axis[1], axis[0], 0.0}};
    *this = Identity + CroossProdOfAxis * sin(AngleInRad) + CroossProdOfAxis * CroossProdOfAxis * (1 - cos(AngleInRad));
}

template <int Size>
Matrix<Size>::Matrix(){
    Vector<Size> temp;
    for(int i = 0; i < Size; ++i){
        temp[i] = 1;
        rows[i] = temp;
        temp[i] = 0;
    }
}

template <int Size>
const Vector<Size>& Matrix<Size>::operator[] (int idx) const{
    if(idx < 0 || idx >= Size){
        std::cerr << "Proba odwolania sie do nieistniejacego pola";
        exit(0);
    }
    return rows[idx];
}

template <int Size>
Matrix<Size> Matrix<Size>::operator+ (const Matrix<Size> & arg2) const{
    Matrix<Size> Result;
    for(int i = 0; i < Size; ++i){
        Result.rows[i] = rows[i] + arg2.rows[i];
    }
    return Result;
}

template <int Size>
Matrix<Size> Matrix<Size>::operator* (double arg2) const{
    Matrix<Size> Result;
    for(int i = 0; i < Size; ++i){
        Result.rows[i] = rows[i] * arg2;
    }
    return Result;
}

template <int Size>
Vector<Size> Matrix<Size>::operator* (const Vector<Size> & arg2) const{
    Vector<Size> Result;
    for(int i = 0; i < Size; ++i){
        for(int j = 0; j < Size; ++j){
            Result[i] += rows[i][j] * arg2[j];
        }
    }
    return Result;
}

template <int Size>
Matrix<Size> Matrix<Size>::operator* (const Matrix<Size> & arg2) const{
    Matrix<Size> Result;
    Vector<Size> Zero;
    for(int i = 0; i < Size; ++i){
        Result.rows[i] = Zero;
        for(int j = 0; j < Size; ++j){
            for(int k = 0; k < Size; ++k){
                Result.rows[i][j] += rows[i][k] * arg2[k][j];
            }
        }
    }
    return Result;
}

template <int Size>
std::ostream& operator << (std::ostream &Strm, const Matrix<Size> &Mx){
    for(int i = 0; i < Size; ++i){
        Strm << Mx[i] << ' ';
    }
    return Strm;
}


template class Matrix<2>;
template class Matrix<3>;
template std::ostream& operator << (std::ostream &Strm, const Matrix<2> &Mx);
template std::ostream& operator << (std::ostream &Strm, const Matrix<3> &Mx);