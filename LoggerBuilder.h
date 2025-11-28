#pragma once
#include <Logger.h>
#include <sstream>

namespace chronoscope
{

class LoggerBuilder
{
public:

    /**
     * Construct a logger builder with basic information.
     * \param[in] file: Filename for the logger.
     * \param[in] line: Line number for the logger.
     * \param[in] function: Function name for the logger.
     * \post The builder is ready to construct a logger.
     */
    LoggerBuilder(const char *file,
                  std::size_t line,
                  const char *function);

    /**
     * Extend the label of the logger being built.
     * \param[in] value: Value to extend the logger label with.
     * \return Reference to this builder.
     */
    template <class T>
    inline LoggerBuilder& operator<<(const T &value)
    {
        _labelStream << value;
        return *this;
    }

    /**
     * Add tags to the logger being built.
     * \param[in] tags: The tags to add to the logger.
     * \return Reference to this builder.
     */
    LoggerBuilder& operator<<(const Tags &tags);

    /**
     * Add metadata to the logger being built.
     * \param[in] metadata: The metadata to add to the logger.
     * \return Reference to this builder.
     */
    LoggerBuilder& operator<<(const Metadata &metadata);

    /**
     * Finalize and create the logger from the previous configuration.
     * \return The new logger instance with the previous configuration.
     * \post The builder becomes unusable after finalization.
     */
    Logger finalize();

    /**
     * Finalize and create the logger.
     * \see LoggerBuilder::finalize
     */
    inline operator Logger() &&
    { return finalize(); }

private:
    std::string _file;
    std::size_t _line;
    std::string _function;
    std::ostringstream _labelStream;
    Tags _tags;
    Metadata _metadata;
    bool _isFinalized;
};

} // namespace chronoscope
