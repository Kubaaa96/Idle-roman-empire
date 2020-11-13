#ifndef IRE_GAME_WINDOW_H
#define IRE_GAME_WINDOW_H

#include "core/gui/SystemWindow.h"

#include "core/gui/widgets/Button.h"
#include "core/gui/widgets/Label.h"
#include "core/gui/widgets/EditBox.h"
#include "core/gui/widgets/Panel.h"
#include "core/gui/widgets/HorizontalLayout.h"
#include "core/gui/widgets/VerticalLayout.h"
#include "client/states/IntroState.h"
#include "client/states/GameState.h"

namespace ire::client {

    struct GameWindow : core::gui::SystemWindow
    {
        using BaseType = core::gui::SystemWindow;

        template <typename... Ts>
        GameWindow(Ts&&... args) :
            BaseType(std::forward<Ts>(args)...)
        {
            //auto introState = std::make_unique<state::IntroState>();
            //setCurrentState(introState);
            auto gameState = std::make_unique<state::GameState>(getRenderTarget().getSize());
            setRootGroup(*gameState->drawGUI());
            //init();
        }
    private:

        void init();
    };

}

#endif // !IRE_GAME_WINDOW_H
