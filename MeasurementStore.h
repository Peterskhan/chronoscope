#pragma once
#include <Measurement.h>

namespace chronoscope
{

/**
 *
 */
enum class FlushPolicy
{
    Immediate
};

/**
 *
 */
class MeasurementStore
{
public:

    /**
     * Get the thread-local instance of the MeasurementStore.
     * \return Reference to the thread-local MeasurementStore.
     */
    static MeasurementStore& getInstance();

    /**
     * Create a new ongoing measurement.
     * \return Reference to the created measurement.
     */
    Measurement& createMeasurement();

    /**
     * Submit a finished measurement.
     */
    void submitMeasurement();

    /**
     * Flush the accumulated measurements immediately.
     */
    void flush();

private:

};

} // namespace chronoscope
