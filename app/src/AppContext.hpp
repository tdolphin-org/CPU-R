//
//  CPU-R
//
//  (c) 2026 TDolphin
//

#pragma once

#include "AOS/Intuition/IntuitionBaseScope.hpp"

class AppContextCore
{
    friend class td::Singleton<AppContextCore>;

    AppContextCore();
    ~AppContextCore();

  public:
    IntuitionBaseScope &getIntuitionBase() const;
};

/// @brief main AppContext (singleton) object
typedef class td::Singleton<AppContextCore> AppContext;
