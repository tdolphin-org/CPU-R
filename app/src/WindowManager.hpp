//
//  CPU-R
//
//  (c) 2026 TDolphin
//

#pragma once

#include "Components/Windows/BoardAttributesWindow.hpp"
#include "Components/Windows/BusInterfacesSpecWindow.hpp"
#include "Core/Singleton.hpp"
#include "MUI/Window.hpp"

#include <vector>

/// @brief holds windows (components)
class WindowManagerCore
{
    friend class td::Singleton<WindowManagerCore>;

    Components::BusInterfacesSpecWindow mBusInterfacesSpecWindow;
    Components::BoardAttributesWindow mBoardAttributesWindow;

    std::vector<MUI::Window> mAllWindows;

    WindowManagerCore();
    ~WindowManagerCore();

  public:
    const std::vector<MUI::Window> &getAllWindows() const;

    Components::BusInterfacesSpecWindow &getBusInterfacesSpecWindow()
    {
        return mBusInterfacesSpecWindow;
    }

    Components::BoardAttributesWindow &getBoardAttributesWindow()
    {
        return mBoardAttributesWindow;
    }
};

/// @brief main Window Manager (singleton) object
typedef class td::Singleton<WindowManagerCore> WindowManager;
