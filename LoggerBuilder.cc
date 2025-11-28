#include <LoggerBuilder.h>

namespace chronoscope
{

LoggerBuilder::LoggerBuilder(const char *file,
                             std::size_t line,
                             const char *function)
    : _file{file},
      _line{line},
      _function{function},
      _labelStream{},
      _tags{},
      _metadata{},
      _isFinalized{false}
{ }

LoggerBuilder& LoggerBuilder::operator<<(const Tags &tags)
{

}

LoggerBuilder& LoggerBuilder::operator<<(const Metadata &metadata)
{

}

Logger LoggerBuilder::finalize()
{
    if (_isFinalized)
    {
        throw std::runtime_error("Attempting to finalize a LoggerBuilder that has "
                                 "already been finalized before");
    }

    _isFinalized = true;
    return Logger{std::move(_labelStream.str()),
                  std::move(_tags),
                  std::move(_metadata),
                  std::move(_file),
                  _line,
                  std::move(_function)};
}

} // namespace chronoscope
