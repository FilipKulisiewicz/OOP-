#include "PlaskowyzRand.hh"

PlateauRand::PlateauRand(std::shared_ptr<drawNS::Draw3DAPI> ptr_drawer, Vector<3> _center, Matrix<3> _orientation, CoordSys* _previous, int minSize, int maxSize)
    : DrawingInterface(ptr_drawer), SceneElemInterface(), CoordSys(_center, _orientation, _previous), longestRadius(0){
    if(minSize > maxSize || minSize <= 0){
        std::cerr << "Proba stworzenia plaskowyza o blednych dlugosciach promieni" << std::endl ;
        exit(0);
    }
    std::random_device rand;
    std::default_random_engine generator(rand());
    std::uniform_int_distribution<int> distribut(4, 9);
    height = distribut(generator);
    
    std::uniform_int_distribution<int> distribution(minSize, maxSize);
    int numOfApexes = distribut(generator);
    Vector<3> temp;
    Matrix<3> rot;
    int randomNum = 0;
    for(int i = 0; i < numOfApexes; ++i){
        randomNum = distribution(generator);
        if(randomNum > longestRadius)
            longestRadius = randomNum;
        rot = {360.0 * i / numOfApexes, {{0, 0, 1}}};
        temp = {{(double)randomNum, 0, 0}};
        temp = rot * temp;
        apex.push_back(temp);
    }
}

void PlateauRand::draw(){
    if(id == 0){
        CoordSys glob = convertToGlobal();
        std::vector<drawNS::Point3D> Base;
        std::vector<drawNS::Point3D> Top;
        
        for(Vector<3> Vec: apex){
            Vec = glob.convertPointToParent(Vec);
            Base.push_back(convertToPoint3D(Vec));
        }
        Vector<3> vecHeight = {{0, 0, height}};
        for(Vector<3> Vec: apex){
            Vec = glob.convertPointToParent(Vec + vecHeight);
            Top.push_back(convertToPoint3D(Vec));
        }
    
        std::vector<std::vector<drawNS::Point3D>> toDraw;
        toDraw.push_back(Base);
        toDraw.push_back(Top);
        id = drawer->draw_polyhedron(toDraw);
    }
}

bool PlateauRand::isOver(std::shared_ptr<DroneInterface> drone){
    double distance = (getGlobalCoordinatesOfCenter() - drone->getDroneCoordinates()).length(); 
    if(distance <  getLongestRadiusOfBase() + drone->getLongestRadiusOfDrone())
        return 1;
    else
        return 0;
}

bool PlateauRand::canLand(std::shared_ptr<DroneInterface> drone, double & _height){
    double distance = (getGlobalCoordinatesOfCenter() - drone->getDroneCoordinates()).length(); 
    if(distance <  getLongestRadiusOfBase() - drone->getLongestRadiusOfBase()){
        _height = height;
        return 1;
    }
    else
        return 0;
}
