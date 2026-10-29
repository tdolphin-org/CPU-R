//
//  CPU-R
//
//  (c) 2026 TDolphin
//

#include "GraphicsBoards.hpp"

#ifdef TRACE
#include "amiga_std_light/iostream.hpp"
#endif

#include "amiga_std_light/sstream.hpp"
#include <algorithm>
#include <iomanip>

namespace Components
{
    GraphicsBoards::GraphicsBoards()
      : mComponent(
            MUI::GroupBuilder().vertical().tagFrame(MUI::Frame::Group).tagFrameTitle("Mounted Devs Monitor(s) / Graphics Card(s)").object())
    {
    }

    GraphicsBoards::~GraphicsBoards()
    {
    }
}
