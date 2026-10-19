//
//  CPU-R
//
//  (c) 2026 TDolphin
//

#pragma once

#include "AOS/Intuition/IntuitionBaseScope.hpp"
#include "AOS/OpenURL/OpenURLBaseScope.hpp"
#include "Core/Singleton.hpp"
#include "MUI/Core/MuiMasterBaseScope.hpp"

class AppContextCore;

class AppCore
{
    friend class td::Singleton<AppCore>;
    friend class AppContextCore;

    // open libraries, close on destructor
    MuiMasterBaseScope muiBaseScope;
    OpenURLBaseScope openURLBaseScope;
    IntuitionBaseScope intuitionBaseScope;

    AppCore();

  public:
    void Run();
};

/// @brief main Application (singleton) object
typedef class td::Singleton<AppCore> App;
