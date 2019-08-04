#include "LaserObject.h"
#include "constants.h"

LaserObject::LaserObject(Point pos, CTexture* tex, CVector velocity, CVector acceleration, Uint32 updateTime, double rotation)
    : GameObject(pos, tex, velocity, acceleration, updateTime)
{
    // std::cout << "Laser ID: " << _id << "\n";
    // std::cout << "Position (" << pos.x << ", " << pos.y << ")\n";
    // std::cout << "New laser velocity: " <<  velocity << std::endl;

    _rotation = rotation;
    _width = _pTex->getWidth()/20;
    _height = _pTex->getHeight()/24;
}

void LaserObject::update(Uint32 updateTime)
{

    double timeDelta = static_cast<double>(updateTime - _lastUpdated)/1000;

    _pos.x += _velocity.getXProjection() * timeDelta;
    _pos.y += _velocity.getYProjection() * timeDelta;

    _lastUpdated = updateTime;

}

bool LaserObject::checkOffscreen()
{
    if(_pos.x < -AsteroidConstants::OFFSCREEN_BOUNDARY || _pos.x > AsteroidConstants::SCREEN_WIDTH + AsteroidConstants::OFFSCREEN_BOUNDARY)
        return true;
    if(_pos.y < -AsteroidConstants::OFFSCREEN_BOUNDARY || _pos.y > AsteroidConstants::SCREEN_HEIGHT + AsteroidConstants::OFFSCREEN_BOUNDARY)
        return true;
    return false;
}

void LaserObject::render(SDL_Renderer* renderer)
{
    int xPosCenter = std::round(_pos.x);
    int yPosCenter = std::round(_pos.y);

    int left = xPosCenter - _width/2;
    int top = yPosCenter - _height/2;

    SDL_Rect dstRect{left, top, _width, _height};

    //std::cout << "Laser position: (" << left << ", " << top << ")" << std::endl;

    SDL_RenderCopyEx( renderer, _pTex->getTexture(), nullptr, &dstRect, _rotation, nullptr, SDL_FLIP_NONE);

    // SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);  
    // SDL_RenderDrawRect(renderer, &dstRect);

    _boundingBox = std::move(dstRect);

}

SDL_Rect& LaserObject::getBoundingBox()
{
    return _boundingBox;
}