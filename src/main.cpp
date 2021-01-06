#include "main.hpp"

static ModInfo modInfo;

Configuration& getConfig() {
    static Configuration config(modInfo);
    config.Load();
    return config;
}

const Logger& getLogger() {
    static const Logger logger(modInfo);
    return logger;
}

extern "C" void setup(ModInfo& info) {
    info.id = "practice_skipper";
    info.version = VERSION;
    modInfo = info;
}

extern "C" void load() {
    if (!LoadConfig()) SaveConfig();

    il2cpp_functions::Init();
    QuestUI::Init();

    custom_types::Register::RegisterType<PracticeSkipper::ModSettingsViewController>();
    QuestUI::Register::RegisterModSettingsViewController<PracticeSkipper::ModSettingsViewController*>((ModInfo){"Practice Skipper", VERSION}, "Practice Skipper");

    PracticeSkipper::InstallHooks();

    getLogger().info("Load complete!");
}
