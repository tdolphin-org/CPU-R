//
//  CPU-R
//
//  (c) 2026 TDolphin
//

#include "MainMenu.hpp"

#include "Events/AppEventType.hpp"
#include "MUI/Menuitem.hpp"
#include "TextResources/Labels.hpp"

//
// CPU-R
// +-- About...
// +======
// +-- Quit
//
// Settings
// +-- MUI...
//

namespace Components
{
    MainMenu::MainMenu()
      : mCPURMenu(MUI::MenuBuilder()
                      .tagTitle(Label::MenuCPUR)
                      .tagChild(MUI::MenuitemBuilder()
                                    .tagUserData(static_cast<unsigned long>(AppEventType::OnMenuAbout))
                                    .tagTitle(Label::MenuAbout)
                                    .object())
                      .tagChild(MUI::MenuItemFactory().Separator())
                      .tagChild(MUI::MenuitemBuilder().tagUserData(MUIV_Application_ReturnID_Quit).tagTitle(Label::MenuQuit).object())
                      .object())
      , mSettingsMenu(MUI::MenuBuilder()
                          .tagTitle(Label::MenuSettings)
                          .tagChild(MUI::MenuitemBuilder()
                                        .tagUserData(static_cast<unsigned long>(AppEventType::OnMenuMUISettings))
                                        .tagTitle(Label::MenuMUISettings)
                                        .object())
                          .object())
      , mComponent(MUI::MenustripBuilder().tagChild(mCPURMenu).tagChild(mSettingsMenu).object())
    {
    }
}