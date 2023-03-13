#ifndef DRON3_HH
#define DRON3_HH

#include "Prostopadloscian.hh"
#include "Graniastoslup6.hh"
#include "InterfejsDrona.hh"
#include "InterfejsElementuKrajobrazu.hh"

#include <cmath>

class Drone3: public DrawingInterface, public DroneInterface, public SceneElemInterface, public CoordSys{
    Cuboid base;
    std::array<Prism,4> rotors;
public:
    /* constructor */
    Drone3(std::shared_ptr<drawNS::Draw3DAPI> ptr_drawer, Vector<3> _center = {}, Matrix<3> _orientation = {}, CoordSys* _previous = nullptr);
    ~Drone3() {erase();}
    double getLongestRadiusOfDrone() const override;
    double getLongestRadiusOfBase() const override;
    double getHeightOfBase() const override;
    double getAltitudeOfBottomOfBase() const override; 
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