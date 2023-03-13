#ifndef UKLADW_HH
#define UKLADW_HH

#include "Wektor.hh"
#include "Macierz.hh"

/**
 * @brief Implementation of coordinate system class
 */
class CoordSys{
private:
	Vector<3> center;
	Matrix<3> orientation;
    CoordSys* previous;	
public:
    /* constructor */
    CoordSys(Vector<3> _center, Matrix<3> _orientation, CoordSys* _previous): center(_center), orientation(_orientation), previous(_previous) {};
    /* get */
    /**
     * @brief get the center
     * 
     * @return center
     */
    Vector<3> getCenter() const;
    /**
     * @brief get the orientation
     * 
     * @return orientation 
     */
    Matrix<3> getOrientation() const;
    /**
     * @brief get the global center
     * 
     * @return global center 
     */
    Vector<3> getGlobalCenter() const;
    /**
     * @brief get the global coordinates
     * 
     * @return global coordinates 
     */
    Vector<2> getGlobalCoordinatesOfCenter() const;
    /**
     * @brief move center by given vector 
     * 
     * @param Vec vector to add
     */
    void translate(Vector<3> Vec);
    /**
     * @brief rotate orientation by given matrix
     * 
     * @param rotMatrix matrix to multiply
     */
    void rotate(Matrix<3> rotMatrix);
    /**
     * @brief convert point to parent coordination system
     * 
     * @param localPoint vector of point in coordination system
     * @return given point in parent coordination system
     */
    Vector<3> convertPointToParent(Vector<3> localPoint);
protected:
    CoordSys convertToGlobal() const;
};


#endif
