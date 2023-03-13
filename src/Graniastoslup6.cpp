#include "Graniastoslup6.hh"

Prism::Prism(Vector<3> _center, Matrix<3> _orientation, CoordSys* _previous, double _height, double _longerRadius, std::shared_ptr<drawNS::Draw3DAPI> drawer):
    DrawingInterface(drawer), CoordSys(_center, _orientation, _previous), height(_height), longerRadius(_longerRadius) {}

double Prism::getLongerRadiusOfBase() const{
    return longerRadius;
}

void Prism::draw(){
    Vector<3> temp[12] = {{{longerRadius * cos(0), longerRadius * sin(0), height / 2}},       {{longerRadius * cos(M_PI / 3), longerRadius * sin(M_PI / 3), height / 2}},         {{longerRadius * cos(2 * M_PI / 3), longerRadius * sin(2 * M_PI / 3), height / 2}},
                          {{longerRadius * cos(M_PI), longerRadius * sin(M_PI), height / 2}}, {{longerRadius * cos(4 * M_PI / 3), longerRadius * sin(4 * M_PI / 3), height / 2}}, {{longerRadius * cos(5 * M_PI / 3), longerRadius * sin(5 * M_PI / 3), height / 2}},
                          {{longerRadius * cos(0), longerRadius * sin(0), -height / 2}},       {{longerRadius * cos(M_PI / 3), longerRadius * sin(M_PI / 3), -height / 2}},         {{longerRadius * cos(2 * M_PI / 3), longerRadius * sin(2 * M_PI / 3), -height / 2}},
                          {{longerRadius * cos(M_PI), longerRadius * sin(M_PI), -height / 2}}, {{longerRadius * cos(4 * M_PI / 3), longerRadius * sin(4 * M_PI / 3), -height / 2}}, {{longerRadius * cos(5 * M_PI / 3), longerRadius * sin(5 * M_PI / 3), -height / 2}} };
    
    CoordSys glob = convertToGlobal();
    for(Vector<3>& Vec: temp){
        Vec = glob.convertPointToParent(Vec);
    }
    std::vector<std::vector<drawNS::Point3D>> toDraw = {{convertToPoint3D(temp[0]), convertToPoint3D(temp[1]), convertToPoint3D(temp[2]),
                                                         convertToPoint3D(temp[3]), convertToPoint3D(temp[4]), convertToPoint3D(temp[5])},
                                                        {convertToPoint3D(temp[6]), convertToPoint3D(temp[7]), convertToPoint3D(temp[8]),
                                                         convertToPoint3D(temp[9]), convertToPoint3D(temp[10]), convertToPoint3D(temp[11])} };
    id = drawer->draw_polyhedron(toDraw);
}