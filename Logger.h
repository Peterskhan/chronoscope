#pragma once
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>
#include <Measurement.h>

namespace chronoscope
{

/**
 *
 */
class Logger
{
public:

    /**
     * Construct a logger with some initial data.
     * \param[in] label: The label for the logger.
     * \param[in] tags: The tags for the logger.
     * \param[in] metadata: The metadata for the logger.
     * \param[in] file: Filename where the logger is created.
     * \param[in] line: Line number where the logger is created.
     * \param[in] function: Function name where the logger is created.
     * \post The logger is made active and starts measuring.
     */
    Logger(std::string label,
           Tags tags = {},
           Metadata metadata = {},
           std::string file = "",
           std::size_t line = 0U,
           std::string function = "");

    /**
     * Loggers can not be copy constructed.
     * \param[in] other: Not used.
     */
    Logger(const Logger &other) = delete;

    /**
     * Construct a logger by moving from another.
     * \param[in] other: The other logger to move from.
     * \post The other logger becomes inactive.
     */
    Logger(Logger &&other);

    /**
     * Loggers can not be copy assigned.
     * \param[in] other: Not used.
     * \return Not used.
     */
    Logger& operator=(const Logger &other) = delete;

    /**
     * Assign this logger by moving from another.
     * \param[in] other: The other logger to move from.
     * \post The other logger becomes inactive.
     */
    Logger& operator=(Logger &&other);

    /**
     * Destroy the logger and stop it if not already stopped.
     * \throw Rethrows any exception emitted from \see Logger::stop.
     * \post The logger is destroyed and measurement results
     *       are submitted to the \see MeasurementStore.
     */
    ~Logger();

    /**
     * Check whether the logger is currently measuring.
     * \return True when the logger is active, false otherwise.
     */
    inline bool isRunning() const noexcept
    { return _isActive; }

    /**
     * Stop the measurement of the logger.
     * \pre The logger has to be running.
     * \throw TODO
     * \post The logger is made inactive.
     */
    void stop();

    /**
     * Add tags to the logger after construction.
     * \param[in] tags: The tags to be added to the logger.
     */
    void addTags(Tags &&tags);

    /**
     * Add metadata to the logger after construction.
     * \param[in] key: The key for the metadata to add.
     * \param[in] value: The value for the metadata to add.
     */
    template <class T>
    inline void addMetadata(const std::string &key, const T& value)
    { addMetadata(std::move(metadata({key, value}))); }

    /**
     * Add metadata to the logger after construction.
     * \param[in] metadata: The metadata to add.
     */
    void addMetadata(Metadata &&metadata);

private:
    Measurement *_pMeasurement;
    bool _isActive;
};

} // namespace chronoscope
