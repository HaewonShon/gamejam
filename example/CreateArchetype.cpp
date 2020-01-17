#include "CreateArchetype.h"
#include "engine/State.h"
#include "CustomBaseObject.h"
#include "DemoCollisionTrigger.h"
#include "DemoPlayerController.h"
#include "Color.h"
#include "DemoPlayerAnimation.h"
#include "DemoChasePlayer.h"
#include "DemoUIButton.h"
#include "ContactData.h"

CustomBaseObject& CreateBody(CustomBaseObject& body, const char* name, float positionX, float positionY,
    float scaleX, float scaleY, CustomPhysics::BodyType type, CustomPhysics::BodyShape shape, SDL_Color color,
    const char* filePath)
{
    // Set the object's name
    body.SetName(name);

    /*
    * Transform
    */
    // Set the position of the object
    body.transform.position.Set(positionX, positionY, 0);
    // Set the scale of the object
    body.transform.SetScale(scaleX, scaleY);
    // Set the rotation of the object
    body.transform.rotation = 0;
    /*
    * Sprite
    */
    // Load the image by passing directory and renderer
    // *Only png files work
    body.sprite.LoadImage(filePath, State::m_renderer);
    // Set the colors r,g,b,a (0~255)
    body.sprite.color = color;

    /*
    * Physics
    */
    // Set the body type of the body
    body.customPhysics.bodyType = type;
    // Set the body shape of the body
    body.customPhysics.bodyShape = shape;
    body.customPhysics.radius = 32.f;
    // Set the restitution of the body
    body.customPhysics.SetRestitution(0);
    // Set the density of the body
    body.customPhysics.SetDensity(10.F);
    // Generate acutal body based on information you set
    body.customPhysics.GenerateBody(State::sCurrentState->GetCustomPhysicsWorld(), &body.transform);


    // Register the object to the state
    State::sCurrentState->AddObject(&body);
    // *You have to add custom physics component to custom physics list manually,
    // by using AddCustomPhysicsComponent function.
    State::sCurrentState->AddCustomPhysicsComponent(&body);

    return body;
}

CustomBaseObject& CreateHudSprite(CustomBaseObject& sprite, const char* name, float positionX, float positionY,
    float scaleX, float scaleY, const char* filePath, bool isVisible)
{
    // Set the object's name
    sprite.SetName(name);

    /*
     * Transform
     */
    // Set the position of the object
    sprite.transform.position.Set(positionX, positionY, 0);
    // Set the scale of the object
    sprite.transform.SetScale(scaleX, scaleY);
    // Set the rotation of the object
    sprite.transform.rotation = 0;

    /*
     * Sprite
     */
     // Load the image by passing directory and renderer
     // *Only png files work
    sprite.sprite.LoadImage(filePath, State::m_renderer);
    // Set either if the object to be hud or not
    sprite.sprite.isHud = true;
    // Set either if the object to be visible or not
    sprite.sprite.isVisible = isVisible;


    // Register the object to the state
    State::sCurrentState->AddObject(&sprite);
    return sprite;
}

CustomBaseObject& CreateHudText(CustomBaseObject& textObject, const char* name, float positionX, float positionY, 
    float scaleX, float scaleY, TTF_Font* font, const char* textContents, SDL_Color color)
{
    // Set the object's name
    textObject.SetName(name);

    /*
    * Transform
    */
    // Set the position of the object
    textObject.transform.position.Set(positionX, positionY, 0);
    // Set the scale of the object
    textObject.transform.SetScale(scaleX, scaleY);

    /*
     * Text
     */
    // Set the text to render out
    textObject.text.SetText(State::m_renderer, textContents, font);
    // Set the colors r,g,b,a (0~255)
    textObject.text.color = color;
    // Set either if the object to be hud or not
    textObject.text.isHud = true;

    // Register the object to the state
    State::sCurrentState->AddObject(&textObject);
    return textObject;
}

