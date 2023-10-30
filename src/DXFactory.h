//
// Created by Fidel on 2023/10/27.
//

#ifndef DXCAM_CPP_DXFACTORY_H
#define DXCAM_CPP_DXFACTORY_H

#include <map>
#include <memory>

#include "DXCamera.h"
#include "core/Device.h"
#include "core/Output.h"
#include "core/OutputMetadata.h"

namespace DXCam {

class DXFactory {
public:
    DXFactory();

    std::shared_ptr<DXCamera> create(int device_idx = 0, int output_idx = -1,
                                     ColorFormat output_color = RGB,
                                     size_t max_buffer_len = 64);
    std::shared_ptr<DXCamera> create(const Region &region, int device_idx = 0,
                                     int output_idx = -1,
                                     ColorFormat output_color = RGB,
                                     size_t max_buffer_len = 64);

    [[nodiscard]] std::vector<DeviceInfo> get_devices_info() const;
    [[nodiscard]] std::vector<std::vector<OutputInfo>> get_outputs_info() const;

    std::vector<Device> devices;
    std::vector<std::vector<Output>> outputs;
    OutputMetadata output_metadata;

private:
    [[nodiscard]] int find_primary_output_idx(int device_idx) const;
    [[nodiscard]] std::shared_ptr<DXCamera> find_instant(int device_idx,
                                                         int output_idx);

    std::map<std::tuple<int, int>, std::weak_ptr<DXCamera>> camera_instants;
};

}  // namespace DXCam

#endif  //DXCAM_CPP_DXFACTORY_H
