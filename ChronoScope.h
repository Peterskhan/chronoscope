#pragma once
#include <Logger.h>
#include <LoggerBuilder.h>

#define CHRONO_SCOPE_CONCAT(var, line) \
  var##line

/**
 * Helper macro for building an anonymous logger.
 * \def CHRONO_SCOPE
 */
#define CHRONO_SCOPE() \
    chronoscope::Logger CHRONO_SCOPE_CONCAT(__chrono_scope_, __LINE__) \
        = chronoscope::LoggerBuilder(__FILE__, __LINE__, CHRONO_FUNCTION)

/**
 * Helper macro for building a named logger.
 * \def CHRONO_SCOPE_NAMED
 */
#define CHRONO_SCOPE_NAMED(name) \
    chronoscope::Logger name \
        = chronoscope::LoggerBuilder(__FILE__, __LINE__, CHRONO_FUNCTION)

namespace chronoscope
{



} // namespace chronoscope
