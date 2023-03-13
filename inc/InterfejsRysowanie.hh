#ifndef DRAWINGINTERFACE_HH
#define DRAWINGINTERFACE_HH

#include <memory>
#include "Wektor.hh"
#include "Draw3D_api_interface.hh"

/**
 * @brief Abstract interface for drawable element class
 */
class DrawingInterface{
protected:
   /**
    * @brief shared pointer to drawing API
    */
   std::shared_ptr<drawNS::Draw3DAPI> drawer;
   /**
    * @brief id of drawn object
    */
   uint id = 0;
public:
   /**
    * @brief construct a new Drawing Interface object
    * 
    * @param _drawer shared pointer to drawing API
    */
   DrawingInterface(std::shared_ptr<drawNS::Draw3DAPI> _drawer): drawer(_drawer) {}
   /**
    * @brief destroy the Drawing Interface object
    */
   virtual ~DrawingInterface() {}
   /**
    * @brief draw object
    */
   virtual void draw() = 0;
   /**
    * @brief erase object if drawn
    */
   virtual void erase(){if(id != 0) drawer->erase_shape(id);}
};

/**
 * @brief convert Vector3D to Point3D
 * 
 * @param Vec which is converted to point
 * @return Point3D made from Vector 
 */
inline
drawNS::Point3D convertToPoint3D(const Vector<3> Vec){
   return {Vec[0],Vec[1],Vec[2]};
}

#endif