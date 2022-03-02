#include <SFML/Graphics.hpp>

using namespace sf;

View view;

View GetPlayerCoordinateForView(float x, float y)
{
    float tempX = x; float tempY = y;
     
    if (x < 539) tempX = 539;
    if (y < 360) tempY = 360;
    if (x > 733) tempX = 733;

    view.setCenter(tempX, tempY);
    return view;
}
