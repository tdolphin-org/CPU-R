//
//  CPU-R
//
//  (c) 2026 TDolphin
//

#pragma once

#include "Components/Tabs/TabsContainer.hpp"
#include "Tabs/AboutTab.hpp"
#include "Tabs/BoardsTab.hpp"
#include "Tabs/CPUTab.hpp"
#include "Tabs/GraphicsTab.hpp"
#include "Tabs/MemoryTab.hpp"
#include "Tabs/OSTab.hpp"

namespace Components
{
    class Content : public Root<MUI::Group>
    {
        CPUTab mCPUTab;
        MemoryTab mMemoryTab;
        GraphicsTab mGraphicsTab;
        BoardsTab mBoardsTab;
        OSTab mOSTab;
        AboutTab mAboutTab;

        TabsContainer mComponent;

      public:
        Content();

        void RegisterEvents();

      protected:
        MUI::Group &muiRoot() const override
        {
            return mComponent;
        }
    };
}
