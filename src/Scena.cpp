#include "Scena.hh"



void Scene::initialAnimation(std::shared_ptr<DroneInterface> drone, double height, double velocity){
    if(drone->flyable()){
        drone->moveNegativeYawAxis(-height);
        const double fps = 30;
        const int milis = 1000 / fps;
        int frames = std::abs(height) * fps / velocity;
        for(int i = 0; i < frames; ++i){
            drone->moveNegativeYawAxis(velocity / fps);
            drone->spinRotors();
            drone->draw();
            std::this_thread::sleep_for(std::chrono::milliseconds(milis));
        }
    }
    else{
        double length = 10.0 * height;
        velocity *= 5.0;
        drone->moveForward(-length);
        const double fps = 30;
        const int milis = 1000 / fps;
        int frames = std::abs(length) * fps / velocity;
        for(int i = 0; i < frames; ++i){
            drone->moveForward(velocity / fps);
            drone->spinRotors();
            drone->draw();
            std::this_thread::sleep_for(std::chrono::milliseconds(milis));
        }
    }
}

std::shared_ptr<DroneInterface> Scene::getCurrentDrone() const {
    return currentDrone;
}

void Scene::setCurrentDrone(uint id){
    if(id < drones.size())
        currentDrone = drones[id];
    else
        std::cout << "Dron o takim indeksie nie istnieje" << std::endl;   
}

void Scene::animate(std::shared_ptr<DroneInterface> drone, double angleInDegrees, double traceLenght, double altitude, double velocity, double angularVelocity){
    const double fps = 40.0;
    const int milis = 1000.0 / fps;

    bool flyable = drone->flyable();
    if(!(drone->flyable())){
        std::cout << "Niestety ten pojazd nie ma jeszcze zamontowanego sterowania ;-;" << std::endl;
        return;
    }
    //TODO: altitude should be absolute not relative
    /* up */
    double upAltitude = altitude - drone->getAltitudeOfBottomOfBase();
    double frames = std::abs(upAltitude) * fps / velocity;
    for(int i = 0; i < frames; ++i){
        drone->moveNegativeYawAxis(velocity / fps);
        drone->spinRotors();
        drone->draw();
        std::this_thread::sleep_for(std::chrono::milliseconds(milis));
    }
    // rotation
    frames = std::abs(angleInDegrees) * fps / angularVelocity;
    for(int i = 0; i < frames; ++i){
        drone->rotateYawAxis(std::copysign(angularVelocity, angleInDegrees) / fps);
        drone->spinRotors(7);
        drone->draw();
        std::this_thread::sleep_for(std::chrono::milliseconds(milis));
    }
    // forward
    frames = std::abs(traceLenght) * fps / velocity;
    double num =  30.0 / frames;
    for(int i = 0; i < frames; ++i){
        if(i <= frames / 4.0 &&  std::abs(traceLenght) > 4 && flyable)
            drone->rotatePitchAxis(std::copysign(num, traceLenght));
        else if(i >= frames * 3.0 / 4.0 &&  std::abs(traceLenght) > 4 && flyable)
            drone->rotatePitchAxis(-(std::copysign(num, traceLenght)));
        drone->moveForward(std::copysign(velocity, traceLenght) / fps);
        drone->spinRotors();
        drone->draw();
        std::this_thread::sleep_for(std::chrono::milliseconds(milis));
    }
    // check collisions
    double landingAltitude = 0; 
    if(checkCollision(drone, landingAltitude)){
        std::cout << "Nie mozna wyladowac, rozpoczeto poszukiwanie bardziej odpowiedniego miejsca..." << std::endl ;
    }
    while(checkCollision(drone, landingAltitude)){ 
        drone->moveForward(std::copysign(velocity, traceLenght) / fps);
        drone->spinRotors();
        drone->draw();
        std::this_thread::sleep_for(std::chrono::milliseconds(milis));
    }
    // down
    std::cout << "Miejsce jest odpowiednie do ladowania, rozpoczeto obnizanie lotu" << std::endl;
    frames = std::abs(altitude - landingAltitude) * fps / velocity;
    for(int i = 0; i < frames; ++i){
        drone->moveNegativeYawAxis(-velocity / fps);
        drone->spinRotors();
        drone->draw();
        std::this_thread::sleep_for(std::chrono::milliseconds(milis));
    }
}

void Scene::drawAll(){
    for(std::shared_ptr<DrawingInterface> obj: drawableElems){
        obj->draw();
    }
}

