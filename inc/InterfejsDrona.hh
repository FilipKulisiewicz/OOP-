#ifndef DRONEINTERFACE_HH
#define DRONEINTERFACE_HH

#include "Wektor.hh"
#include <memory>

/**
 * @brief Abstract interface for drone class
 */
class DroneInterface{
public:
    /**
     * @brief destroy the drone Interface object
     */
    virtual ~DroneInterface() {}
    /**
     * @brief get the drone coordinates
     * 
     * @return coordinates of the drones center
     */
    virtual double getLongestRadiusOfBase() const = 0;
    /**
     * @brief get the outer radius of the drone
     * 
     * @return outer radius of the drone
     */
    virtual double getLongestRadiusOfDrone() const = 0;
    /**
     * @brief get the height of base of the drone
     * 
     * @return height of base of the drone
     */
    virtual double getHeightOfBase() const = 0;
    /**
     * @brief get the altitude of bottom of base of the drone
     * 
     * @return altitude of bottom of base of the drone
     */
    virtual double getAltitudeOfBottomOfBase() const = 0;
    /**
     * @brief get the altitude of bottom of base of the drone
     * 
     * @return true if flyable
     * @return false if not flyable
     */
    virtual Vector<2> getDroneCoordinates() const = 0;
    /**
     * @brief get the radius of base of the drone
     * 
     * @return radius of base of the drone
     */
    virtual bool flyable() {return 1;}
    /**
     * @brief redraw the drone
     */
    virtual void draw() = 0;
    /**
     * @brief spin the rotors
     * 
     * @param fanSpeed anglee of which each rotor spins [in degrees]
     */
    virtual void spinRotors(double fanSpeed = 5) = 0;
    /**
     * @brief move the drone forward
     * 
     * @param metres length of which drone moves [in metres]
     */
    virtual void moveForward(double metres) = 0;
    /**
     * @brief move the drone up
     * 
     * @param metres length of which drone moves [in metres] 
     */
    virtual void moveNegativeYawAxis(double metres) = 0;
    /**
     * @brief rotate the drone horizontally (left/right)
     * 
     * @param angleInDegrees of which drone rotates [in degrees] 
     */
    virtual void rotateYawAxis(double angleInDegrees) = 0;
    /**
     * @brief rotate the drone vertically (nose up/down)
     * 
     * @param angleInDegrees of which drone rotates [in degrees]
     */
    virtual void rotatePitchAxis(double angleInDegrees) = 0;
};

/**
 * @brief rotate vector3D to horizontall plane
 * 
 * @param Vec vector to rotate
 * @return Vector<3> after rotation
 */
inline
Vector<3> rotateVectorToHorizontalPlane(Vector<3> Vec){
    double lengthPre = Vec.length();
    Vec[2] = 0;
    double lengthPost = Vec.length();
    return Vec * (lengthPre / lengthPost);
}

#endif