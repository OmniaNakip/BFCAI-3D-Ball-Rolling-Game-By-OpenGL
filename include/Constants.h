#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace Constants {
constexpr int kWindowWidth = 1024;
constexpr int kWindowHeight = 768;
constexpr const char* kWindowTitle = "Endless Runner 3D";

constexpr int kTargetFps = 60;
constexpr int kFrameMs = 1000 / kTargetFps;
constexpr float kFrameSeconds = 1.0f / static_cast<float>(kTargetFps);

constexpr float kClearColorR = 0.05f;
constexpr float kClearColorG = 0.07f;
constexpr float kClearColorB = 0.12f;
constexpr float kClearColorA = 1.0f;

constexpr float kGroundY = 0.0f;
constexpr float kGroundWidth = 6.0f;
constexpr float kGroundLength = 60.0f;
constexpr float kGroundBackZ = 8.0f;

constexpr float kRoadEdgeWidth = 0.2f;
constexpr float kRoadEdgeHeight = 0.02f;
constexpr float kEdgeSegmentLength = 3.0f;
constexpr float kEdgeSegmentGap = 1.0f;
constexpr float kEdgeColor1R = 0.95f;
constexpr float kEdgeColor1G = 0.9f;
constexpr float kEdgeColor1B = 0.2f;
constexpr float kEdgeColor2R = 0.2f;
constexpr float kEdgeColor2G = 1.0f;
constexpr float kEdgeColor2B = 0.35f;

constexpr int kLaneCount = 3;
constexpr float kLaneWidth = 2.0f;

constexpr float kPlayerRadius = 0.5f;
constexpr float kPlayerGroundY = kPlayerRadius;
constexpr float kJumpVelocity = 6.5f;
constexpr float kGravity = 14.0f;

constexpr float kObstacleSize = 1.0f;
constexpr float kObstacleStartZ = -40.0f;
constexpr float kObstacleResetZ = 6.0f;
constexpr float kObstacleSpacing = 12.0f;
constexpr float kObstacleSpeed = 8.0f;
constexpr float kSpeedAccelerationRate = 0.2f;  // Speed increases by this factor per second

constexpr float kAsteroidScaleX = 1.0f;
constexpr float kAsteroidScaleY = 0.8f;
constexpr float kAsteroidScaleZ = 1.1f;
constexpr float kAsteroidColorR = 0.6f;
constexpr float kAsteroidColorG = 0.55f;
constexpr float kAsteroidColorB = 0.5f;

constexpr int kCoinCount = 10;
constexpr float kCoinRadius = 0.22f;
constexpr float kCoinHeight = 0.9f;
constexpr float kCoinStartZ = -18.0f;
constexpr float kCoinSpacing = 9.0f;
constexpr float kCoinColorR = 0.95f;
constexpr float kCoinColorG = 0.85f;
constexpr float kCoinColorB = 0.2f;

constexpr float kCameraHeight = 3.5f;
constexpr float kCameraDistance = 8.0f;
constexpr float kCameraLookAhead = -6.0f;
}  // namespace Constants

#endif  // CONSTANTS_H
