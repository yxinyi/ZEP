#pragma once

#define MgrRegHelper(mgr_name_)                                   \
class static_mgr_helper_##mgr_name_{                              \
public:                                                           \
    static_mgr_helper_##mgr_name_();                              \
};                                                                \
static static_mgr_helper_##mgr_name_ _mgr_init_helper_obj;        \
static_mgr_helper_##mgr_name_::static_mgr_helper_##mgr_name_##()

