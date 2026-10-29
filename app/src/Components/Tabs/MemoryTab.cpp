//
//  CPU-R
//
//  (c) 2026 TDolphin
//

#include "MemoryTab.hpp"

#include "AOS/Exec/Library.hpp"
#include "Core/ToString.hpp"
#include "MUI/Core/MakeObject.hpp"

namespace Components
{
    MemoryTab::MemoryTab()
      : mTotalSystemMemoryText(ValueText("Total System Memory"))
      , mComponent(MUI::GroupBuilder()
                       .vertical()
                       .tagChild(MUI::MakeObject::HVSpace())
                       .tagChild(MUI::GroupBuilder()
                                     .tagFrame(MUI::Frame::Group)
                                     .tagFrameTitle("System Memory")
                                     .tagColumns(2)
                                     .tagChild(LabelText(MUIX_R "Total Size:"))
                                     .tagChild(mTotalSystemMemoryText)
                                     .object())
                       .tagChild(MUI::MakeObject::HVSpace())
                       .object())
    {
        mTotalSystemMemoryText.setContents(ToString::FromBytesValue(
            AOS::Exec::Library::libAvailMem(AOS::Exec::MEMF_Type::ANY, AOS::Exec::MEMF_Avail::TOTAL), MemorySizeUnit::MegaBytes));
    }
}
