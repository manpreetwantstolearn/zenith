#pragma once

#include "Job.h"

namespace zenith::execution {

class IThreadPool {
public:
    virtual ~IThreadPool() = default;
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual bool submit(Job job) = 0;
};

} // namespace zenith::execution
