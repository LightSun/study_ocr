#pragma once

#include <string>

#define USE_OPENVONO 1
//#define USE_MED_RSA 1
//#define USE_TABLE_API 1

namespace h7 {

using String = std::string;

enum RunModeType{
    kPADDLE = 1,
    kTRT_F32,
    kTRT_F16,
    kTRT_INT8,
    kOpenvino
};

struct OcrConfig{
    String cache_dir;
    String model_desc_dir;

    String model_dir_cls;
    String model_dir_det;
    String model_dir_rec;
    String rec_label_file;

    String device {"GPU"}; //GPU or CPU

    float threshold {0.5f};
    int gpu_id {0};
    int run_mode {kTRT_F32};
    int max_batch_cls {6};
    int max_batch_rec {8};
    bool debug {false};
    String logFile;
};

}

