#ifndef HILL_HH
#define HILL_HH

#include "UkladW.hh"
#include "InterfejsRysowanie.hh"
#include "InterfejsElementuKrajobrazu.hh"
#include "Dron.hh"

#include <random>

/**
 * @brief Implementation of hill class
 */
class Hill: public DrawingInterface, public SceneElemInterface, public CoordSys{
    std::vector<Vector<3>> apex;
	double height;
    double longestRadius;
public:
    /**
     * @brief Construct a new Hill
     * 
     * @param ptr_drawer shared pointer to drawing API
     * @param _center of the hill relative to the '_previous' coordination system
     * @param _orientation of the hill relative to the '_previous' coordination system
     * @param _previous pointer to previous coordinate system
     * @param minSize minimum lenght of the plateau radius
     * @param maxSize maximum lenght of the plateau radius
     */
    Hill(std::shared_ptr<drawNS::Draw3DAPI> ptr_drawer, Vector<3> _center, Matrix<3> _orientation = {}, CoordSys* _previous = nullptr, int minSize = 3, int maxSize = 9);
    /**
     * @brief destroy and erase the Hill
     */
    ~Hill() {erase();}
    /* override getters */
    double getLongestRadiusOfBase() const override {return longestRadius;}
    std::string getName() const override {return "Wzgorze";}
    /* override methods */ 
    void draw() override;
    bool isOver(std::shared_ptr<DroneInterface> drone) override;   
};

#endif