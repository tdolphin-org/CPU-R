//
//  CPU-R
//
//  (c) 2026 TDolphin
//

#include "Components/Core/Root.hpp"

#include "Components/Base.hpp"
#include "Components/Tabs/Boards/BoardRomSize.hpp"
#include "DataInfo/BoardInfo.hpp"
#include "MUI/Group.hpp"
#include "MUI/Window.hpp"

// forward declarations
namespace AOS::PCIX
{
    struct BoardAttributes;
}

namespace Components
{
    class BoardAttributesWindow : public Root<MUI::Window>, public Base
    {
        MUI::Text mVendor;
        MUI::Text mDevice;
        MUI::Text mClass;

        MUI::Group mHeaderGroup;

        MUI::Window mComponent;

      public:
        BoardAttributesWindow();

        void Open(const BoardInfo &boardInfo); // TODO : pass some Board Attributes
        void Close();

        bool isOpen() const
        {
            return mComponent.isOpen();
        }

      protected:
        MUI::Window &muiRoot() const override
        {
            return const_cast<MUI::Window &>(mComponent);
        }
    };
}
