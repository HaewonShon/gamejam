/******************************************************************************/
/*!
\file   ComponentTypes.h
\author Hun Yang
\par    email: hun.yang8456@gmail.com
\par    GAM150 demo
\date   2019/04/30


*/
/******************************************************************************/
#pragma once

#include <string>

/**
* \brief
* This is enum class for component types
*/
enum class eComponentTypes
{
    INVALID = 0,
    DemoLv1Controller,
    DemoLv2Controller,
    DemoControlEmitters,
    DemoLv4Controller,
    DemoPlatformerController,
    DemoPlayerController,
    DemoEnemyController,
    DemoTopdownController,
    DemoPlayerAnimation,
    DemoCameraLogic,
    DemoUIButton,
    DemoReposition,
    DemoRescale,
    DemoCollisionTrigger,
    DemoWrapPosition,
    DemoEnemySpawner,
    DemoChasePlayer,

    NUM_COMPONENTS
};

/**
* \brief
* Convert string to eComponentTypes's component
*
* \param string
* String to be  converted for component type
*
* \return
* Converted component type
*/
inline eComponentTypes StringToComponent(const std::string& string)
{
    if (string == "DemoLv1Controller")			    return eComponentTypes::DemoLv1Controller;
    if (string == "DemoLv2Controller")			    return eComponentTypes::DemoLv2Controller;
    if (string == "DemoControlEmitters")			return eComponentTypes::DemoControlEmitters;
    if (string == "DemoLv4Controller")			    return eComponentTypes::DemoLv4Controller;
    if (string == "DemoPlatformerController")			return eComponentTypes::DemoPlatformerController;
    if (string == "DemoPlayerController")			return eComponentTypes::DemoPlayerController;
    if (string == "DemoEnemyController")			return eComponentTypes::DemoEnemyController;
    if (string == "DemoTopdownController")			return eComponentTypes::DemoTopdownController;
    if (string == "DemoPlayerAnimation")			return eComponentTypes::DemoPlayerAnimation;
    if (string == "DemoCameraLogic")			    return eComponentTypes::DemoCameraLogic;
    if (string == "DemoUIButton")			        return eComponentTypes::DemoUIButton;
    if (string == "DemoReposition")			        return eComponentTypes::DemoReposition;
    if (string == "DemoRescale")			        return eComponentTypes::DemoRescale;
    if (string == "DemoCollisionTrigger")			return eComponentTypes::DemoCollisionTrigger;
    if (string == "DemoWrapPosition")			    return eComponentTypes::DemoWrapPosition;
    if (string == "DemoEnemySpawner")			    return eComponentTypes::DemoEnemySpawner;
    if (string == "DemoChasePlayer")			    return eComponentTypes::DemoChasePlayer;
    return eComponentTypes::INVALID;
}

/**
* \brief
* Convert eComponentTypes's component to string
*
* \param type
* Component type to be converted for string
*
* \return
* Converted string
*/
inline std::string ComponentToString(eComponentTypes type)
{
    if (type == eComponentTypes::DemoLv1Controller)		        return "DemoLv1Controller";
    if (type == eComponentTypes::DemoLv2Controller)		        return "DemoLv2Controller";
    if (type == eComponentTypes::DemoControlEmitters)		    return "DemoControlEmitters";
    if (type == eComponentTypes::DemoLv4Controller)		        return "DemoLv4Controller";
    if (type == eComponentTypes::DemoPlatformerController)		    return "DemoPlatformerController";
    if (type == eComponentTypes::DemoPlayerController)		    return "DemoPlayerController";
    if (type == eComponentTypes::DemoEnemyController)		    return "DemoEnemyController";
    if (type == eComponentTypes::DemoTopdownController)		    return "DemoTopdownController";
    if (type == eComponentTypes::DemoPlayerAnimation)		    return "DemoPlayerAnimation";
    if (type == eComponentTypes::DemoCameraLogic)		        return "DemoCameraLogic";
    if (type == eComponentTypes::DemoUIButton)		            return "DemoUIButton";
    if (type == eComponentTypes::DemoReposition)		        return "DemoReposition";
    if (type == eComponentTypes::DemoRescale)		            return "DemoRescale";
    if (type == eComponentTypes::DemoCollisionTrigger)		    return "DemoCollisionTrigger";
    if (type == eComponentTypes::DemoWrapPosition)		        return "DemoWrapPosition";
    if (type == eComponentTypes::DemoEnemySpawner)		        return "DemoEnemySpawner";
    if (type == eComponentTypes::DemoChasePlayer)		        return "DemoChasePlayer";

    return "Invalid";
}