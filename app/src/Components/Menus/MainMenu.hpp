//
//  CPU-R
//
//  (c) 2026 TDolphin
//

#pragma once

#include "Components/Core/Root.hpp"
#include "MUI/Menu.hpp"
#include "MUI/Menuitem.hpp"
#include "MUI/Menustrip.hpp"

namespace Components
{
    class MainMenu : public Root<MUI::Menustrip>
    {
        MUI::Menu mCPURMenu;
        MUI::Menu mSettingsMenu;

        MUI::Menustrip mComponent;

      public:
        MainMenu();

      protected:
        MUI::Menustrip &muiRoot() const override
        {
            return (MUI::Menustrip &)mComponent;
        }
    };
}
