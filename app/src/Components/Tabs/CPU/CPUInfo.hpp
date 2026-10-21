//
//  CPU-R
//
//  (c) 2026 TDolphin
//

#pragma once

#include "Components/Base.hpp"
#include "Components/Core/Root.hpp"

#include "MUI/Group.hpp"

namespace Components
{
    class CPUInfo : public Root<MUI::Group>, public Base
    {
        MUI::Group mComponent;

      public:
        explicit CPUInfo();

      protected:
        MUI::Group &muiRoot() const override
        {
            return const_cast<MUI::Group &>(mComponent);
        }
    };
}
