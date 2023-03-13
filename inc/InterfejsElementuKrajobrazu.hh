#ifndef SCENEELEMINTERFACE_HH
#define SCENEELEMINTERFACE_HH

#include "InterfejsDrona.hh"

/**
 * @brief Abstract interface for scene element class
 */
class SceneElemInterface{
public:
    /**
     * @brief destroy the scene element Interface object
     */
    virtual ~SceneElemInterface() {}
    /**
     * @brief get the longest radius of circumscribed circle constucded on base
     * 
     * @return leanght of the longest radius of circumscribed circle constucded on base
     */
    virtual double getLongestRadiusOfBase() const = 0;
    /**
     * @brief check if the drone is over this element 
     * 
     * @param drone which check if is over
     * @return true if the drone is over it
     * @return false if the drone is not over it
     */
    virtual bool isOver(std::shared_ptr<DroneInterface> drone) = 0;
    /**
     * @brief check if the drone can land on this element
     * 
     * @param drone which check if it can land
     * @param height on which can land
     * @return true if the drone can land
     * @return false if the drone can not land
     */
    virtual bool canLand(std::shared_ptr<DroneInterface> drone, double & height) {return 0;};
    /**
     * @brief get the name object
     * 
     * @return name of element 
     */
    virtual std::string getName() const = 0;
};

#endif