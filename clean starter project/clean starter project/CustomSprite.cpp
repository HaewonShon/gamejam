#include "CustomSprite.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

CustomSprite::CustomSprite():
    mTexture(nullptr),
    mImageWidth(0), mImageHeight(0),
    mFrames(0), mFrameSpeed(0),
    mActiveAnimation(false), mRewindAnimation(false), mStopAnimation(false)
{

}

/**
 * \brief 
 * if there is texture, destroy it.
 */
CustomSprite::~CustomSprite()
{
    if (mTexture) {
        SDL_DestroyTexture(mTexture);
        mTexture = nullptr;
    }
}

/**
 * \brief
 * Load image and set animation info
 * 
 * \param renderer 
 * \param filePath 
 * \param isAnimation 
 * \param frames 
 * \param speed 
 */
void CustomSprite::Initialize(SDL_Renderer* renderer, std::string filePath, bool isAnimation, unsigned frames, float speed)
{
    // Load image file
    SDL_Surface* loadedImage = IMG_Load(filePath.c_str());
    // Get image size (width and height)
    mImageWidth = loadedImage->w;
    mImageHeight = loadedImage->h;
    // Create surface and allocate to texture
    mTexture = SDL_CreateTextureFromSurface(renderer, loadedImage);
    // Release temp surface
    SDL_FreeSurface(loadedImage);

    mActiveAnimation    = isAnimation;
    mFrames             = frames;
    mFrameSpeed         = speed;
}

/**
 * \brief 
 * Get pointer to the texture
 * 
 * \return mTexture
 * pointer to the texture
 */
SDL_Texture* CustomSprite::GetTexture() const
{
    return mTexture;
}
