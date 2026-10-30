//
//  CPU-R
//
//  (c) 2026 TDolphin
//

#include "AppContext.hpp"

#include "App.hpp"

#ifdef TRACE
#include "amiga_std_light/iostream.hpp"
#endif

AppContextCore::AppContextCore()
{
#ifdef TRACE
    std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
}

AppContextCore::~AppContextCore()
{
#ifdef TRACE
    std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
}

OpenURLBaseScope &AppContextCore::getOpenURLBase() const
{
    return App::instance().openUrlBaseScope;
}

IntuitionBaseScope &AppContextCore::getIntuitionBase() const
{
    return App::instance().intuitionBaseScope;
}
