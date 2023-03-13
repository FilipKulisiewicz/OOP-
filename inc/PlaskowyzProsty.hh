#ifndef PLATEAU_HH
#define PLATEAU_HH

#include "Prostopadloscian.hh"
#include "InterfejsRysowanie.hh"
#include "InterfejsElementuKrajobrazu.hh"
#include "Dron.hh"
#include <algorithm>
#include <random>

/**
 * @brief Implementation of plateau class
 */
class Plateau: public Cuboid, public SceneElemInterface{
public:
    /**
     * @brief Construct a new Plateau object
     * 
     * @param ptr_drawer shared pointer to drawing API
     * @param _center of the plateau relative to the '_previous' coordination system
     * @param _orientation of the plateau relative to the '_previous' coordination system
     * @param _previous pointer to previous coordinate system
     * @param _length of the plateau
     * @param _width of the plateau
     * @param _height of the plateau
     */
    Plateau(std::shared_ptr<drawNS::Draw3DAPI> ptr_drawer, Vector<3> _center, Matrix<3> _orientation = {}, CoordSys* _previous = nullptr, double _length = 12, double _width = 9, double _height = 8);  
    /**
     * @brief destroy the Plateau 
     */
    ~Plateau() {erase();}
    /* override getters */
    double getLongestRadiusOfBase() const override;
    std::string getName() const override {return "Plaskowyz prosty";}
    /* override methods */ 
    void draw() override;
    bool isOver(std::shared_ptr<DroneInterface> drone) override;
    bool canLand(std::shared_ptr<DroneInterface> drone, double & height) override;

};

#endif
