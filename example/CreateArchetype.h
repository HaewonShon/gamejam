#pragma once
#include <SDL2/SDL.h>
#include "CommonLevel.h"

CustomBaseObject&   CreateBody                      (CustomBaseObject &body, const char *name,
                                                    float positionX, float positionY, float scaleX, float scaleY,
                                                    CustomPhysics::BodyType type, CustomPhysics::BodyShape shape,
                                                    SDL_Color color, const char* filePath = "texture/rect.png");
CustomBaseObject&   CreateHudSprite                 (CustomBaseObject &sprite, const char* name,
                                                    float positionX, float positionY, float scaleX, float scaleY,
                                                    const char* filePath, bool isVisible);
CustomBaseObject&   CreateHudText                   (CustomBaseObject& textObject, const char* name,
                                                    float positionX, float positionY, float scaleX, float scaleY,
                                                    TTF_Font* font, const char *textContents, SDL_Color color);

CustomBaseObject&   CreateCheckPoint                (CustomBaseObject& check, const char* name, 
                                                    float positionX, float positionY, float scaleX, float scaleY);

CustomBaseObject&   CreateDamageTrap                (CustomBaseObject& trap, const char* name, const char* targetName, 
                                                    float positionX, float positionY, float scaleX, float scaleY, 
                                                    CustomPhysics::BodyType type, bool isGhost, 
                                                    SDL_Color color, const char* filePath = "texture/rect.png", 
                                                    int damage = 2, bool isTrap = true);

CustomBaseObject&   CreatePlatformerEnemy           (CustomBaseObject& enemy, const char* name, const char* targetName, 
                                                    float positionX, float positionY, float scaleX, float scaleY,
                                                    std::string textureName, unsigned frame, float frameSpeed, bool isWalking);

CustomBaseObject&   CreatePlatformerLevelClear      (CustomBaseObject& levelClear, const char* name,
                                                    float positionX, float positionY, float scaleX, float scaleY,
                                                    Level_ID nextLevel);
CustomBaseObject&   CreateTopdownPlayer             (CustomBaseObject& player, const char* name,
                                                    float scaleX, float scaleY);
CustomBaseObject&   CreatePlatformerPlayer          (CustomBaseObject& player, const char* name,
                                                    float scaleX, float scaleY);

DemoUIButton*       CreateUIButton                  (CustomBaseObject& buttonObject, const char* name,
                                                    float positionX, float positionY, float scaleX, float scaleY,
                                                    std::string defaultFileName, std::string hoveredFileName,
                                                    eCommandTypes commandType);
