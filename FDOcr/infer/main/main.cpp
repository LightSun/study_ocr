#include <iostream>
#include "opencv2/opencv.hpp"
#include "fastdeploy/vision.h"

#include "infer/src/fd_ocr.h"
#include "infer/src/ocr_common.h"

using namespace h7;

static void test1();

int main(int argc , const char* argv[])
{
    setbuf(stdout, NULL);
    test1();
    return 0;
}

void test1(){
    String descDir = "/media/heaven7/Elements_SE/study/work/OCR/off_modules/OcrV4_desc";
    String cacheDir = "/media/heaven7/Elements_SE/study/work/OCR/local/cache";
    OcrConfig config;
    config.model_desc_dir = descDir;
    config.cache_dir = cacheDir;
    //config.device = "cpu";
    config.run_mode = h7::kPADDLE;
    //
    OcrApi api;
    api.setOcrConfig(config);
    FDASSERT(api.loadConfigs(), "loadConfigs from dir failed: %s", descDir.data());
    FDASSERT(api.buildOCR(), "buildOCR failed.");
    String inDir = "/media/heaven7/Elements_SE/study/work/OCR/local";
    String imgPath = inDir + "/test.jpeg";
    auto img = cv::imread(imgPath);
    //cv::imwrite(inDir + "/test.png", img);
   // for(int i = 0 ; i < 100 ; ++ i)
    {
        fastdeploy::vision::OCRResult result;
        FDASSERT(api.infer(img, &result), "infer failed.");
        auto str = result.Str();
        printf("%s\n", str.data());
    }
}
