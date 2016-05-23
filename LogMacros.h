#pragma once

#include "Logger.h"

#define NEW_LOG_TRACE(message) CLogger::log(logTrace, __LINE__, message, __FILE__);
#define NEW_LOG_DEBUG(message) CLogger::log(logDebug, __LINE__, message, __FILE__);
#define NEW_LOG_WARNING(message) CLogger::log(logWarning, __LINE__, message, __FILE__);
#define NEW_LOG_ERROR(message) CLogger::log(logError, __LINE__, message, __FILE__);
#define SET_LEVEL(level) CLogger::setLevel(level)