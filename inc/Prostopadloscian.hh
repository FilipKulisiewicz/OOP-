#ifndef PROSTOPADLOSCIAN_HH
#define PROSTOPADLOSCIAN_HH

#include "UkladW.hh"
#include "InterfejsRysowanie.hh"

/**
 * @brief Implementation of cuboid class
 */
class Cuboid: public DrawingInterface, public CoordSys{
protected:
    double length;	
	double width;
	double height;
public:
    /**
     * @brief Construct a new Cuboid 
     * 
     * @param _center of the prism relative to the '_previous' coordination system
     * @param _orientation of the prism relative to the '_previous' coordination system
     * @param _previous pointer to previous coordinate system
     * @param _length of the prism
     * @param _width of the prism
     * @param _height of the prism
     * @param ptr_drawer shared pointer to drawing API
     */
    Cuboid(Vector<3> _center, Matrix<3> _orientation, CoordSys* _previous, double _length, double _width, double _height, std::shared_ptr<drawNS::Draw3DAPI> ptr_drawer);
    /**
     * @brief get the height
     * 
     * @return height of cuboid 
     */
    double getHeight() const;
    /**
     * @brief get the longer radius of circumscribed circle constucded on cuboid base
     * 
     * @return lenght of longer radius of circumscribed circle constucded on cuboid base
     */
    double getLongerRadiusOfBase() const;
    /* override methods */ 
    void draw() override;
    
};

#endif
