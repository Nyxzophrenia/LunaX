#include "Time.h"
#include <chrono>
#include <iostream>

double Time::s_LastTime = 0.0;
double Time::s_DeltaTime = 0.0;

void Time::Update()
{
    using namespace std::chrono;
    static auto last = high_resolution_clock::now();
    auto now = high_resolution_clock::now();
    s_DeltaTime = duration<double>(now - last).count();
    last = now;

    // TODO: Clamp delta to avoid simulation spikes
    if (s_DeltaTime > 0.1)
        s_DeltaTime = 0.1;
}

double Time::Delta()
{
    return s_DeltaTime;
}