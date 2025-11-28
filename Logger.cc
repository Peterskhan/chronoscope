#include <Logger.h>
#include <MeasurementStore.h>

namespace chronoscope
{

Logger::Logger(std::string label,
               Tags tags,
               Metadata metadata,
               std::string file,
               std::size_t line,
               std::string function)
    : _pMeasurement{nullptr},
      _isActive{true} // TODO
{
    if (_isActive)
    {
        _pMeasurement = &MeasurementStore::getInstance().createMeasurement(
            std::move(label),
            std::move(tags),
            std::move(metadata),
            std::move(file),
            line,
            std::move(function)
        );
    }
}

Logger::Logger(Logger &&other)
    : _pMeasurement{other._pMeasurement},
      _isActive{other._isActive}
{
    other.stop(); // TODO???
    other._pMeasurement = nullptr;
    other._isActive = false;
}

Logger& Logger::operator=(Logger &&other)
{
    // TODO???
}

Logger::~Logger()
{
    if (_isActive)
    {
        stop();
    }
}

void Logger::stop()
{

}

void Logger::addTags(Tags &&tags)
{

}

void Logger::addMetadata(Metadata &&metadata)
{

}

} // namespace chronoscope