CustomBaseObject& CreateCheckPoint(CustomBaseObject& check, const char* name, float positionX,
    float positionY, float scaleX, float scaleY)
{
    // Set the object's name
    check.SetName(name);

    /*
    * Transform
    */
    // Set the position of the object
    check.transform.position.Set(positionX, positionY + scaleY * 0.5f, 0.f);
    // Set the scale of the object
    check.transform.SetScale(scaleX, scaleY);
    // Set the rotation of the object
    check.transform.rotation = 0;

    /*
    * Sprite
    */
    // Set the image of sprite
    check.sprite.LoadImage("texture/CheckpointSpot1.png", State::m_renderer);
    // Set toggle true so animation activates 
    check.sprite.activeAnimation = true;
    // Set the number of frames to update
    check.sprite.SetFrame(5);
    // Set the speed of frame updating
    check.sprite.SetSpeed(12.f);

    /*
     * Physics
     */
    // Set the body type of the body
    check.customPhysics.bodyType = CustomPhysics::STATIC;
    // Set the body shape of the body
    check.customPhysics.bodyShape = CustomPhysics::BOX;
    // Set the restitution of the body
    check.customPhysics.SetRestitution(0.f); // by setting 0, object does not bounce, when it collide with something
    // Set the density of the body
    check.customPhysics.SetDensity(10.F);
    // Generate acutal body based on information you set
    check.customPhysics.GenerateBody(State::sCurrentState->GetCustomPhysicsWorld(), &check.transform);
    // Set the ghost collision of the body
    check.customPhysics.ActiveGhostCollision(false);

    /*
     * Component
     */
    // Add component to the object
    DemoCollisionTrigger* trigger = dynamic_cast<DemoCollisionTrigger*>(
                 State::sCurrentState->AddComponentToObject(&check, eComponentTypes::DemoCollisionTrigger));
    // Set component's information
    trigger->mTargetName = "Player";
    trigger->mCommandType = eCommandTypes::CheckPointCommand;


    // Register the object to the state
    State::sCurrentState->AddObject(&check);
    // *You have to add custom physics component to custom physics list manually,
    // by using AddCustomPhysicsComponent function.
    State::sCurrentState->AddCustomPhysicsComponent(&check);

    return check;
}

CustomBaseObject& CreateDamageTrap(CustomBaseObject& trap, const char* name, const char* targetName,
    float positionX, float positionY, float scaleX, float scaleY, CustomPhysics::BodyType type, bool isGhost,
    SDL_Color color, const char* filePath, int damage, bool isTrap)
{
    // Set the object's name
    trap.SetName(name);

    /*
    * Transform
    */
    // Set the position of the object
    trap.transform.position.Set(positionX, positionY, 0);
    // Set the scale of the object
    trap.transform.SetScale(scaleX, scaleY);
    // Set the rotation of the object
    trap.transform.rotation = 0;
    /*
    * Sprite
    */
    // Set the image of sprite
    trap.sprite.LoadImage(filePath, State::m_renderer);
    // Set the color of sprite
    trap.sprite.color = color;

    /*
    * Physics
    */
    // Set the body type of the body
    trap.customPhysics.bodyType         = type;
    // Set the body shape of the body
    trap.customPhysics.bodyShape        = CustomPhysics::BOX;
    trap.customPhysics.radius           = 32.f;
    // Set the restitution of the body
    trap.customPhysics.SetRestitution(0);
    // Set the density of the body
    trap.customPhysics.SetDensity(10.F);
    // Generate acutal body based on information you set
    trap.customPhysics.GenerateBody(State::sCurrentState->GetCustomPhysicsWorld(), &trap.transform);
    // Set the ghost collision of the body
    trap.customPhysics.ActiveGhostCollision(!isGhost);
    /*
    * Component
    */
    DemoCollisionTrigger* trigger = dynamic_cast<DemoCollisionTrigger*>(
        State::sCurrentState->AddComponentToObject(&trap, eComponentTypes::DemoCollisionTrigger));
    // Set component's information
    trigger->mTargetName = targetName;
    if (!isTrap)
    {
        trigger->SetTiriggerType(eTriggerTypes::Disappear);
    }
    trigger->mCommandType = eCommandTypes::DamageCommand;
    trigger->mDamage = damage;


    // Register the object to the state
    State::sCurrentState->AddObject(&trap);
    // *You have to add custom physics component to custom physics list manually,
    // by using AddCustomPhysicsComponent function.
    State::sCurrentState->AddCustomPhysicsComponent(&trap);

    return trap;
}

