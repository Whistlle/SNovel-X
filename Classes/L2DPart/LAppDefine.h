/**
 *
 *  You can modify and use this source freely
 *  only for the development of application related Live2D.
 *
 *  (c) Live2D Inc. All rights reserved.
 */
#pragma once



static const float VIEW_MAX_SCALE = 2.0f;
static const float VIEW_MIN_SCALE = 0.8f;

static const float VIEW_LOGICAL_LEFT = -1;
static const float VIEW_LOGICAL_RIGHT = 1;

static const float VIEW_LOGICAL_MAX_LEFT = -2;
static const float VIEW_LOGICAL_MAX_RIGHT = 2;
static const float VIEW_LOGICAL_MAX_BOTTOM = -2;
static const float VIEW_LOGICAL_MAX_TOP = 2;




static const char BACK_IMAGE_NAME[] = "back_class_normal.png" ;



static const int SCENE_INDEX_HARU		= 0;
static const int SCENE_INDEX_SHIZUKU		= 1;
static const int SCENE_INDEX_WANKO		= 2;
static const int SCENE_INDEX_MULTI_MODEL		= 3;

static const char MODEL_HARU_DIR[]		= "live2d/haru/";
static const char MODEL_SHIZUKU_DIR[]		= "live2d/shizuku/";
static const char MODEL_WANKO_DIR[]       = "live2d/wanko/";

static const char MODEL_HARU[]		= "haru.model.json";
static const char MODEL_HARU_A[]		= "haru_01.model.json";
static const char MODEL_HARU_B[]		= "haru_02.model.json";
static const char MODEL_SHIZUKU[]		= "shizuku.model.json";
static const char MODEL_WANKO[]       = "wanko.model.json";



static const char MOTION_GROUP_IDLE[]			="idle";
static const char MOTION_GROUP_TAP_BODY[]		="tap_body";


static const char HIT_AREA_NAME_HEAD[]		="head";
static const char HIT_AREA_NAME_BODY[]		="body";


static const int PRIORITY_NONE  = 0;
static const int PRIORITY_IDLE  = 1;
static const int PRIORITY_NORMAL= 2;
static const int PRIORITY_FORCE = 3;


class LAppDefine {
public:
    static const bool DEBUG_LOG=true;
	static const bool DEBUG_TOUCH_LOG=false;
};
