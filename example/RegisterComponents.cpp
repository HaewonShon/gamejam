#include "RegisterComponents.h"
#include "engine/ComponentBuilder.h"
#include "example/ComponentTypes.h"
#include "example/DemoLv1Controller.h"
#include "example/DemoLv2Controller.h"
#include "example/DemoControlEmitters.h"
#include "example/DemoLv4Controller.h"
#include "example/DemoPlatformerController.h"
#include "example/DemoCameraLogic.h"
#include "example/DemoUIButton.h"
#include "example/DemoPlayerController.h"
#include "example/DemoEnemyController.h"
#include "example/DemoPlayerAnimation.h"
#include "example/DemoRescale.h"
#include "example/DemoCollisionTrigger.h"
#include "example/DemoTopdownController.h"
#include "example/DemoWrapPosition.h"
#include "example/DemoEnemySpawner.h"
#include "example/DemoReposition.h"
#include "example/DemoChasePlayer.h"

/**
 * \brief 
 * Register each component builder
 */
void RegisterComponents()
{
    State::AddComponentBuilder( eComponentTypes::DemoLv1Controller, 
                                new ComponentTBuilder<DemoLv1Controller>());
    State::AddComponentBuilder( eComponentTypes::DemoLv2Controller,
                                new ComponentTBuilder<DemoLv2Controller>());
    State::AddComponentBuilder( eComponentTypes::DemoControlEmitters, 
                                new ComponentTBuilder<DemoControlEmitters>());
    State::AddComponentBuilder( eComponentTypes::DemoLv4Controller, 
                                new ComponentTBuilder<DemoLv4Controller>());
    State::AddComponentBuilder( eComponentTypes::DemoPlatformerController,
                                new ComponentTBuilder<DemoPlatformerController>());
    State::AddComponentBuilder( eComponentTypes::DemoPlayerController,
                                new ComponentTBuilder<DemoPlayerController>());
    State::AddComponentBuilder( eComponentTypes::DemoEnemyController,
                                new ComponentTBuilder<DemoEnemyController>());
    State::AddComponentBuilder( eComponentTypes::DemoPlayerAnimation,
                                new ComponentTBuilder<DemoPlayerAnimation>());
    State::AddComponentBuilder( eComponentTypes::DemoCameraLogic,
                                new ComponentTBuilder<DemoCameraLogic>());
    State::AddComponentBuilder( eComponentTypes::DemoUIButton,
                                new ComponentTBuilder<DemoUIButton>());
    State::AddComponentBuilder( eComponentTypes::DemoReposition,
                                new ComponentTBuilder<DemoReposition>());
    State::AddComponentBuilder( eComponentTypes::DemoRescale,
                                new ComponentTBuilder<DemoRescale>());
    State::AddComponentBuilder( eComponentTypes::DemoCollisionTrigger,
                                new ComponentTBuilder<DemoCollisionTrigger>());
    State::AddComponentBuilder( eComponentTypes::DemoTopdownController,
                                new ComponentTBuilder<DemoTopdownController>());
    State::AddComponentBuilder( eComponentTypes::DemoWrapPosition,
                                new ComponentTBuilder<DemoWrapPosition>());
    State::AddComponentBuilder( eComponentTypes::DemoEnemySpawner,
                                new ComponentTBuilder<DemoEnemySpawner>());
    State::AddComponentBuilder( eComponentTypes::DemoChasePlayer,
                                new ComponentTBuilder<DemoChasePlayer>());
}
