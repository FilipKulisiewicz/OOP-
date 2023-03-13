#include "PlaskowyzProsty.hh"

Plateau::Plateau(std::shared_ptr<drawNS::Draw3DAPI> drawer, Vector<3> _center, Matrix<3> _orientation, CoordSys* _previous, double _length, double _width, double _height)
    : Cuboid(_center, _orientation,  _previous, _length, _width, _height, drawer), SceneElemInterface() 
{
    translate({{0, 0, height / 2.0}});
}

double Plateau::getLongestRadiusOfBase() const{
    return std::sqrt(std::pow(length, 2.0) + std::pow(width, 2.0)) / 2.0 ;
}

void Plateau::draw(){
    if(id == 0){
        CoordSys glob = convertToGlobal();
        Vector<3> temp[8] = { {{length/2, -width/2, height/2}},  {{length/2, width/2, height/2}},  {{-length/2, width/2, height/2}}, {{-length/2, -width/2, height/2}},
                            {{length/2, -width/2, -height/2}}, {{length/2, width/2, -height/2}}, {{-length/2, width/2, -height/2}}, {{-length/2, -width/2, -height/2}} };
        for(Vector<3>& Vec: temp){
            Vec =  glob.convertPointToParent(Vec);
        }
        std::vector<std::vector<drawNS::Point3D>> toDraw = {{ convertToPoint3D(temp[0]), convertToPoint3D(temp[1]), convertToPoint3D(temp[2]), convertToPoint3D(temp[3]) },
                                                            { convertToPoint3D(temp[4]), convertToPoint3D(temp[5]), convertToPoint3D(temp[6]), convertToPoint3D(temp[7]) }};
        id = drawer->draw_polyhedron(toDraw);
    }
}

bool Plateau::isOver(std::shared_ptr<DroneInterface> drone){
    double distance = (getGlobalCoordinatesOfCenter() - drone->getDroneCoordinates()).length(); 
    if(distance <  getLongestRadiusOfBase() + drone->getLongestRadiusOfDrone())
        return 1;
    else
        return 0;
}

bool Plateau::canLand(std::shared_ptr<DroneInterface> drone, double & _height){
    double distance = (getGlobalCoordinatesOfCenter() - drone->getDroneCoordinates()).length(); 
    if(distance <  getLongestRadiusOfBase() - drone->getLongestRadiusOfBase()){
        _height = height;
        return 1;
    }
    else
        return 0;
}
