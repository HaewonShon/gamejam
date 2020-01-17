/******************************************************************************/
/*!
\file   CustomSprite.h
\author Hun Yang
\par    email: hun.yang8456@gmail.com
\par    GAM150 demo
\date   2019/04/28

Custom sprite component
This is used, when one object needs to change it's sprite image based on various conditions.
*/
/******************************************************************************/
#pragma once
#include <string>

struct SDL_Texture;
struct SDL_Renderer;

class CustomSprite
{
    friend class Sprite;
public:
    CustomSprite();
    ~CustomSprite();
    // Load image and set animation info
    void            Initialize  (SDL_Renderer* renderer, std::string filePath, bool isAnimation = false, unsigned frames = 0, float speed = 0);
    // Get pointer to the texture
    SDL_Texture*    GetTexture  (void)  const;
private:
    SDL_Texture*    mTexture;	                    // Texture to store image
    int			    mImageWidth, mImageHeight;      // Size of the image
    unsigned        mFrames;                        // number of frames
    float           mFrameSpeed;                    // the speed of frame change
    bool            mActiveAnimation,	            // Animation toggle 
                    mRewindAnimation,	            // Rewind toggle
                    mStopAnimation ;;		        // Stop toggle

};
