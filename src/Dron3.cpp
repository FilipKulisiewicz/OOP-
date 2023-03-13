#include "Dron3.hh"

Drone3::Drone3(std::shared_ptr<drawNS::Draw3DAPI> ptr_drawer, Vector<3> _center, Matrix<3> _orientation, CoordSys* _previous)
    : DrawingInterface(ptr_drawer), DroneInterface(), SceneElemInterface(), CoordSys(_center, _orientation, _previous),
    base({{0,0,0}}, {}, this, 10, 6, 2, drawer),
    rotors({{ { {{5, 3, 1}}, {90, {{1, 0, 0}}}, this, 2, 2, drawer},  { {{5, -3, 1}}, {-90, {{1, 0, 0}}}, this, 2, 2, drawer},
              { {{-5, 3, 1}}, {90, {{1, 0, 0}}}, this, 2, 2, drawer}, { {{-5, -3, 1}}, {-90, {{1, 0, 0}}}, this, 2, 2, drawer} }}) 
{
    translate({{0, 0, base.getHeight() / 2.0}});
}

double Drone3::getLongestRadiusOfBase() const{
    return base.getLongerRadiusOfBase();
}

double Drone3::getLongestRadiusOfDrone() const{
    return base.getLongerRadiusOfBase() + rotors[0].getLongerRadiusOfBase();
}

double Drone3::getHeightOfBase() const{
    return base.getHeight();
}

double Drone3::getAltitudeOfBottomOfBase() const{
    return getGlobalCenter()[2] - getHeightOfBase() / 2;
}

void Drone3::draw(){    
    if(id == 1)
        erase();
    base.draw();
    for(Prism& rotor: rotors){
        rotor.draw();
    }
    id = 1;
}

void Drone3::erase(){
    for(Prism& rotor: rotors){
        rotor.erase();
    }    
    base.erase();
}

void Drone3::spinRotors(double fanSpeed){
    Matrix<3> Rot(fanSpeed, {{0, 0 ,1}});
    Matrix<3> RotMinus(-fanSpeed, {{0, 0 ,1}});
    rotors[0].rotate(Rot);
    rotors[1].rotate(RotMinus);
    rotors[2].rotate(Rot);
    rotors[3].rotate(RotMinus);
}

void Drone3::moveForward(double meters){
    Vector<3> temp({meters, 0, 0});
    temp = getOrientation() * temp;
    temp = rotateVectorToHorizontalPlane(temp);
    translate(temp);
}

void Drone3::moveNegativeYawAxis(double meters){
    translate({{0, 0, meters}});
}

void Drone3::rotateYawAxis(double angleInDegrees){
    Matrix<3> temp(angleInDegrees, {{0, 0, 1}});
    rotate(temp);
}

void Drone3::rotatePitchAxis(double angleInDegrees){
    Matrix<3> temp(angleInDegrees, {{0, 1, 0}});
    rotate(temp);
}

bool Drone3::isOver(std::shared_ptr<DroneInterface> drone){
    double distance = (getGlobalCoordinates() - std::static_pointer_cast<Drone3>(drone)->getGlobalCoordinates()).length(); 
    if(distance < getLongestRadiusOfDrone() + drone->getLongestRadiusOfDrone())
        return 1;
    else
        return 0;
}

bool Drone3::canLand(std::shared_ptr<DroneInterface> drone, double & height){
    return 0;
}
