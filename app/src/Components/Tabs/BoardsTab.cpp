//
//  CPU-R
//
//  (c) 2026 TDolphin
//

#include "BoardsTab.hpp"

#include "MUI/Core/MakeObject.hpp"

namespace Components
{
    BoardsTab::BoardsTab()
      : mBoardsList() // TODO: pass actual list of boards to constructor
      , mComponent(
            MUI::GroupBuilder()
                .vertical()
                .tagChild(mBoardsList)
                .tagChild(
                    MUI::TextBuilder().tagFont(MUI::Font::Tiny).tagContents(MUIX_L "Double click on list item to view board attributes.").object())
                .object())
    {
    }

    BoardsTab::~BoardsTab() { }
}
