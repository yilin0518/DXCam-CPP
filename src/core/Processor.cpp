//
// Created by Fidel on 2023/10/26.
//

#include "core/Processor.h"

namespace DXCam {

Processor::Processor(const ColorFormat output_color) {
    this->color_mode = output_color;
}

cv::Mat Processor::process_cvt_color(const cv::Mat &image) {
    // one-time initialization for cvt_color
    if (!this->cvt_color) {
        if (this->color_mode == BGRA) {  // no conversion required
            this->cvt_color = [](const cv::Mat &image) { return image; };
        } else {
            const auto cv2_code = this->COLOR_MAPPING.at(this->color_mode);
            this->cvt_color = [cv2_code](const cv::Mat &src) {
                cv::Mat dst;
                cv::cvtColor(src, dst, cv2_code);
                return dst;
            };
        }
    }

    return this->cvt_color(image);
}

cv::Mat Processor::process(const DXGI_MAPPED_RECT &rect, const int width,
                           const int height, const Region &region,
                           const int rotation_angle) {
    const auto pitch = rect.Pitch / 4;

    cv::Mat image;
    if (rotation_angle == 0 || rotation_angle == 180) {
        image = cv::Mat(height, pitch, CV_8UC4, rect.pBits);
    } else {
        image = cv::Mat(width, pitch, CV_8UC4, rect.pBits);
    }

    image = this->process_cvt_color(image);

    // TODO untested
    switch (rotation_angle) {
        case 90:
            cv::rotate(image, image, cv::ROTATE_90_CLOCKWISE);
            break;
        case 180:
            cv::rotate(image, image, cv::ROTATE_180);
            break;
        case 270:
            cv::rotate(image, image, cv::ROTATE_90_COUNTERCLOCKWISE);
            break;
        default:
            break;
    }

    if (region.right - region.left != width ||
        region.bottom - region.top != height) {
        image = image(cv::Range(region.top, region.bottom),
                      cv::Range(region.left, region.right));
    }

    return image;
}

}  // namespace DXCam