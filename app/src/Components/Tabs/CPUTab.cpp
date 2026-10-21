//
//  CPU-R
//
//  (c) 2026 TDolphin
//

#include "CPUTab.hpp"

#include "AOS/Exec/Library.hpp"
#include "MUI/Core/MakeObject.hpp"
#include "MUI/Image.hpp"

#include <numeric>
#include <stdexcept>

namespace Components
{
    CPUTab::CPUTab()
      : mCPUOrCoreCycle(MCC::ActionCycleBuilder().tagWeight(0).object(*this))
      , mCPUCountText(MUI::TextBuilder()
                          .tagShortHelp("Number of CPUs")
                          .tagContents("of " + std::to_string(0))
                          .tagWeight(0)
                          .object()) // TODO: set actual number of CPUs
      , mComponent(MUI::GroupBuilder()
                       .vertical()
                       .tagChild(MUI::MakeObject::HVSpace())
                       .tagChild(mCPUInfoGroup)
                       .tagChild(MUI::GroupBuilder()
                                     .horizontal()
                                     .tagFrame(MUI::Frame::Group)
                                     .tagChild(LabelText(MUIX_R "CPU"))
                                     .tagChild(mCPUOrCoreCycle)
                                     .tagChild(mCPUCountText)
                                     .tagChild(MUI::MakeObject::HVSpace())
                                     .object())
                       .tagChild(MUI::MakeObject::HVSpace())
                       .object())
    {
        mCPUInfoGroup.setActivePage(MUI::Group_ActivePage::First);
    }

    unsigned long CPUTab::OnCycle()
    {
        auto selection = mCPUOrCoreCycle.getActive();
        mCPUInfoGroup.setActivePage(selection);
        return 0;
    }
}
