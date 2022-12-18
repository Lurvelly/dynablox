#include <ros/ros.h>

#include "lidar_motion_detection/motion_detector.h"

int main(int argc, char** argv) {
  ros::init(argc, argv, "motion_detector");

  // Always add these arguments for proper logging.
  config_utilities::RequiredArguments ra(
      &argc, &argv, {"--logtostderr", "--colorlogtostderr"});

  // Setup logging.
  config_utilities::GlobalSettings().indicate_default_values = true;
  config_utilities::GlobalSettings().indicate_units = true;
  google::InitGoogleLogging(argv[0]);
  google::InstallFailureSignalHandler();
  google::ParseCommandLineFlags(&argc, &argv, false);

  // Setup node.
  ros::NodeHandle nh;
  ros::NodeHandle nh_private("~");
  motion_detection::MotionDetector motion_detector(nh, nh_private);

  ros::spin();
  return 0;
}
