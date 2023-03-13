#ifndef SURFACE_HH
#define SURFACE_HH

#include "InterfejsRysowanie.hh"

/**
 * @brief Implementation of surface class
 */
class Surface: public DrawingInterface{
    int size;
    double height;
public:
    /**
     * @brief construct a new surface with 'H' sign in center
     * 
     * @param drawer shared pointer to drawing API
     * @param _size number of rows of tiles drawn in each direction
     * @param _height on which surface is drawn on scene 
     */
    Surface(std::shared_ptr<drawNS::Draw3DAPI> drawer, int _size = 3, double _height = 0): DrawingInterface(drawer), size(_size), height(_height) {};
    /* override methods */
    void draw() override;
};

#endif