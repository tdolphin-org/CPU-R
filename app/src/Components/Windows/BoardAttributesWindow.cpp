//
//  CPU-R
//
//  (c) 2026 TDolphin
//

#include "BoardAttributesWindow.hpp"

#include "Components/IDs.hpp"
#include "MUI/Core/MakeObject.hpp"
#include "MUI/Notifier/Notifier.hpp"
#include "Version.hpp"

namespace Components
{
    BoardAttributesWindow::BoardAttributesWindow()
      : mVendor(ValueText("Vendor name", "--", true))
      , mDevice(ValueText("Device name", "--", true))
      , mClass(ValueText("Class name", "--", true))
      , mHeaderGroup(MUI::GroupBuilder()
                         .horizontal()
                         .tagColumns(2)
                         .tagChild(LabelText(MUIX_R "Vendor:"))
                         .tagChild(mVendor)
                         .tagChild(LabelText(MUIX_R "Device:"))
                         .tagChild(mDevice)
                         .tagChild(LabelText(MUIX_R "Class:"))
                         .tagChild(mClass)
                         .object())
      , mComponent(MUI::WindowBuilder()
                       .tagTitle("Board Attributes")
                       .tagScreenTitle(SCREEN_TITLE)
                       .tagID(WindowID::BoardAttributesWindow)
                       .tagWidth(400)
                       .tagHeight(500)
                       .tagAltWidth(600)
                       .tagAltHeight(600)
                       .tagRootObject(MUI::GroupBuilder()
                                          .vertical()
                                          .tagChild(MUI::MakeObject::HVSpace())
                                          .tagChild(mHeaderGroup)
                                          .tagChild(MUI::MakeObject::HVSpace())
                                          .object())
                       .object())
    {
        // window "X" button => close window
        MUI::Notifier::from(mComponent).onCloseRequest(true).notifySelf().setOpen(false);
    }

    void BoardAttributesWindow::Open(const BoardInfo &boardInfo)
    {
        mVendor.setContents(boardInfo.vendor);
        mDevice.setContents(boardInfo.device);
        mClass.setContents(boardInfo.className);

        if (mComponent.isOpen())
            return;

        mComponent.Open();
    }

    void BoardAttributesWindow::Close()
    {
        mComponent.Close();
    }
}