CustomBaseObject& CreatePlatformerEnemy(CustomBaseObject& enemy, const char* name, const char* targetName,
    float positionX, float positionY, float scaleX, float scaleY, std::string textureName, unsigned frame, float frameSpeed, bool isWalking)
{
    // Set the object's name
    enemy.SetName(name);

    /*
    * Transform
    */
    // Set the position of the object
    enemy.transform.position.Set(positionX, positionY, 0);
    // Set the scale of the object
    enemy.transform.SetScale(scaleX, scaleY);
    // Set the rotation of the object
    enemy.transform.rotation = 0;

    /*
    * Sprite
    */
    // Set the image of sprite
    std::string filePath = "texture/" + textureName;
    enemy.sprite.LoadImage(filePath.c_str(), State::m_renderer);
    // Set toggle true so animation activates 
    enemy.sprite.activeAnimation = true;
    // Set the number of frames to update
    enemy.sprite.SetFrame(frame);
    // Set the speed of frame updating
    enemy.sprite.SetSpeed(frameSpeed);

    /*
    * Physics
    */
    // Set the body type of the body
    enemy.customPhysics.bodyType = CustomPhysics::DYNAMIC;
    // Set the body shape of the body
    enemy.customPhysics.bodyShape = CustomPhysics::BOX;
    enemy.customPhysics.radius = 32.f;
    // Set the restitution of the body
    enemy.customPhysics.SetRestitution(0);
    // Set the density of the body
    enemy.customPhysics.SetDensity(10.F);
    // Generate acutal body based on information you set
    enemy.customPhysics.GenerateBody(State::sCurrentState->GetCustomPhysicsWorld(), &enemy.transform);

    /*
    * Component
    */
    if (isWalking)
    {
        // Add component to the object
        State::sCurrentState->AddComponentToObject(&enemy, eComponentTypes::DemoEnemyController);
        // Add component to the object
        DemoCollisionTrigger* trigger = dynamic_cast<DemoCollisionTrigger*>(
            State::sCurrentState->AddComponentToObject(&enemy, eComponentTypes::DemoCollisionTrigger));
        // Set component's information
        trigger->mTargetName = targetName;
        trigger->mCommandType = eCommandTypes::DamageCommand;
    }
    else
    {
        // Add component to the object
        DemoChasePlayer* chase = dynamic_cast<DemoChasePlayer*>(
            State::sCurrentState->AddComponentToObject(&enemy, eComponentTypes::DemoChasePlayer));
        // Set component's information
        chase->mSpeed = 10.f;
        chase->mDetectRadius = 250.f;
        // Add component to the object
        DemoCollisionTrigger* trigger = dynamic_cast<DemoCollisionTrigger*>(
            State::sCurrentState->AddComponentToObject(&enemy, eComponentTypes::DemoCollisionTrigger));
        // Set component's information
        trigger->mTargetName = targetName;
        trigger->mCommandType = eCommandTypes::DamageCommand;

        // Set the ghost collision of the body
        enemy.customPhysics.ActiveGhostCollision(false);
        // Set the gravity scale
        enemy.customPhysics.GetBody()->SetGravityScale(0); // by setting Zero, it does not affected by Gravity
    }

    // Register the object to the state
    State::sCurrentState->AddObject(&enemy);
    // *You have to add custom physics component to custom physics list manually,
    // by using AddCustomPhysicsComponent function.
    State::sCurrentState->AddCustomPhysicsComponent(&enemy);

    return enemy;
}

