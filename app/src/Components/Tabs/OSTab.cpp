//
//  CPU-R
//
//  (c) 2026 TDolphin
//

#include "OSTab.hpp"

#include "AOS/Dos/Library.hpp"
#include "AOS/Exec/Library.hpp"
#include "AppContext.hpp"
#include "Core/StringUtils.hpp"
#include "MUI/Core/MakeObject.hpp"
#include "MUI/Listview.hpp"
#include "ProgDefines.hpp"

namespace Components
{
    OSTab::OSTab()
      : mFullOSNameText(ValueText("Full name of Operating System and version, copyrights etc", "--", true))
      , mUserText(ValueText("Current user login (env variable USER)"))
      , mUserLoginText(ValueText("Current user login (env variable LOGNAME)"))
      , mUserHomePathText(ValueText("Current user home path (env variable HOME)"))
      , mKickstartVersionText(ValueText("Kickstart Version"))
      , mExecVersionText(ValueText("Exec Version"))
      , mAmbientVersionText(ValueText("Ambient Version", "--"))
      , mWorkbenchVersionText(ValueText("Workbench Version"))
      , mTimeZoneText(ValueText("Current time zone"))
      , mCodePageText(ValueText("Current code page"))
      , mLocaleText(ValueText("Current locale"))
      , mLoadedLibrariesList(MUI::ListBuilder()
                                 .tagFrame(MUI::Frame::ReadList)
                                 .tagConstructHookString()
                                 .tagDestructHookString()
                                 .tagFormat("BAR,")
                                 .tagTitle(false)
                                 .object())
      , mLoadedDevicesList(
            MUI::ListBuilder().tagFrame(MUI::Frame::ReadList).tagConstructHookString().tagDestructHookString().tagFormat("BAR,").object())
      , mLoadedDatatypesList(MUI::ListBuilder()
                                 .tagFrame(MUI::Frame::ReadList)
                                 .tagConstructHookString()
                                 .tagDestructHookString()
                                 .tagFormat("BAR,")
                                 .tagTitle(false)
                                 .object())
      , mLoadedMUIList(MUI::ListBuilder()
                           .tagFrame(MUI::Frame::ReadList)
                           .tagConstructHookString()
                           .tagDestructHookString()
                           .tagFormat("BAR,")
                           .tagTitle(false)
                           .object())
      , mLoadedResourcesList(MUI::ListBuilder().tagFrame(MUI::Frame::ReadList).tagConstructHookString().tagDestructHookString().object())
      , mLoadedOtherList(MUI::ListBuilder()
                             .tagFrame(MUI::Frame::ReadList)
                             .tagConstructHookString()
                             .tagDestructHookString()
                             .tagFormat("BAR,")
                             .tagTitle(false)
                             .object())
      , mExecNodesTabs({
            { "Libraries", mLoadedLibrariesList },
            { "Devices", mLoadedDevicesList },
            { "Datatypes", mLoadedDatatypesList },
            { "MUI", mLoadedMUIList },
            { "Resources", mLoadedResourcesList },
            { "Other", mLoadedOtherList },
        })
      , mComponent(MUI::GroupBuilder()
                       .vertical()
                       .tagChild(MUI::GroupBuilder()
                                     .tagFrame(MUI::Frame::Group)
                                     .tagFrameTitle("Operating System")
                                     .tagChild(mFullOSNameText)
                                     .tagChild(MUI::GroupBuilder()
                                                   .tagColumns(8)
                                                   .tagChild(LabelText(MUIX_R "User:"))
                                                   .tagChild(mUserText)
                                                   .tagChild(LabelText(MUIX_R "Login:"))
                                                   .tagChild(mUserLoginText)
                                                   .tagChild(LabelText(MUIX_R "Home path:"))
                                                   .tagChild(mUserHomePathText)
                                                   .tagChild(LabelText(MUIX_R "Kickstart:"))
                                                   .tagChild(mKickstartVersionText)
                                                   .tagChild(LabelText(MUIX_R "Exec:"))
                                                   .tagChild(mExecVersionText)
                                                   .tagChild(LabelText(MUIX_R "Ambient:"))
                                                   .tagChild(mAmbientVersionText)
                                                   .tagChild(LabelText(MUIX_R "Workbench:"))
                                                   .tagChild(mWorkbenchVersionText)
                                                   .tagChild(LabelText(MUIX_R "Time Zone:"))
                                                   .tagChild(mTimeZoneText)
                                                   .tagChild(LabelText(MUIX_R "Locale:"))
                                                   .tagChild(mLocaleText)
                                                   .tagChild(LabelText(MUIX_R "Code Page:"))
                                                   .tagChild(mCodePageText)
                                                   .tagChild(MUI::MakeObject::HVSpace())
                                                   .tagChild(MUI::MakeObject::HVSpace())
                                                   .object())
                                     .object())
                       .tagChild(MUI::MakeObject::CLabel("Loaded Exec Nodes"))
                       .tagChild(mExecNodesTabs)
                       .object())
    {
        // user related
        auto user = AOS::Dos::Library::libGetVar("USER");
        mUserText.setContents(user.has_value() ? user.value() : "--");
        auto login = AOS::Dos::Library::libGetVar("LOGNAME");
        mUserLoginText.setContents(login.has_value() ? login.value() : "--");
        auto home = AOS::Dos::Library::libGetVar("HOME");
        mUserHomePathText.setContents(home.has_value() ? home.value() : "--");

        // kickstart version and others
        auto kickstart = AOS::Dos::Library::libGetVar("Kickstart");
        mKickstartVersionText.setContents(kickstart.has_value() ? "v" + StringUtils::Split(kickstart.value()).back() : "??");

        auto workbench = AOS::Dos::Library::libGetVar("Workbench");
        mWorkbenchVersionText.setContents(workbench.has_value() ? "v" + StringUtils::Split(workbench.value()).back() : "--");

        auto timezone = AOS::Dos::Library::libGetVar("TZ");
        mTimeZoneText.setContents(timezone.has_value() ? timezone.value() : "--");
        auto codepage = AOS::Dos::Library::libGetVar("CODEPAGE");
        mCodePageText.setContents(codepage.has_value() ? codepage.value() : "--");
        auto locale = AOS::Dos::Library::libGetVar("Language");
        mLocaleText.setContents(locale.has_value() ? locale.value() : "--");

        mExecVersionText.setContents("v" + AOS::Exec::Library::GetVersion());

        auto isLibrary = [](const AOS::Exec::NodeInfo &node) -> bool { return StringUtils::hasSuffix(node.name, ".library"); };
        auto isDatatype = [](const AOS::Exec::NodeInfo &node) -> bool {
            return StringUtils::hasSuffix(node.name, { ".datatype", ".decoder", ".encoder" });
        };
        auto isMUI = [](const AOS::Exec::NodeInfo &node) -> bool { return StringUtils::hasSuffix(node.name, { ".mui", ".mcc" }); };

        mLoadedLibrariesList.setQuiet(true);
        mLoadedDatatypesList.setQuiet(true);
        mLoadedMUIList.setQuiet(true);
        mLoadedOtherList.setQuiet(true);

        auto allLibraries = AOS::Exec::Library::GetAllLibraryNodeNames();
        for (const auto &entry : allLibraries)
        {
            std::string version = entry.version.has_value() ? entry.version.value() : "??";
            const char *arr[] = { entry.name.c_str(), version.c_str(), nullptr };
            if (isLibrary(entry))
                mLoadedLibrariesList.InsertSingleSorted(arr);
            else if (isDatatype(entry))
                mLoadedDatatypesList.InsertSingleSorted(arr);
            else if (isMUI(entry))
                mLoadedMUIList.InsertSingleSorted(arr);
            else
                mLoadedOtherList.InsertSingleSorted(arr);
        }

        mLoadedLibrariesList.setQuiet(false);
        mLoadedDatatypesList.setQuiet(false);
        mLoadedMUIList.setQuiet(false);
        mLoadedOtherList.setQuiet(false);

        mLoadedDevicesList.setQuiet(true);
        auto allDevices = AOS::Exec::Library::GetAllDeviceNodeNames();
        for (const auto &entry : allDevices)
        {
            std::string version = entry.version.has_value() ? entry.version.value() : "??";
            const char *arr[] = { entry.name.c_str(), version.c_str(), nullptr };
            mLoadedDevicesList.InsertSingleSorted(arr);
        }
        mLoadedDevicesList.setQuiet(false);

        auto allResources = AOS::Exec::Library::GetAllResourceNodeNames();
        mLoadedResourcesList.InsertSorted([&]() -> std::vector<std::string> {
            std::vector<std::string> result;
            for (const auto &entry : allResources)
                result.push_back(entry.name);
            return result;
        }());
    }
}
