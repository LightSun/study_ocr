# import ctypes
# from ctypes import *
#
# sofile = "/media/heaven7/Elements_SE/study/work/OCR/build-FDOcr-qt_5_14_2_gcc64-Debug/pybind" \
#          + "/PyOcrInfer.cpython-38-x86_64-linux-gnu.so"
#
# lib = ctypes.cdll.LoadLibrary(sofile)

import os
import sys

LD_DIR = "/media/heaven7/Elements_SE/study/work/OCR/FD_LIBS"
sys.path.append(LD_DIR)

import  PyOcrInfer as PyOcr
import cv2

descDir = "/media/heaven7/Elements_SE/study/work/OCR/off_modules/OcrV4_desc"
cacheDir = "/media/heaven7/Elements_SE/study/work/OCR/local/cache"
eh = PyOcr.EdmHelper()
eh.loadDir(descDir)
#

def test_ocr_infer():
    config = PyOcr.OcrConfig()
    config.cache_dir = cacheDir
    config.model_desc_dir = descDir
    config.run_mode = "PADDLE"
    #
    api = PyOcr.OcrApi()
    api.setConfig(config)
    if api.loadConfigs() and api.buildOCR():
        print("Build OcrInfer ok.")
    else:
        print("Build OcrInfer failed.")
        return
    inDir = "/media/heaven7/Elements_SE/study/work/OCR/local"
    imgPath = inDir + "/test.jpeg"
    mat = cv2.imread(imgPath)
    ocrRet = api.infer(mat)
    #print("OcrResult: ", str(ocrRet))
    # boxes, texts, rec_scores, cls_scores, cls_labels
    for i in range(len(ocrRet.boxes)):
        box = ocrRet.boxes[i]
        text = ocrRet.texts[i]
        rec_score = ocrRet.rec_scores[i]
        cls_score = ocrRet.cls_scores[i]
        cls_label = ocrRet.cls_labels[i]
        print(i," box: ", box)
        print(i, " text: ", text)
        print(i, " rec_score: ", rec_score)
        print(i, " cls_score: ", cls_score)
        print(i, " cls_label: ", cls_label)


test_ocr_infer()


