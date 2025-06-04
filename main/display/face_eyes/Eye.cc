#include "Eye.h"

Eye::Eye() : container_(nullptr), pupil_(nullptr), eyelid_(nullptr), position_({0,0}), eye_container_({0,0,0}), pupil_container_({0,0,0}) {}

void Eye::create(lv_obj_t* parent, const std::vector<lv_coord_t>& position, const std::vector<int32_t>& eye_container, const std::vector<int32_t>& pupil_container, const bool is_oled) {
    position_ = position;
    eye_container_ = eye_container;
    pupil_container_ = pupil_container;
    is_oled_ = is_oled;

    container_ = lv_obj_create(parent);
    lv_obj_set_size(container_, eye_container_[0], eye_container_[1]);
    lv_obj_set_style_pad_all(container_, 0, 0);
    lv_obj_set_style_radius(container_, eye_container_[2], 0);
    lv_obj_set_style_bg_color(container_, is_oled_ ? lv_color_white() : lv_color_black(), 0);
    lv_obj_set_style_border_width(container_, 0, 0);
    lv_obj_clear_flag(container_, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_align(container_, LV_ALIGN_TOP_LEFT, position_[0], position_[1]);

    pupil_ = lv_obj_create(container_);
    lv_obj_set_size(pupil_, pupil_container_[0], pupil_container_[1]);
    lv_obj_set_style_pad_all(pupil_, 0, 0);
    lv_obj_set_style_radius(pupil_, pupil_container_[2], 0);
    lv_obj_set_style_bg_color(pupil_, is_oled_ ? lv_color_black() : lv_color_white(), 0);
    lv_obj_set_style_border_width(pupil_, 0, 0);
    lv_obj_align(pupil_, LV_ALIGN_CENTER, 0, 0);

    eyelid_ = lv_obj_create(container_);
    lv_obj_set_size(eyelid_, eye_container_[0], eye_container_[1]);
    lv_obj_set_style_radius(eyelid_, eye_container_[2], 0);
    lv_obj_set_style_bg_color(eyelid_, is_oled_ ? lv_color_white() : lv_color_black(), 0);
    lv_obj_set_style_border_width(eyelid_, 0, 0);
    lv_obj_align(eyelid_, LV_ALIGN_TOP_MID, 0, -eye_container_[1]);
}

void Eye::movePupil(int dx, int dy) {
    const int x_offset = eye_container_[0] - pupil_container_[0];
    const int y_offset = eye_container_[1] - pupil_container_[1];
    const int max_offset = x_offset > y_offset ? y_offset / 2 : x_offset / 2;
    if (dx > max_offset) dx = max_offset;
    if (dx < -max_offset) dx = -max_offset;
    if (dy > max_offset) dy = max_offset;
    if (dy < -max_offset) dy = -max_offset;

    lv_obj_align(pupil_, LV_ALIGN_CENTER, dx, dy);
}

void Eye::blink() {
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, eyelid_);
    lv_anim_set_values(&a, -eye_container_[1], 0);
    lv_anim_set_time(&a, 150);
    lv_anim_set_exec_cb(&a, blinkCallback);
    lv_anim_start(&a);

    lv_anim_t a2;
    lv_anim_init(&a2);
    lv_anim_set_var(&a2, eyelid_);
    lv_anim_set_values(&a2, 0, -eye_container_[1]);
    lv_anim_set_time(&a2, 150);
    lv_anim_set_delay(&a2, 200);
    lv_anim_set_exec_cb(&a2, blinkCallback);
    lv_anim_start(&a2);
}

void Eye::blinkCallback(void* eyelid, int32_t v) {
    lv_obj_set_y((lv_obj_t*)eyelid, v);
}