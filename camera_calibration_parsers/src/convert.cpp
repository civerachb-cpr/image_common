// Copyright (c) 2009, Willow Garage, Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//    * Redistributions of source code must retain the above copyright
//      notice, this list of conditions and the following disclaimer.
//
//    * Redistributions in binary form must reproduce the above copyright
//      notice, this list of conditions and the following disclaimer in the
//      documentation and/or other materials provided with the distribution.
//
//    * Neither the name of the copyright holder nor the names of its
//      contributors may be used to endorse or promote products derived from
//      this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#include <cstdio>
#include <string>

#include "rclcpp/logging.hpp"
#include "sensor_msgs/msg/camera_info.hpp"
#include "camera_calibration_parsers/parse.hpp"

using camera_calibration_parsers::readCalibration;
using camera_calibration_parsers::writeCalibration;

int main(int argc, char ** argv)
{
  auto logger = rclcpp::get_logger("camera_calibration_parsers.convert");
  if (argc < 3) {
    printf(
      "Usage: %s input.yml output.ini\n"
      "       %s input.ini output.yml\n", argv[0], argv[0]);
    return 0;
  }

  std::string name;
  sensor_msgs::msg::CameraInfo cam_info;
  if (!readCalibration(argv[1], name, cam_info)) {
    RCLCPP_ERROR(logger, "Failed to load camera model from file %s", argv[1]);
    return -1;
  }
  if (!writeCalibration(argv[2], name, cam_info)) {
    RCLCPP_ERROR(logger, "Failed to save camera model to file %s", argv[2]);
    return -1;
  }

  RCLCPP_INFO(logger, "Saved %s", argv[2]);
  return 0;
}
