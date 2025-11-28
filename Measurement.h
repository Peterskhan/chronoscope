#pragma once
#include <Logger.h>
#include <thread>
#include <unistd.h>

namespace chronoscope
{

/**
 * Portable macro for identifying the current function,
 * depending on the compiler being used.
 * \def CHRONO_FUNCTION
 */
#if defined(__GNUC__) || defined(__clang__)
    #define CHRONO_FUNCTION __PRETTY_FUNCTION__
#elif defined(_MSC_VER)
    #define CHRONO_FUNCTION __FUNCSIG__
#else
    #define CHRONO_FUNCTION __func__
#endif

using TimePoint = std::chrono::high_resolution_clock::time_point;
using LoggerId = std::size_t;

/**
 * Wrapper class for representing logger tags.
 */
class Tags
{
public:
    using StorageType = std::vector<std::string>;

    /**
     *
     */
    Tags(std::initializer_list<std::string> tags);

    /**
     *
     */
    explicit Tags(StorageType tags);

    /**
     * Access the underlying tag storage (read-only).
     */
    inline const StorageType& get() const
    { return _tags; }

private:
    StorageType _tags;
};

/**
 * Helper function to create logger tags.
 * \param[in] _tags: List of strings to create as tags.
 * \return Wrapper containing the list of specified tags.
 */
Tags tags(std::initializer_list<std::string> _tags);

/**
 * Wrapper class for representing logger metadata.
 */
class Metadata
{
public:
    using MetadataValue = std::variant<bool, int, double, std::string>;
    using StorageType = std::unordered_map<std::string, MetadataValue>;

    /**
     *
     */
    Metadata(std::initializer_list<std::pair<const std::string, MetadataValue>> items);

    /**
     *
     */
    explicit Metadata(StorageType metadata);

    /**
     * Access the underlying meatadata storage (read-only).
     */
    inline const StorageType& get() const
    { return _metadata; }

private:
    StorageType _metadata;
};

/**
 * Helper function to create logger metadata.
 * \param[in] items: List of key-value pairs.
 * \return Wrapper containing the specified metadata.
 */
template <class... Args>
inline Metadata metadata(Args&&... items)
{
    return Metadata{{std::forward<Args>(items)...}};
}

/**
 * Represents a measurement performed by a Logger.
 */
struct Measurement
{
    /**
     * The textual label for the measurement.
     * This can be used to identify the thing being measured.
     */
    std::string label;

    /**
     * The file where the measurement is started.
     * Usually the value of the __FILE__ macro.
     */
    std::string file;

    /**
     * The line number where the measurement is started.
     * Usually the value of the __LINE__ macro.
     */
    std::size_t line;

    /**
     * The function name where the measurement is started.
     * Compiler specific, the value of the __func__ identifier
     * is used as a fallback solution.
     */
    std::string function;

    /**
     * Point in time where the measurement is started.
     * Precision is implementation specific, usually ~nanoseconds.
     */
    TimePoint startTime;

    /**
     * Point in time where the measurement is stopped.
     * Precision is implementation specific, usually ~nanoseconds.
     */
    TimePoint endTime;

    /**
     * The unique identifier of the logger taking the measurement.
     */
    LoggerId id;

    /**
     * The unique identifier of the parent of the logger taking the measurement.
     */
    LoggerId parentId;

    /**
     * Tags for the measurement.
     * These are optional string values that enable grouping of measurements.
     */
    Tags tags;

    /**
     * Metadata for the measurements.
     * These are key-value pairs that enable adding additional context for measurements.
     */
    Metadata metadata;

    /**
     * The unique identifier of thread where the measurement is taken.
     */
    std::thread::id threadId;

    /**
     * The unique identifier of the process where the measurement is taken.
     */
    pid_t processId;
};

} // namespace chronoscope
