//
//  CPU-R
//
//  (c) 2026 TDolphin
//

#pragma once

#include "Components/Core/Root.hpp"
#include "Components/MCC/ActionList.hpp"
#include "DataInfo/BoardInfo.hpp"

#include "MUI/Group.hpp"
#include "MUI/List.hpp"

namespace Components
{
    class BoardsList : public Root<MUI::List>, public MCC::ActionListDispatcher
    {
        MUI::List mComponent;

      public:
        explicit BoardsList(); // TODO : pass actual list of boards to constructor

      protected:
        // implements pure virtual MCC::ActionListDispatcher
        unsigned long OnActiveEntry() override;
        unsigned long OnDoubleClickEntry() override;

      protected:
        MUI::List &muiRoot() const override
        {
            return const_cast<MUI::List &>(mComponent);
        }

      private:
        void OpenBoardAttributes(const long activeEntry) const;
    };
}