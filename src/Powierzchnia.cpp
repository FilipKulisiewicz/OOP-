#include "Powierzchnia.hh"

void Surface::draw(){
    for(double i = -size; i <= size; ++i){
        for(double j = -size; j <= size; ++j){
            drawer->draw_surface({{ {i * 10 - 5, j * 10 - 5, height}, {i * 10 - 5, (j + 1) * 10 - 5, height} }, { {(i + 1) * 10 - 5, j * 10 - 5, height}, {(i + 1) * 10 - 5, (j + 1) * 10 - 5, height} }});
        }
    }
    /* H */
    drawer->draw_polygonal_chain({{ {3, 3, 0}, {-3, 3, 0}, {-3, 1, 0}, {-1, 1, 0}, {-1, -1, 0}, {-3, -1, 0}, {-3, -3, 0}, {3, -3, 0}, {3, -1, 0}, {1, -1, 0}, {1, 1, 0}, {3, 1, 0}, {3, 3, 0} }});
    id = 999;
}