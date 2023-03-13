#include "Dron.hh"

Drone::Drone(std::shared_ptr<drawNS::Draw3DAPI> ptr_drawer, Vector<3> _center, Matrix<3> _orientation, CoordSys* _previous)
    : DrawingInterface(ptr_drawer), DroneInterface(), SceneElemInterface(), CoordSys(_center, _orientation, _previous),
    base({{0,0,0}}, {}, this, 10, 6, 2, drawer),
    rotors({{ { {{5, 3, 2}}, {}, this, 2, 2, drawer},  { {{5, -3, 2}}, {}, this, 2, 2, drawer},
              { {{-5, 3, 2}}, {}, this, 2, 2, drawer}, { {{-5, -3, 2}}, {}, this, 2, 2, drawer} }}) 
{
    translate({{0, 0, base.getHeight() / 2.0}});
}

double Drone::getLongestRadiusOfBase() const{
    return base.getLongerRadiusOfBase();
}

double Drone::getLongestRadiusOfDrone() const{
    return base.getLongerRadiusOfBase() + rotors[0].getLongerRadiusOfBase();
}

double Drone::getHeightOfBase() const{
    return base.getHeight();
}

double Drone::getAltitudeOfBottomOfBase() const{
    return getGlobalCenter()[2] - getHeightOfBase() / 2;
}

void Drone::draw(){    
    if(id == 1)
        erase();
    base.draw();
    for(Prism& rotor: rotors){
        rotor.draw();
    }
    id = 1;
}

void Drone::erase(){
    for(Prism& rotor: rotors){
        rotor.erase();
    }    
    base.erase();
}

void Drone::spinRotors(double fanSpeed){
    Matrix<3> Rot(fanSpeed, {{0, 0 ,1}});
    Matrix<3> RotMinus(-fanSpeed, {{0, 0 ,1}});
    rotors[0].rotate(Rot);
    rotors[1].rotate(RotMinus);
    rotors[2].rotate(Rot);
    rotors[3].rotate(RotMinus);
}

void Drone::moveForward(double meters){
    Vector<3> temp({meters, 0, 0});
    temp = getOrientation() * temp;
    temp = rotateVectorToHorizontalPlane(temp);
    translate(temp);
}

void Drone::moveNegativeYawAxis(double meters){
    translate({{0, 0, meters}});
}

void Drone::rotateYawAxis(double angleInDegrees){
    Matrix<3> temp(angleInDegrees, {{0, 0, 1}});
    rotate(temp);
}

void Drone::rotatePitchAxis(double angleInDegrees){
    Matrix<3> temp(angleInDegrees, {{0, 1, 0}});
    rotate(temp);
}

bool Drone::isOver(std::shared_ptr<DroneInterface> drone){
    double distance = (getGlobalCoordinatesOfCenter() - drone->getDroneCoordinates()).length(); 
    if(distance < getLongestRadiusOfDrone() + drone->getLongestRadiusOfDrone())
        return 1;
    else
        return 0;
}

bool Drone::canLand(std::shared_ptr<DroneInterface> drone, double & height){
    return 0;
}
