#include <MeasurementStore.h>

namespace chronoscope
{

MeasurementStore& MeasurementStore::getInstance()
{
    static thread_local MeasurementStore sInstance;
    return sInstance;
}

} // namespace chronoscope
