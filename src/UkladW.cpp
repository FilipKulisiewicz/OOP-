#include "UkladW.hh"

Vector<3> CoordSys::getCenter() const{
    return center;
}

Matrix<3> CoordSys::getOrientation() const{
    return orientation;
}

Vector<3> CoordSys::getGlobalCenter() const{
    return convertToGlobal().center;
}

Vector<2> CoordSys::getGlobalCoordinatesOfCenter() const{
    Vector<3> tmp = convertToGlobal().center;
    return {{tmp[0], tmp[1]}};
}

void CoordSys::translate(Vector<3> Vec){
    center += Vec;
}

void CoordSys::rotate(Matrix<3> rotMatrix){
    orientation = orientation * rotMatrix;
}

CoordSys CoordSys::convertToGlobal() const{
    CoordSys inGlobal = *this;
    while(inGlobal.previous != nullptr){
        inGlobal.center = inGlobal.previous->orientation * inGlobal.center + inGlobal.previous->center;
        inGlobal.orientation = inGlobal.previous->orientation * inGlobal.orientation;
        inGlobal.previous = inGlobal.previous->previous;
    }
    return inGlobal;
}

Vector<3> CoordSys::convertPointToParent(Vector<3> localPoint){
    return orientation * localPoint + center;

}