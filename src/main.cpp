#include "Scena.hh"
#include "Dron.hh"
#include "Dron2.hh"
//#include "Dron3.hh"
#include "Powierzchnia.hh"
#include "Wzgorze.hh"
#include "PlaskowyzRand.hh"
#include "PlaskowyzProsty.hh"
#include "OpenGL_API.hh"

void printMenu();

int main(int argc, char** argv){
    std::shared_ptr<drawNS::Draw3DAPI> ptr_drawer = std::make_shared<drawNS::APIopenGL3D>(-35, 35, -35, 35, 0, 40, 0, &argc, argv);
    
    Scene scene;
    Surface ground(ptr_drawer);
    ground.draw();

    scene.addSceneElem(std::shared_ptr<SceneElemInterface>(new Hill(ptr_drawer, {{-20, -10, 0}}))); 
    scene.addSceneElem(std::shared_ptr<SceneElemInterface>(new Plateau(ptr_drawer, {{-20, 20, 0}}, {45, {{0, 0, 1}}}))); 
    scene.addSceneElem(std::shared_ptr<SceneElemInterface>(new PlateauRand(ptr_drawer, {{25, 0, 0}}))); 
    scene.drawAll();   
    
    scene.addDrone(std::shared_ptr<DroneInterface>(new Drone(ptr_drawer))); 
    scene.addDrone(std::shared_ptr<DroneInterface>(new Drone2(ptr_drawer, {{10, 25, 0}}, {-55, {{0, 0 ,1}}}))); 
    scene.addDrone(std::shared_ptr<DroneInterface>(new Drone(ptr_drawer, {{22, -22, 0}}, {45, {{0, 0 ,1}}}))); 
    
    //scene.addDrone(std::shared_ptr<DroneInterface>(new Drone3(ptr_drawer, {{20, 20, 0}}, {-30, {{0, 0 ,1}}})));
    //scene.addDrone(std::shared_ptr<DroneInterface>(new Drone2(ptr_drawer, {{30, -30, 0}}, {45, {{0, 0 ,1}}})));

    printMenu();
    char menu = '_';
    double angleInDegrees = 0;
    double traceLenght = 0;
    do{
        std::cout << "> ";
        std::cin >> menu;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        switch(menu){
            case 'a':{ 
                std::cout << "Wpisz ID drona (lista i) ktorego chcesz kontrolowac" << std::endl;
                uint tmp;
                std::cin >> tmp;
                scene.setCurrentDrone(tmp);
                break;
            }
            case 'p':{
                if(scene.getCurrentDrone() == nullptr){
                    std::cout << "Nie wybrano drona" << std::endl;
                    break;
                }
                std::cout << "Podaj kierunek lotu (kat w stopniach) oraz dlugosc lotu > ";
                std::cin >> angleInDegrees;
                if(std::cin.fail()){
                    std::cout << "! Blednie wprowadzono kat" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    break;
                }
                std::cin >> traceLenght; 
                if(std::cin.fail()){
                    std::cout << "! Blednie dlugosc lotu" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    break;
                }
                scene.animate(scene.getCurrentDrone(), angleInDegrees, traceLenght);
                break;
            }
            case 'm':{
                printMenu();
                break;
            }
            case 'd':{
                char tmp;
                std::cout << "Co chcesz dodac? d - drona; e - element krajobrazu" << std::endl;
                std::cin >> tmp;
                switch(tmp){
                    case 'd':{
                        scene.addDrone(std::shared_ptr<DroneInterface>(new Drone(ptr_drawer))); 
                        break;
                    }
                    case 'e':{
                        double x, y, angle;
                        std::cout << "Jaki element krajobrazu dodac? w - wzgorze, p - plaskowyz, r - plaskowyz zdegenerowany" << std::endl;
                        std::cin >> tmp;
                        std::cout << "podaj wspolrzedne 'x' i 'y' w ktorym ma znalesc sie ten obiekt oraz kat 'a' o jaki chcesz go obrocic" << std::endl;
                        std::cin >> x >> y >> angle;
                        switch(tmp){
                            case 'w':{
                                scene.addSceneElem(std::shared_ptr<SceneElemInterface>(new Hill(ptr_drawer, {{x, y, 0}}, {angle, {{0, 0, 1}}}))); 
                                break;
                            }
                            case 'p':{
                                scene.addSceneElem(std::shared_ptr<SceneElemInterface>(new Plateau(ptr_drawer, {{x, y, 0}}, {angle, {{0, 0, 1}}}))); 
                                break;
                            }
                            case 'r':{
                                scene.addSceneElem(std::shared_ptr<SceneElemInterface>(new PlateauRand(ptr_drawer, {{x, y, 0}}, {angle, {{0, 0, 1}}}))); 
                                break;
                            }
                            default:{
                                std::cout << "Blednie wybrana opcja - nie dodano zadnego elementu krajobrazu" << std::endl;
                                break; 
                            }
                        }
                        break;
                    }
                    default:{
                        std::cout << "Blednie wybrana opcja - nie dodano zadnego obiektu" << std::endl;
                        break; 
                    }
                }
                scene.drawAll();   
                break;
            }
            case 'u':{
                char tmp;
                std::cout << "Jaki element usunac? d - dron; e - element krajobrazu - dowolny" << std::endl;
                std::cin >> tmp;
                switch(tmp){
                    case 'd':{
                        std::cout << "Podaj ID drona (lista i) do usuniecia:" << std::endl;
                        uint idx = 0;
                        std::cin >> idx;
                        scene.deleteDrone(idx); 
                        break;
                    }
                    case 'e':{
                        std::cout << "Podaj ID elementu (lista j) do usuniecia:" << std::endl;
                        uint idx = 0;
                        std::cin >> idx;
                        scene.deleteSceneElem(idx); 
                        break;
                    }
                }
                break;
            }
            case 'i':{
                scene.showDronesId();
                break;
            }
            case 'j':{
                scene.showSceneElemsId();
                break;
            }
            case 'v':{
                std::cout << "Utworzono " << Vector<3>::getNumOfCreated() << " wektorow" << std::endl;
                std::cout << "Istnieje " << Vector<3>::getNumOfExisting() << " wektorow" << std::endl;
                break;
            }
            case 'k':{
                break;
            }
            default:
                std::cerr << "Nie ma takiej opcji w menu" << std::endl;
                break;
        }
    }while(menu != 'k'); 
}

void printMenu(){
    std::cout   <<  "a - wybierz aktywnego drona" << std::endl
                <<  "p - zadaj parametry przelotu" << std::endl
                <<  "m - wyswietl menu" << std::endl
                <<  "d - dodaj nowy element" << std::endl
                <<  "u - usun nowy element" << std::endl
                <<  "i - wyswietl ID dronow" << std::endl
                <<  "j - wyswietl ID wszystkich elementow sceny" << std::endl
                <<  "v - wyswietl ilosc wektorow" << std::endl
                <<  "k - koniec dzialania programu" << std::endl;
}