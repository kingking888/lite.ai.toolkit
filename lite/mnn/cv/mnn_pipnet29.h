//
// Created by DefTruth on 2022/3/20.
//

#ifndef LITE_AI_TOOLKIT_MNN_CV_MNN_PIPNET29_H
#define LITE_AI_TOOLKIT_MNN_CV_MNN_PIPNET29_H

#include "lite/mnn/core/mnn_core.h"

namespace mnncv
{
  class LITE_EXPORTS MNNPIPNet29 : public BasicMNNHandler
  {
  public:
    explicit MNNPIPNet29(const std::string &_mnn_path, unsigned int _num_threads = 1); //
    ~MNNPIPNet29() override = default;

  private:
    const float mean_vals[3] = {0.485f * 255.f, 0.456f * 255.f, 0.406f * 255.f};
    const float norm_vals[3] = {(1.0f / 0.229f) * (1.0 / 255.f),
                                (1.0f / 0.224f) * (1.0 / 255.f),
                                (1.0f / 0.225f) * (1.0 / 255.f)};
    static constexpr const unsigned int num_nb = 10;
    static constexpr const unsigned int num_lms = 29;
    static constexpr const unsigned int max_len = 19;
    static constexpr const unsigned int net_stride = 32;

  private:
    void initialize_pretreat(); //

    void transform(const cv::Mat &mat) override; // resize & normalize.

    void generate_landmarks(types::Landmarks &landmarks,
                            const std::map<std::string, MNN::Tensor *> &output_tensors,
                            float img_height, float img_width);

  public:
    void detect(const cv::Mat &mat, types::Landmarks &landmarks);

