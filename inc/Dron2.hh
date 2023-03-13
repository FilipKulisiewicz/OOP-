#ifndef DRON2_HH
#define DRON2_HH

#include "Prostopadloscian.hh"
#include "Graniastoslup6.hh"
#include "InterfejsDrona.hh"
#include "InterfejsElementuKrajobrazu.hh"

#include <cmath>

/**
 * @brief Implementation of drone2 class
 */
class Drone2: public DrawingInterface, public DroneInterface, public SceneElemInterface, public CoordSys{
    Cuboid base;
    std::array<Prism, 2> rotors;
public:
    /**
     * @brief construct a new drone2
     * 
     * @param ptr_drawer shared pointer to drawing API
     * @param _center of the drone relative to the '_previous' coordination system
     * @param _orientation of the drone relative to the '_previous' coordination system
     * @param _previous pointer to previous coordinate system
     */
    Drone2(std::shared_ptr<drawNS::Draw3DAPI> ptr_drawer, Vector<3> _center = {}, Matrix<3> _orientation = {}, CoordSys* _previous = nullptr);
    /**
     * @brief destroy and erase the drone2  
     */
    ~Drone2() {erase();}
    /* override getters */
    double getLongestRadiusOfDrone() const override;
    double getLongestRadiusOfBase() const override;
    double getHeightOfBase() const override;
    double getAltitudeOfBottomOfBase() const override; 
    Vector<2> getDroneCoordinates() const override {return getGlobalCoordinatesOfCenter();};
    std::string getName() const override {return "Dron";}
    /* override methods */ 
    void draw() override;
    void erase() override;
    void spinRotors(double fanSpeed = 10) override;
    void moveForward(double meters) override;
    void moveNegativeYawAxis(double meters) override;
    void rotateYawAxis(double angleInDegrees) override;
    void rotatePitchAxis(double angleInDegrees) override;
    bool isOver(std::shared_ptr<DroneInterface> drone) override;
    bool canLand(std::shared_ptr<DroneInterface> drone, double & height) override;
};

#endif