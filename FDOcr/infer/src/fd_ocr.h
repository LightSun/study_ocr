#pragma once

#include "infer/src/ocr_context.h"

namespace fastdeploy {
namespace vision {
struct OCRResult;
}
}

namespace h7 {

class EdmHelper;
class FD_OCR;

enum{
    kOCR_Type_DET,
    kOCR_Type_CLS,
    kOCR_Type_REC,
};

class OcrApi: public INoCopy
{
public:
    OcrApi();
    ~OcrApi();

    void setOcrConfig(const OcrConfig&);

    bool loadConfigs();
    bool loadConfigs(EdmHelper* decoder);

    bool buildOCR();

    bool infer(cv::Mat& mat, fastdeploy::vision::OCRResult* res);

    bool inferBatch(const std::vector<cv::Mat>& imgs,
                       std::vector<fastdeploy::vision::OCRResult>* results);

private:
    FD_OCR* m_ptr;
};

}

