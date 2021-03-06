/* Copyright (C) 2008, Morgan Quigley and Willow Garage, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the names of Stanford University or Willow Garage, Inc. nor the names of its
 *     contributors may be used to endorse or promote products derived from
 *     this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#include "ros/ros.h"
#include "geometry_msgs/PoseWithCovarianceStamped.h"
#include "geometry_msgs/PoseStamped.h"
#include <sstream>

// the odometry_combined publish
ros::Publisher odom_pub;

void poseCallback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg)
{
  geometry_msgs::PoseStamped pose;
  pose.header = msg->header;
  pose.pose = msg->pose.pose;

  odom_pub.publish(pose);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "posecov2pose_node");

  ros::NodeHandle n;
  ros::NodeHandle np("~");

  std::string input_odom, output_odom;

  if(!np.getParam("input",input_odom)) {
    std::cerr << "No input parameter" << std::endl;
    return 0;
  }

  if(!np.getParam("output",output_odom)) {
    std::cerr << "No output parameter" << std::endl;
    return 0;
  }




  // topics
  ros::Subscriber odom_sub = n.subscribe<geometry_msgs::PoseWithCovarianceStamped>(input_odom, 1000, poseCallback);
  odom_pub = n.advertise<geometry_msgs::PoseStamped>(output_odom, 1000);
  ros::spin();

  return 0;
}
