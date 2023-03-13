#include "Prostopadloscian.hh"

Cuboid::Cuboid(Vector<3> _center, Matrix<3> _orientation, CoordSys* _previous, double _length, double _width, double _height, std::shared_ptr<drawNS::Draw3DAPI> drawer)
    : DrawingInterface(drawer), CoordSys(_center, _orientation, _previous), length(_length), width(_width), height(_height) {}

void Cuboid::draw(){
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


double Cuboid::getHeight() const{
    return height;
}

double Cuboid::getLongerRadiusOfBase() const{
    return std::sqrt(std::pow(length, 2.0 ) + std::pow(width, 2.0)) / 2.0;
}