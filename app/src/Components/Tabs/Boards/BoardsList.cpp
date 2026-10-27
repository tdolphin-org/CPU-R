//
//  CPU-R
//
//  (c) 2026 TDolphin
//

#include "BoardsList.hpp"

#include "AOS/PCIIDS/Library.hpp"
#include "WindowManager.hpp"

#include "amiga_std_light/sstream.hpp"
#include <iomanip>

namespace Components
{
    const char *titles[] = { "[ID] Vendor", "[ID] Device", "Class", "Subsystem ID", nullptr };

    BoardsList::BoardsList()
      : mComponent(MCC::ActionListBuilder()
                       .stringArrayHooks(4)
                       .tagFormat("BAR MINWIDTH=0,BAR MINWIDTH=0,BAR MINWIDTH=0,")
                       .tagTitleArray(titles)
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
        auto boardAttributesOpt = AOS::PCIX::Library::GetBoardAttributes(mBoards[activeEntry].first);
        if (boardAttributesOpt.has_value())
            WindowManager::instance().getBoardAttributesWindow().Open(mBoards[activeEntry].second, boardAttributesOpt.value());
    }
}
