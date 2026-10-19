//
//  CPU-R
//
//  (c) 2026 TDolphin
//

#pragma once

#include "AOS/Intuition/IntuitionBaseScope.hpp"
#include "AOS/OpenURL/OpenURLBaseScope.hpp"

class AppContextCore
{
    friend class td::Singleton<AppContextCore>;

    AppContextCore();
    ~AppContextCore();

  public:
    OpenURLBaseScope &getOpenURLBase() const;
    IntuitionBaseScope &getIntuitionBase() const;
};

/// @brief main AppContext (singleton) object
typedef class td::Singleton<AppContextCore> AppContext;
