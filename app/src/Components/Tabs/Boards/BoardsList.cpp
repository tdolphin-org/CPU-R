//
//  CPU-R
//
//  (c) 2026 TDolphin
//

#include "BoardsList.hpp"

#include "WindowManager.hpp"

#include "amiga_std_light/sstream.hpp"
#include <iomanip>

namespace Components
{
    const char *titles[] = { "[ID] Vendor", "[ID] Device", "Class", "Subsystem ID", nullptr };

    BoardsList::BoardsList()
      : mComponent(MCC::ActionListBuilder()
                       .tagConstructHookString()
                       .tagDestructHookString()
                       .tagFormat("BAR MINWIDTH=0,BAR MINWIDTH=0,BAR MINWIDTH=0,")
                       .tagTitle(true)
                       .tagFrame(MUI::Frame::Group)
                       .object(*this))
    {
        // TODO: populate list with boards
    }

    unsigned long BoardsList::OnActiveEntry()
    {
        auto activeEntry = mComponent.getActive();
        if (activeEntry < 0)
            return 0;

        if (!WindowManager::instance().getBoardAttributesWindow().isOpen())
            return 0;

        // when board attributes window is open, than activate entry also show attributes of the active board
        OpenBoardAttributes(activeEntry);

        return 0;
    }

    unsigned long BoardsList::OnDoubleClickEntry()
    {
        auto activeEntry = mComponent.getActive();
        if (activeEntry < 0)
            return 0;

        // when entry is double clicked, than open board attributes window (or bring it to front if already open) and show attributes of the
        // active board
        OpenBoardAttributes(activeEntry);

        return 0;
    }

    void BoardsList::OpenBoardAttributes(const long activeEntry) const
    {
        // TODO : get board attributes and open board attributes window with them
    }
}
