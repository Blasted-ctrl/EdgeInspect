// Host-side OpenCV demo for EdgeInspect: runs on your PC, not on the ESP32.
// It lives in tools/ (outside src/), so PlatformIO never compiles it into the
// firmware. Open it in Cortex and press Run; Cortex finds OpenCV and links it.
//
// It draws a synthetic metal plate with a hole and a chipped corner, finds its
// edges with Canny, and prints how many edge pixels were found plus a small
// ASCII picture of them.
#include <opencv2/opencv.hpp>

#include <iostream>

int main() {
  const int size = 160;
  cv::Mat plate(size, size, CV_8UC1, cv::Scalar(40));
  cv::rectangle(plate, {30, 30}, {130, 130}, cv::Scalar(200), cv::FILLED);   // the plate
  cv::circle(plate, {80, 80}, 25, cv::Scalar(40), cv::FILLED);               // a drilled hole
  cv::rectangle(plate, {30, 30}, {48, 40}, cv::Scalar(40), cv::FILLED);      // chipped corner (the defect)

  cv::Mat blurred, edges;
  cv::GaussianBlur(plate, blurred, cv::Size(5, 5), 1.4);
  cv::Canny(blurred, edges, 50, 150);

  std::cout << "OpenCV " << CV_VERSION << "\n";
  std::cout << "edge pixels found: " << cv::countNonZero(edges) << "\n\n";

  // 4x4 pixels per character: '#' wherever the block contains an edge.
  const int block = 4;
  for (int y = 0; y < size; y += block) {
    for (int x = 0; x < size; x += block) {
      std::cout << (cv::countNonZero(edges({x, y, block, block})) > 0 ? '#' : ' ');
    }
    std::cout << "\n";
  }
  return 0;
}
