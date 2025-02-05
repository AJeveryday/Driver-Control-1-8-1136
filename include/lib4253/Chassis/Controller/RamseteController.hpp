#pragma once
#include "lib4253/Chassis/Device/Chassis.hpp"
#include "lib4253/Chassis/Device/Odometry.hpp"
#include "lib4253/Trajectory/Trajectory.hpp"
#include "lib4253/Utility/Units.hpp"
namespace lib4253{

class RamseteController{
    public:
    RamseteController(
        std::shared_ptr<Chassis> iChassis,
        std::shared_ptr<Odometry> iOdometry,
        const double& iB,
        const double& iZeta
    );

    void followPath(const Trajectory& path);

    private:
    std::shared_ptr<Chassis> chassis;
    std::shared_ptr<Odometry> odometry;
    Pose2D tolerance;
    double b;
    double zeta;

    std::pair<okapi::QSpeed, okapi::QAngularSpeed> update(const TrajectoryPoint& target, const Pose2D& currentPos);

};
}