CustomBaseObject& CreatePlatformerLevelClear(CustomBaseObject& levelClear, const char* name, float positionX,
    float positionY, float scaleX, float scaleY, Level_ID nextLevel)
{
    // Set the object's name
    levelClear.SetName(name);

    /*
    * Transform
    */
    // Set the position of the object
    levelClear.transform.position.Set(positionX, positionY, 0);
    // Set the scale of the object
    levelClear.transform.SetScale(scaleX, scaleY);
    // Set the rotation of the object
    levelClear.transform.rotation = 0;

    /*
    * Sprite
    */
    // Set the image of sprite
    levelClear.sprite.LoadImage("texture/CheckpointSpot2Wave.png", State::m_renderer);
    // Set toggle true so animation activates 
    levelClear.sprite.activeAnimation = true;
    // Set the number of frames to update
    levelClear.sprite.SetFrame(4);
    // Set the speed of frame updating
    levelClear.sprite.SetSpeed(12.f);

    /*
    * Physics
    */
    // Set the body type of the body
    levelClear.customPhysics.bodyType = CustomPhysics::STATIC;
    // Set the body shape of the body
    levelClear.customPhysics.bodyShape = CustomPhysics::BOX;
    // Set the restitution of the body
    levelClear.customPhysics.SetRestitution(0.f);
    // Set the density of the body
    levelClear.customPhysics.SetDensity(10.F);
    // Generate acutal body based on information you set
    levelClear.customPhysics.GenerateBody(State::sCurrentState->GetCustomPhysicsWorld(), &levelClear.transform);
    // Set the ghost collision of the body
    levelClear.customPhysics.ActiveGhostCollision(false);

    /*
    * Component
    */
    // Add component to the object
    DemoCollisionTrigger* clearTrigger = dynamic_cast<DemoCollisionTrigger*>(State::sCurrentState->AddComponentToObject(&levelClear, eComponentTypes::DemoCollisionTrigger));
    // Set component's information
    clearTrigger->SetTiriggerType(eTriggerTypes::Once);
    clearTrigger->mReactiveCount = 1.5f;
    clearTrigger->mTargetName = "Player";
    clearTrigger->mCommandType = eCommandTypes::ChangeStateCommand;
    clearTrigger->mChangeLevel = nextLevel;

    // Register the object to the state
    State::sCurrentState->AddObject(&levelClear);
    // *You have to add custom physics component to custom physics list manually,
    // by using AddCustomPhysicsComponent function.
    State::sCurrentState->AddCustomPhysicsComponent(&levelClear);
    return levelClear;
}

CustomBaseObject& CreateTopdownPlayer(CustomBaseObject& player, const char* name, float scaleX, float scaleY)
{
    // Set the object's unique name
    player.SetName(name);

    /*
    * Transform
    */
    // Set the position of the object
    player.transform.position.SetZero();
    // Set the scale of the object
    player.transform.SetScale(scaleX, scaleY);

    /*
    * Sprite
    */
    // Connet the address of transform so sprite can use it implicitly
    player.sprite.LoadImage("texture/TopdownPlayer.png", State::m_renderer);

    /*
    * Physics
    */
    // Set body type 
    player.customPhysics.bodyType = CustomPhysics::DYNAMIC;
    // Set body shape
    player.customPhysics.bodyShape = CustomPhysics::BOX;
    // Set radius
    player.customPhysics.radius = (scaleX > scaleY ? scaleX : scaleY) * 0.5f;
    // Set density
    player.customPhysics.SetDensity(1.f);
    // Set restitution
    player.customPhysics.SetRestitution(0.f);
    // Generate rigidbody passing world and transform
    player.customPhysics.GenerateBody(State::sCurrentState->GetCustomPhysicsWorld(), &player.transform);

    /*
     * Emitter
     */
    player.emitter.type = Emitter::PARTICLE_NORMAL;
    player.emitter.life = 0.1f;
    player.emitter.LoadImage("texture/fire.png", State::m_renderer);
    b2Vec3 player_start(1.f, 1.f, 1.f), player_end(1.f, 1.f, 1.f);
    player.emitter.SetColors(player_start, player_end);
    player.emitter.GenerateParticles(500, &player.transform);
    b2Vec2 player_xVel(0, 0), player_yVel(0, 0);
    player.emitter.SetVelocity(player_xVel, player_yVel);


    /*
    * Component
    */
    // Add component to the object
    State::sCurrentState->AddComponentToObject(&player, eComponentTypes::DemoTopdownController);
    // Add component to the object
    State::sCurrentState->AddComponentToObject(&player, eComponentTypes::DemoWrapPosition);


    // Register the object to the state
    State::sCurrentState->AddObject(&player);
    // *You have to add custom physics component to custom physics list manually,
    // by using AddCustomPhysicsComponent function.
    State::sCurrentState->AddCustomPhysicsComponent(&player);
    return player;
}

