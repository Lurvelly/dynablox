#ifndef LIDAR_MOTION_DETECTION_PROCESSING_TRACKING_H_
#define LIDAR_MOTION_DETECTION_PROCESSING_TRACKING_H_

#include "lidar_motion_detection/3rd_party/config_utilities.hpp"
#include "lidar_motion_detection/common/types.h"

namespace motion_detection {

class Tracking {
 public:
  // Config.
  struct Config : public config_utilities::Config<Config> {
    // If false just skip this step.
    bool use_tracking = true;

    // Numbers of frames a cluster needs to be tracked to be considered dynamic.
    int min_track_duration = 3;

    // Maximum distance a cluster may have moved to be considered a track [m].
    float max_tracking_distance = 1.f;

    Config() { setConfigName("Tracking"); }

   protected:
    void setupParamsAndPrinting() override;
    void checkParams() const override;
  };

  // Constructor.
  Tracking(const Config& config);

  /**
   * @brief Track all clusters w.r.t. the previous clsuters. Denote the object
   * level points dynamic in the cloud_info.
   *
   * @param cloud Current lidar point cloud.
   * @param clusters Current detected clusters.
   * @param cloud_info Cloud info to denote moving points.
   */
  void track(const Cloud& cloud, Clusters& clusters, CloudInfo& cloud_info);

 private:
  const Config config_;

  // Tracking data w.r.t. previous observation.
  std::vector<voxblox::Point> previous_centroids_;
  std::vector<int> previous_ids_;
  std::vector<int> previous_track_lengths_;

  /**
   * @brief Simple closest association tracking for now.
   *
   * @param cloud Lidar point cloud.
   * @param clusters Current clusters to be tracked.
   */
  void trackClusterIDs(const Cloud& cloud, Clusters& clusters);
};

}  // namespace motion_detection

#endif  // LIDAR_MOTION_DETECTION_PROCESSING_TRACKING_H_
