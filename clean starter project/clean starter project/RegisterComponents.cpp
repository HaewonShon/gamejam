
#include "engine\State.h"
#include "RegisterComponents.h"
#include "engine/ComponentBuilder.h"
#include "DemoUIButton.h"

/**
 * \brief 
 * Register each component builder
 */
void RegisterComponents()
{
    State::AddComponentBuilder( eComponentTypes::DemoUIButton,
                                new ComponentTBuilder<DemoUIButton>());
}

void UnregisterComponents()
{
    State::RemoveComponentBuilder(eComponentTypes::DemoUIButton);
}
