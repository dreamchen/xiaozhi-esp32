#include "EyesManager.h"

Eye EyesManager::leftEye;
Eye EyesManager::rightEye;

void EyesManager::start(lv_obj_t* scr, const std::vector<std::vector<lv_coord_t>>& positions, const std::vector<int32_t>& eye_container, const std::vector<int32_t>& pupil_container, bool is_oled) {
    leftEye.create(scr, positions[0], eye_container, pupil_container, is_oled);
    rightEye.create(scr, positions[1], eye_container, pupil_container, is_oled);

    lv_timer_create(timerCallback, 1500, NULL);
}

void EyesManager::timerCallback(lv_timer_t* timer) {
    static int dx = 0, dy = 0;
    static int dir = 0;

    switch (dir) {
        case 0: dx = 10; dy = 0; break;  // Right
        case 1: dx = -10; dy = 0; break; // Left
        case 2: dx = 0; dy = -10; break; // Up
        case 3: dx = 0; dy = 10; break;  // Down
    }

    leftEye.movePupil(dx, dy);
    rightEye.movePupil(dx, dy);

    if (dir % 2 == 0) {
        leftEye.blink();
        rightEye.blink();
    }

    dir = (dir + 1) % 4;
}