bool Scene::checkCollision(std::shared_ptr<DroneInterface> drone, double & landingAltitude){
    for(unsigned long int i = 0; i < sceneElems.size(); ++i){
        if(sceneElems[i]->isOver(drone) && std::dynamic_pointer_cast<DroneInterface>(sceneElems[i]) != drone){
            if(!(sceneElems[i]->canLand(drone, landingAltitude))){
                landingAltitude = 0;
                return 1;
            }
        }
    }
    return 0;
}

void Scene::addSceneElem(std::shared_ptr<SceneElemInterface> sceneElem){
    sceneElems.push_back(sceneElem);
    drawableElems.push_back(std::dynamic_pointer_cast<DrawingInterface>(sceneElem));
}

void Scene::deleteSceneElem(uint id){
    if(id >= sceneElems.size()){
        std::cout << "proba usuniecia nieistnijacego elementu krajobrazu" << std::endl;
        return;
    }
    if(getCurrentDrone() != nullptr && std::dynamic_pointer_cast<DroneInterface>(sceneElems[id]) == getCurrentDrone()){
        std::cout << "usunieto aktualnie sterowanego drona" <<  std::endl;
        currentDrone = nullptr;
    }
    std::shared_ptr<SceneElemInterface> tmp = sceneElems[id];
    std::shared_ptr<DrawingInterface> tmp2 = std::dynamic_pointer_cast<DrawingInterface>(tmp);
    std::shared_ptr<DroneInterface> tmp3 = std::dynamic_pointer_cast<DroneInterface>(tmp);
    sceneElems.erase(std::remove(sceneElems.begin(), sceneElems.end(), tmp), sceneElems.end());
    drawableElems.erase(std::remove(drawableElems.begin(), drawableElems.end(), tmp2), drawableElems.end());
    drones.erase(std::remove(drones.begin(), drones.end(), tmp3), drones.end());
}

void Scene::addDrone(std::shared_ptr<DroneInterface> drone){    
    double buf;
    drones.push_back(drone);
    sceneElems.push_back(std::dynamic_pointer_cast<SceneElemInterface>(drones.back()));
    drawableElems.push_back(std::dynamic_pointer_cast<DrawingInterface>(drones.back()));
    if(drones.size() == 1)
        currentDrone = drones.back();
    if(checkCollision(drone, buf) == 0){
        initialAnimation(drone);
    }
    else{
        deleteDrone(drones.size() - 1);
        std::cout << "Miejsce poczatkowe jest zajete nie mozna dodac drona" << std::endl;
    }
}

void Scene::deleteDrone(uint id){
    if(id >= drones.size()){
        std::cout << "proba usuniecia nieistnijacego drona" << std::endl;
        return;
    }
    if(drones[id] == getCurrentDrone()){
        std::cout << "usunieto aktualnie sterowanego drona" <<  std::endl;
        currentDrone = nullptr;
    }
    std::shared_ptr<DroneInterface> tmp = drones[id];
    std::shared_ptr<DrawingInterface> tmp2 = std::dynamic_pointer_cast<DrawingInterface>(tmp);
    std::shared_ptr<SceneElemInterface> tmp3 = std::dynamic_pointer_cast<SceneElemInterface>(tmp);
    drones.erase(std::remove(drones.begin(), drones.end(), tmp), drones.end());
    drawableElems.erase(std::remove(drawableElems.begin(), drawableElems.end(), tmp2), drawableElems.end());
    sceneElems.erase(std::remove(sceneElems.begin(), sceneElems.end(), tmp3), sceneElems.end());
}

void Scene::showDronesId() const{
    if(drones.size() == 0){
        std::cout << "Brak dronow na scenie" << std::endl;
    }
    for(unsigned long int i = 0; i < drones.size(); ++i){
        std::cout << "id: " << i << "; Srodek: " << (std::dynamic_pointer_cast<CoordSys>(drones[i]))->getGlobalCoordinatesOfCenter();
        if(currentDrone == drones[i])
                std::cout << "(Aktywny)";
        std::cout << std::endl;
    }
}

void Scene::showSceneElemsId() const{
    if(sceneElems.size() == 0){
        std::cout << "Brak elementow na scenie" << std::endl;
    }
    for(unsigned long int i = 0; i < sceneElems.size(); ++i){
        std::cout << "id: " << i << "; Srodek: " << (std::dynamic_pointer_cast<CoordSys>(sceneElems[i]))->getCenter() << sceneElems[i]->getName() << std::endl;
    }
}

void Scene::showDrawableElemsId() const{
    for(unsigned long int i = 0; i < drawableElems.size(); ++i){
        std::cout << "id: " << i << "; Srodek: " << (std::dynamic_pointer_cast<CoordSys>(drawableElems[i]))->getCenter() << std::endl;
    }
}
