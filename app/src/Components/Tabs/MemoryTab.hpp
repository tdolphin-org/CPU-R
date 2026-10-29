//
//  CPU-R
//
//  (c) 2026 TDolphin
//

#pragma once

#include "Components/Base.hpp"
#include "Components/Core/Root.hpp"

#include "MUI/Group.hpp"
#include "MUI/Text.hpp"

namespace Components
{
    class MemoryTab : public Root<MUI::Group>, public Base
    {
        MUI::Text mTotalSystemMemoryText;

        MUI::Group mComponent;

      public:
        MemoryTab();

      protected:
        MUI::Group &muiRoot() const override
        {
            return const_cast<MUI::Group &>(mComponent);
        }
    };
}