  private:
    const unsigned int reverse_index1[29 * 19] = {
        2, 4, 5, 8, 12, 13, 16, 2, 4, 5, 8, 12, 13, 16, 2, 4, 5, 8, 12, 3, 6, 7, 9, 14, 15, 17, 3, 6, 7, 9, 14, 15, 17, 3, 6, 7, 9, 14, 0,
        3, 4, 5, 6, 7, 8, 10, 11, 12, 13, 14, 16, 0, 3, 4, 5, 6, 7, 0, 1, 2, 4, 5, 6, 7, 9, 10, 11, 12, 14, 15, 17, 0, 1, 2, 4, 5, 0, 2, 5,
        8, 10, 12, 13, 16, 0, 2, 5, 8, 10, 12, 13, 16, 0, 2, 5, 0, 2, 4, 8, 10, 12, 13, 16, 0, 2, 4, 8, 10, 12, 13, 16, 0, 2, 4, 1, 3, 7, 9,
        11, 14, 15, 17, 1, 3, 7, 9, 11, 14, 15, 17, 1, 3, 7, 1, 3, 6, 9, 11, 14, 15, 17, 1, 3, 6, 9, 11, 14, 15, 17, 1, 3, 6, 0, 2, 4, 5,
        10, 12, 13, 16, 0, 2, 4, 5, 10, 12, 13, 16, 0, 2, 4, 1, 3, 6, 7, 11, 14, 15, 17, 1, 3, 6, 7, 11, 14, 15, 17, 1, 3, 6, 0, 2, 3, 4, 5,
        8, 12, 13, 16, 18, 20, 0, 2, 3, 4, 5, 8, 12, 13, 1, 2, 3, 6, 7, 9, 14, 15, 17, 19, 20, 21, 1, 2, 3, 6, 7, 9, 14, 0, 2, 4, 5, 8, 10,
        13, 16, 0, 2, 4, 5, 8, 10, 13, 16, 0, 2, 4, 0, 2, 4, 5, 8, 10, 12, 16, 18, 22, 0, 2, 4, 5, 8, 10, 12, 16, 18, 1, 3, 6, 7, 9, 11, 15,
        17, 1, 3, 6, 7, 9, 11, 15, 17, 1, 3, 6, 1, 3, 6, 7, 9, 11, 14, 17, 19, 23, 1, 3, 6, 7, 9, 11, 14, 17, 19, 0, 2, 4, 5, 8, 10, 12, 13,
        18, 0, 2, 4, 5, 8, 10, 12, 13, 18, 0, 1, 3, 6, 7, 9, 11, 14, 15, 19, 1, 3, 6, 7, 9, 11, 14, 15, 19, 1, 0, 4, 5, 8, 10, 12, 13, 16,
        19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 0, 1, 6, 7, 9, 11, 14, 15, 17, 18, 20, 21, 22, 23, 24, 25, 26, 27, 28, 1, 1, 8, 9, 10, 11,
        13, 15, 16, 17, 18, 19, 21, 22, 23, 24, 25, 26, 27, 28, 18, 19, 20, 22, 23, 24, 25, 26, 27, 28, 18, 19, 20, 22, 23, 24, 25, 26, 27,
        18, 20, 21, 24, 25, 26, 27, 28, 18, 20, 21, 24, 25, 26, 27, 28, 18, 20, 21, 19, 21, 24, 25, 26, 27, 28, 19, 21, 24, 25, 26, 27, 28,
        19, 21, 24, 25, 26, 18, 19, 20, 21, 22, 23, 25, 26, 27, 28, 18, 19, 20, 21, 22, 23, 25, 26, 27, 18, 19, 20, 21, 22, 23, 24, 26, 27,
        28, 18, 19, 20, 21, 22, 23, 24, 26, 27, 18, 19, 20, 21, 22, 23, 24, 25, 27, 28, 18, 19, 20, 21, 22, 23, 24, 25, 27, 20, 21, 22, 23,
        24, 25, 26, 28, 20, 21, 22, 23, 24, 25, 26, 28, 20, 21, 22, 22, 23, 24, 25, 26, 27, 22, 23, 24, 25, 26, 27, 22, 23, 24, 25, 26, 27,
        22
    };
    const unsigned int reverse_index2[29 * 19] = {
        9, 3, 5, 3, 7, 7, 7, 9, 3, 5, 3, 7, 7, 7, 9, 3, 5, 3, 7, 9, 3, 5, 3, 7, 7, 7, 9, 3, 5, 3, 7, 7, 7, 9, 3, 5, 3, 7, 7, 6, 6, 6, 8, 9,
        7, 0, 9, 6, 5, 9, 6, 7, 6, 6, 6, 8, 9, 9, 7, 6, 8, 9, 6, 6, 7, 8, 0, 9, 6, 6, 6, 9, 7, 6, 8, 9, 2, 5, 0, 5, 5, 3, 6, 5, 2, 5, 0, 5,
        5, 3, 6, 5, 2, 5, 0, 1, 3, 0, 4, 4, 2, 4, 2, 1, 3, 0, 4, 4, 2, 4, 2, 1, 3, 0, 2, 4, 0, 5, 5, 3, 5, 5, 2, 4, 0, 5, 5, 3, 5, 5, 2, 4,
        0, 1, 3, 0, 4, 4, 2, 4, 2, 1, 3, 0, 4, 4, 2, 4, 2, 1, 3, 0, 0, 7, 4, 3, 6, 5, 3, 4, 0, 7, 4, 3, 6, 5, 3, 4, 0, 7, 4, 0, 7, 4, 3, 6,
        5, 2, 4, 0, 7, 4, 3, 6, 5, 2, 4, 0, 7, 4, 6, 0, 8, 7, 7, 6, 4, 2, 3, 5, 6, 6, 0, 8, 7, 7, 6, 4, 2, 6, 8, 0, 7, 7, 6, 4, 3, 3, 5, 7,
        9, 6, 8, 0, 7, 7, 6, 4, 3, 1, 1, 1, 2, 3, 1, 0, 3, 1, 1, 1, 2, 3, 1, 0, 3, 1, 1, 5, 4, 5, 4, 0, 2, 1, 1, 6, 9, 5, 4, 5, 4, 0, 2, 1,
        1, 6, 3, 1, 1, 1, 2, 3, 1, 0, 3, 1, 1, 1, 2, 3, 1, 0, 3, 1, 1, 5, 5, 5, 4, 0, 2, 1, 1, 7, 9, 5, 5, 5, 4, 0, 2, 1, 1, 7, 4, 2, 2, 2,
        1, 1, 0, 0, 9, 4, 2, 2, 2, 1, 1, 0, 0, 9, 4, 4, 2, 2, 2, 1, 1, 0, 0, 9, 4, 2, 2, 2, 1, 1, 0, 0, 9, 4, 8, 9, 8, 8, 7, 8, 8, 8, 8, 1,
        3, 0, 8, 5, 8, 9, 9, 9, 8, 8, 9, 8, 8, 7, 8, 8, 8, 8, 2, 4, 8, 0, 6, 7, 8, 8, 7, 8, 9, 9, 9, 9, 8, 9, 9, 9, 9, 0, 0, 0, 6, 6, 4, 4,
        6, 7, 8, 1, 1, 0, 5, 5, 2, 3, 3, 4, 6, 1, 1, 0, 5, 5, 2, 3, 3, 4, 2, 8, 7, 7, 5, 4, 6, 5, 2, 8, 7, 7, 5, 4, 6, 5, 2, 8, 7, 2, 8, 8,
        6, 5, 5, 4, 2, 8, 8, 6, 5, 5, 4, 2, 8, 8, 6, 5, 3, 3, 3, 1, 2, 3, 0, 2, 2, 3, 3, 3, 3, 1, 2, 3, 0, 2, 2, 4, 4, 4, 2, 1, 1, 0, 0, 1,
        2, 4, 4, 4, 2, 1, 1, 0, 0, 1, 7, 6, 5, 5, 3, 2, 1, 1, 0, 1, 7, 6, 5, 5, 3, 2, 1, 1, 0, 9, 6, 4, 4, 3, 2, 1, 0, 9, 6, 4, 4, 3, 2, 1,
        0, 9, 6, 4, 7, 7, 9, 9, 7, 3, 7, 7, 9, 9, 7, 3, 7, 7, 9, 9, 7, 3, 7
    };
  };
}


#endif //LITE_AI_TOOLKIT_MNN_CV_MNN_PIPNET29_H
