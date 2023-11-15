//
// Created by Fidel on 2023/10/26.
//

#ifndef DXCAM_CPP_DXCAM_H
#define DXCAM_CPP_DXCAM_H

#include "DXCamera.h"

namespace DXCam {

/**
 * @brief Create a DXCamera instance which captures the full screen by default.
 * @param [in] device_idx The index of the device to be used. Use
 * get_devices_info() to list all devices.
 * @param [in] output_idx The index of the monitor to be used. Use
 * get_outputs_info() to list all outputs.
 * @param [in] max_buffer_len The size of the frame buffer.
 * @return A shared pointer to the DXCamera instance. If there exists an
 * instance with the same device and output, the shared pointer to the existing
 * instance will be returned.
 */
[[maybe_unused]] DXCAM_EXPORT std::shared_ptr<DXCamera> create(
        int device_idx = 0, int output_idx = -1, size_t max_buffer_len = 64);

/**
 * @brief Create a DXCamera instance which captures a rectangle region by
 * default.
 * @param [in] region The rectangle region to be captured.
 * @param [in] device_idx The index of the device to be used. Use
 * get_devices_info() to list all devices.
 * @param [in] output_idx The index of the monitor to be used. Use
 * get_outputs_info() to list all outputs.
 * @param [in] max_buffer_len The size of the frame buffer.
 * @return A shared pointer to the DXCamera instance. If there exists an
 * instance with the same device and output, the shared pointer to the existing
 * instance will be returned.
 */
[[maybe_unused]] DXCAM_EXPORT std::shared_ptr<DXCamera> create(
        const Region &region, int device_idx = 0, int output_idx = -1,
        size_t max_buffer_len = 64);

/**
 * @brief List all devices.
 * @return A vector of DeviceInfo.
 */
[[maybe_unused]] DXCAM_EXPORT std::vector<DeviceInfo> get_devices_info();
/**
 * @brief List all outputs.
 * @return A vector of vector of OutputInfo. The first dimension represents each
 * device, and the second dimension represents each output of that device.
 */
[[maybe_unused]] DXCAM_EXPORT std::vector<std::vector<OutputInfo>>
get_outputs_info();

}  // namespace DXCam


#endif  // DXCAM_CPP_DXCAM_H