CustomBaseObject& CreatePlatformerPlayer(CustomBaseObject& player, const char* name, float scaleX, float scaleY)
{
    // Set the object's name
    player.SetName(name);

    /*
    * Transform
    */
    // Set the position of the object
    player.transform.position.Set(DemoPlayerController::sStartPosition.x, DemoPlayerController::sStartPosition.y, 0.0f);
    // Set the scale of the object
    player.transform.SetScale(scaleX, scaleY);

    /*
    * Sprite
    */
    // Connet the address of transform so sprite can use it implicitly
    player.sprite.LoadImage("texture/MonkeyStand.png", State::m_renderer);

    /*
    * Physics
    */
    // Set the body type of the body
    player.customPhysics.bodyType = CustomPhysics::DYNAMIC;
    // Set body shape
    player.customPhysics.bodyShape = CustomPhysics::BOX;
    // Set radius
    player.customPhysics.radius = (scaleX > scaleY ? scaleX : scaleY) * 0.5f;
    // Set density
    player.customPhysics.SetDensity(1.f);
    // Set restitution
    player.customPhysics.SetRestitution(0.f);
    // Generate rigidbody passing world and transform
    player.customPhysics.GenerateBody(State::sCurrentState->GetCustomPhysicsWorld(), &player.transform);
    // generate foot sensor
    player.customPhysics.GenerateSensor(0, -scaleY * 0.5f, eContactTypes::FootSensor);

    /*
    * Component
    */
    // Add component to the object
    State::sCurrentState->AddComponentToObject(&player, eComponentTypes::DemoPlayerController);
    // Add component to the object
    DemoPlayerAnimation* playerAnimation = dynamic_cast<DemoPlayerAnimation*>(
                        State::sCurrentState->AddComponentToObject(&player, eComponentTypes::DemoPlayerAnimation));
    // set player's animation file name
    playerAnimation->mPlayerStandFile   = "texture/MonkeyStand.png";
    playerAnimation->mPlayerWalkFile    = "texture/MonkeyWalk.png";
    playerAnimation->mPlayerJumpFile    = "texture/MonkeyJump.png";


    // Register the object to the state
    State::sCurrentState->AddObject(&player);
    // *You have to add custom physics component to custom physics list manually,
    // by using AddCustomPhysicsComponent function.
    State::sCurrentState->AddCustomPhysicsComponent(&player);

    return player;
}

DemoUIButton* CreateUIButton(CustomBaseObject& buttonObject, const char* name, float positionX, float positionY,
    float scaleX, float scaleY, std::string defaultFileName, std::string hoveredFileName, eCommandTypes commandType)
{
    // Set the object's name
    buttonObject.SetName(name);

    /*
    * Transform
    */
    // Set the position of the object
    buttonObject.transform.position.Set(positionX, positionY, 0.f);
    // Set the scale of the object
    buttonObject.transform.SetScale(scaleX, scaleY);


    /*
    * Sprite
    */
    std::string filePath = "texture/";
    // Set the image of sprite
    buttonObject.sprite.LoadImage((filePath + defaultFileName).c_str(), State::m_renderer);
    // Set either if the object to be hud or not
    buttonObject.sprite.isHud = true;

    /*
    * Component
    */
    // Add component to the object
    DemoUIButton* button = dynamic_cast<DemoUIButton*>(
        State::sCurrentState->AddComponentToObject(&buttonObject, eComponentTypes::DemoUIButton));
    // Set component's information
    button->mDefaultSpriteFile = filePath + defaultFileName;
    button->mHoveredSpriteFile = filePath + hoveredFileName;
    // Add command to the component
    button->mButtonEvent = State::sCurrentState->CreateCommand(commandType);

    // Register the object to the state
    State::sCurrentState->AddObject(&buttonObject);
    return button;
}
