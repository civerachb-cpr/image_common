// Copyright (c) 2023 Open Source Robotics Foundation, Inc.
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
//    * Neither the name of the Willow Garage nor the names of its
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

#ifndef IMAGE_TRANSPORT__REPUBLISH_HPP_
#define IMAGE_TRANSPORT__REPUBLISH_HPP_

#include <memory>
#include <mutex>

#include "image_transport/image_transport.hpp"
#include "image_transport/visibility_control.hpp"

#include <pluginlib/class_loader.hpp>

#include <rclcpp/rclcpp.hpp>

namespace image_transport
{
class Republisher : public rclcpp::Node
{
public:
  /// Constructor
  IMAGE_TRANSPORT_PUBLIC
  explicit Republisher(const rclcpp::NodeOptions & options);

private:
  void initialize();

  rclcpp::TimerBase::SharedPtr timer_;
  bool initialized_{false};
  image_transport::Subscriber sub;
  image_transport::Publisher pub;
  std::mutex pub_matched_mutex;
  pluginlib::UniquePtr<image_transport::PublisherPlugin> instance;
  std::shared_ptr<pluginlib::ClassLoader<image_transport::PublisherPlugin>> loader;
};

}  // namespace image_transport
#endif  // IMAGE_TRANSPORT__REPUBLISH_HPP_
