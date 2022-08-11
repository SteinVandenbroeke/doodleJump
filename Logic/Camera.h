//
// Created by stein on 18/11/2021.
//

#ifndef TESTREPO_CAMERA_H
#define TESTREPO_CAMERA_H
#include "Stopwatch.h"
#include <memory>

class EntityLogic;
class Camera {
    int height = 0;
    std::shared_ptr<Stopwatch> stopwatch = stopwatch->getInstance();
    int screenHeight = 0;
    int screenWidth = 0;
public:
    /***
     * Creates a new camera view
     * @param screenWidth
     * @param screenHeight
     */
    Camera(int screenWidth, int screenHeight);

    /***
     * Converts a logic coordinate to a representative pixel
     * @param coordinate
     * @param entity
     * @return
     */
    std::pair<float, float> coordinateToPixel(const std::pair<float,float>& coordinate, const EntityLogic& entity) const;

    /***
     * Converts a logic y coordinate to the y location of a pixel
     * @param y
     * @return the pixel location of that y coordinate
     */
    float yCoordinateToPixel(float y) const;

    /***
     * Add height to the camera (player goes up)
     * @param height
     */
    void addToHeight(unsigned int height);

    /***
     * Function that returns the getScreenWidth
     * @return
     */
    int getScreenWidth() const;

    /***
     * Function that returns the getScreenHeight
     * @return
     */
    int getScreenHeight() const;

    /***
     * Function that returns the current camera height in the logic world
     * @return
     */
    int getHeight() const;
};


#endif //TESTREPO_CAMERA_H
