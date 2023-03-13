#include "InterfejsDrona.hh"
#include "InterfejsElementuKrajobrazu.hh"
#include "InterfejsRysowanie.hh"
#include "Dron.hh"
#include "UkladW.hh"

#include <vector>
#include <algorithm>
#include <memory>
#include <thread>
#include <chrono>

/**
 * @brief Implementation of scene class
 */
class Scene{
protected:
    /**
     * @brief stack of pointers to all drones which are on the scene
     */
    std::vector<std::shared_ptr<DroneInterface>> drones;
    /**
     * @brief stack of pointers to all elements which are on the scene
     */
    std::vector<std::shared_ptr<SceneElemInterface>> sceneElems;
    /**
     * @brief stack of pointers to all drawabeale elements which are on the scene
     */
    std::vector<std::shared_ptr<DrawingInterface>> drawableElems;
    /**
     * @brief pointer to currently steared drone which is on the scene
     */
    std::shared_ptr<DroneInterface> currentDrone;
    
    /**
     * @brief animate initial entry of the drone into the scene
     * 
     * @param drone shared pointer to drone which flight is animated
     * @param height (negative) from which drone flies up [in metres]
     * @param velocity at which drone moves vertically [in metres/second]
     */
    void initialAnimation(std::shared_ptr<DroneInterface> drone, double height = 5.0, double velocity = 7.0);
public:
    /**
     * @brief get the poiter to current drone 
     * 
     * @return shared_ptr to interface pointing to currently chosen drone
     */
    std::shared_ptr<DroneInterface> getCurrentDrone() const;
    /**
     * @brief set current drone
     * 
     * @param id number of drone which is set as new current drone  
     */    
    void setCurrentDrone(uint id);
    /**
     * @brief animate flight of the drone,
     * take-off -> rotate -> fly forward -> look for the landong spot -> land   
     * 
     * @param drone shared pointer to drone which flight is animated
     * @param angleInDegrees by which the drone rotates after the take-off [in degrees]
     * @param traceLenght flown after which drone starts to look for a landing spot [in metres]
     * @param altitude at which drone flies horizontally [in metres]
     * @param velocity at which drone moves horizontally & vertically [in metres/second]
     * @param angularVelocity at which drone rotates [in degrees/second]
     */
    void animate(std::shared_ptr<DroneInterface> drone,  double angleInDegrees, double traceLenght, double altitude = 14, double velocity = 9.0, double angularVelocity = 100.0);
    /**
     * @brief print ID and position of all drones which are on the scene
     */
    void showDronesId() const;
    /**
     * @brief print ID and position of all elements which are on the scene
     */
    void showSceneElemsId() const;
    /**
     * @brief print ID and position of all drawable element which are on the scene
     */
    void showDrawableElemsId() const;
    /**
    * @brief draw all drawable scene elements
    */
    void drawAll();
    /**
     * @brief check if drone can (and on what height) land directly under its current cosition
     * 
     * @param drone shared pointer to drone which is trying to land
     * @param landingAltitude on which drone can land [in metres]
     * @return true if drone can land
     * @return false if drone can't land  
     */
    bool checkCollision(std::shared_ptr<DroneInterface> drone, double & landingAltitude);
    /**
     * @brief add element to scene
     * 
     * @param sceneElem shared pointer to element interface of element to add
     */
    void addSceneElem(std::shared_ptr<SceneElemInterface> sceneElem);
    /**
     * @brief delete element of the given number from the scene 
     * 
     * @param id number of element to delete
     */
    void deleteSceneElem(uint id);
    /**
     * @brief add drone to scene if landing is not occupied 
     * 
     * @param drone shared pointer to drone interface of drone to add
     */
    void addDrone(std::shared_ptr<DroneInterface> drone);
    /**
     * @brief delete drone of the given number from the scene 
     * 
     * @param id number of drone to delete
     */
    void deleteDrone(uint id);
};