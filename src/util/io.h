//
// Created by Fidel on 2023/10/27.
//

#ifndef DXCAM_CPP_IO_H
#define DXCAM_CPP_IO_H

#include <dxgi.h>

#include <map>
#include <vector>

#include "core/OutputMetadata.h"

namespace DXCam {

std::vector<IDXGIAdapter1 *> enum_dxgi_adapters();

OutputMetadata get_output_metadata();

}  // namespace DXCam

#endif  // DXCAM_CPP_IO_H
