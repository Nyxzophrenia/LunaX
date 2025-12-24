#pragma once

class Time {
public:
    // TODO: Update delta time every frame
    static void Update();

    // TODO: Return delta time
    static double Delta();

    // TODO: Support fixed timestep override
    // TODO: Support time scaling (slow/fast)
private:
    static double s_LastTime;
    static double s_DeltaTime;
};
