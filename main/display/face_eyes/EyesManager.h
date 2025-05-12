#ifndef EYES_MANAGER_H
#define EYES_MANAGER_H

#include "Eye.h"

class EyesManager {
public:
    static void start(lv_obj_t* scr,
    const std::vector<std::vector<lv_coord_t>>& positions ={{60, 60}, {120, 60}},
    const std::vector<int32_t>& eye_container = {60L, 60L, 15L},
    const std::vector<int32_t>& pupil_container = {40L, 40L, 10L},
    const bool is_oled = false);
    
private:
    static Eye leftEye;
    static Eye rightEye;
    static void timerCallback(lv_timer_t* timer);
};

#endif // EYES_MANAGER_H