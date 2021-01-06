#pragma once

#include "beatsaber-hook/shared/utils/logging.hpp"

const Logger& getLogger();

#define _LOG_DEBUG(m...) getLogger().debug(std::string(__func__) + " (" + std::string(__FILE__) + ":" + std::to_string(__LINE__) + ")" + m)
#define LOG_DEBUG(m...) _LOG_DEBUG(": " + m)
#define LOG_CALLER _LOG_DEBUG("")
