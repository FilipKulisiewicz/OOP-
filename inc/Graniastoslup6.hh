#ifndef GRANAISTOSLUP_HH
#define GRANAISTOSLUP_HH

#include "UkladW.hh"
#include "InterfejsRysowanie.hh"

/**
 * @brief Implementation of prism class
 */
class Prism: public DrawingInterface, public CoordSys{
	double height;
    double longerRadius;
public:
    /**
     * @brief construct a new Prism
     * 
     * @param _center of the prism relative to the '_previous' coordination system
     * @param _orientation of the prism relative to the '_previous' coordination system
     * @param _previous pointer to previous coordinate system
     * @param _height of the prism
     * @param _longerRadius of the prism
     * @param ptr_drawer shared pointer to drawing API
     */
    Prism(Vector<3> _center, Matrix<3> _orientation, CoordSys* _previous, double _height, double _longerRadius, std::shared_ptr<drawNS::Draw3DAPI> ptr_drawer);
    /**
     * @brief get the longer radius of circumscribed circle constucded on prisms base 
     * 
     * @return lenght of longer radius of circumscribed circle constucded on prisms base
     */
    double getLongerRadiusOfBase() const;
    /* override methods */
    void draw() override;
};

#endif