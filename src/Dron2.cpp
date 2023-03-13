#include "Dron2.hh"

Drone2::Drone2(std::shared_ptr<drawNS::Draw3DAPI> ptr_drawer, Vector<3> _center, Matrix<3> _orientation, CoordSys* _previous)
    : DrawingInterface(ptr_drawer), DroneInterface(), SceneElemInterface(), CoordSys(_center, _orientation, _previous),
    base({{0,0,0}}, {}, this, 10, 6, 2, drawer),
    rotors({{ { {{0, 0, 2}}, {}, this, 1.5, 4.5, drawer}, {{{-5, 0, 0}}, {90, {{0, 1, 0}}}, this, 1.5, 2, drawer} }}) 
{
    translate({{0, 0, base.getHeight() / 2.0}});
}

double Drone2::getLongestRadiusOfBase() const{
    return base.getLongerRadiusOfBase();
}

double Drone2::getLongestRadiusOfDrone() const{
    return base.getLongerRadiusOfBase() + rotors[0].getLongerRadiusOfBase();
}

double Drone2::getHeightOfBase() const{
    return base.getHeight();
}

double Drone2::getAltitudeOfBottomOfBase() const{
    return getGlobalCenter()[2] - getHeightOfBase() / 2;
}

void Drone2::draw(){    
    if(id == 1)
        erase();
    base.draw();
    for(Prism& rotor: rotors){
        rotor.draw();
    }
    id = 1;
}

void Drone2::erase(){
    for(Prism& rotor: rotors){
        rotor.erase();
    }    
    base.erase();
}

void Drone2::spinRotors(double fanSpeed){
    Matrix<3> Rot(fanSpeed, {{0, 0 ,1}});
    Matrix<3> RotMinus(-fanSpeed, {{0, 0 ,1}});
    rotors[0].rotate(Rot);
    rotors[1].rotate(RotMinus);
}

void Drone2::moveForward(double meters){
    Vector<3> temp({meters, 0, 0});
    temp = getOrientation() * temp;
    temp = rotateVectorToHorizontalPlane(temp);
    translate(temp);
}

void Drone2::moveNegativeYawAxis(double meters){
    translate({{0, 0, meters}});
}

void Drone2::rotateYawAxis(double angleInDegrees){
    Matrix<3> temp(angleInDegrees, {{0, 0, 1}});
    rotate(temp);
}

void Drone2::rotatePitchAxis(double angleInDegrees){
    Matrix<3> temp(angleInDegrees, {{0, 1, 0}});
    rotate(temp);
}

bool Drone2::isOver(std::shared_ptr<DroneInterface> drone){
    double distance = (getGlobalCoordinatesOfCenter() - drone->getDroneCoordinates()).length(); 
    if(distance < getLongestRadiusOfDrone() + drone->getLongestRadiusOfDrone())
        return 1;
    else
        return 0;
}

bool Drone2::canLand(std::shared_ptr<DroneInterface> drone, double & height){
    return 0;
}
