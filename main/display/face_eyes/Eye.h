#ifndef EYE_H
#define EYE_H

#include "lvgl.h"
#include <vector>

class Eye {
public:
    Eye();

    void create(lv_obj_t* parent, const std::vector<lv_coord_t>& position, const std::vector<int32_t>& eye_container, const std::vector<int32_t>& pupil_container, const bool is_oled = false);
    void movePupil(int dx, int dy);
    void blink();

private:
    lv_obj_t* container_;
    lv_obj_t* pupil_;
    lv_obj_t* eyelid_;
    std::vector<lv_coord_t> position_;
    std::vector<int32_t> eye_container_;
    std::vector<int32_t> pupil_container_;
    bool is_oled_;

    static void blinkCallback(void* eyelid, int32_t v);
};

#endif // EYE_H