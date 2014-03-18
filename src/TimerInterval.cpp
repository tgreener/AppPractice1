
#include "TimerInterval.h"

TimerInterval::TimerInterval(dispatch_source_t di) : dispatchInterval(di) {}

void TimerInterval::cancel() {
    dispatch_source_cancel(dispatchInterval);
}
