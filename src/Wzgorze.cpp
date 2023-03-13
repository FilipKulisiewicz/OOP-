#include "Wzgorze.hh"

Hill::Hill(std::shared_ptr<drawNS::Draw3DAPI> ptr_drawer, Vector<3> _center, Matrix<3> _orientation, CoordSys* _previous, int minSize, int maxSize)
    : DrawingInterface(ptr_drawer), SceneElemInterface(), CoordSys(_center, _orientation, _previous), longestRadius(0){
    if(minSize > maxSize || minSize <= 0){
        std::cerr << "Proba stworzenia wzgorza o blednych dlugosciach promieni" << std::endl ;
        exit(0);
    }
    std::random_device rand;
    std::default_random_engine generator(rand());
    std::uniform_int_distribution<int> distribut(4, 9);
    int numOfApexes = distribut(generator);
    std::uniform_int_distribution<int> distribution(minSize, maxSize);
    int randomNum = 0;
    Vector<3> temp;
    Matrix<3> rot;
    for(int i = 0; i < numOfApexes; ++i){
        randomNum = distribution(generator);
        if(randomNum > longestRadius)
            longestRadius = randomNum;
        rot = {360.0 * i / numOfApexes, {{0, 0, 1}}};
        temp = {{(double)randomNum, 0, 0}};
        temp = rot * temp;
        apex.push_back(temp);
    }
    height = randomNum + 2;
}

void Hill::draw(){
    if(id == 0){
        CoordSys glob = convertToGlobal();
        std::vector<drawNS::Point3D> Base;
        std::vector<drawNS::Point3D> Top;
        
        for(Vector<3> Vec: apex){
            Vec =  glob.convertPointToParent(Vec);
            Base.push_back(convertToPoint3D(Vec));
        }
        Vector<3> temp = glob.convertPointToParent({{0, 0, height}});
        drawNS::Point3D summit = convertToPoint3D(temp);
        for(unsigned int i = 0; i < apex.size(); ++i){
            Top.push_back(summit);
        }

        std::vector<std::vector<drawNS::Point3D>> toDraw;
        toDraw.push_back(Base);
        toDraw.push_back(Top);
        id = drawer->draw_polyhedron(toDraw);
    }   
}

bool Hill::isOver(std::shared_ptr<DroneInterface> drone){
    double distance = (getGlobalCoordinatesOfCenter() - drone->getDroneCoordinates()).length(); 
    if(distance < getLongestRadiusOfBase() + drone->getLongestRadiusOfDrone())
        return 1;
    else
        return 0;
}