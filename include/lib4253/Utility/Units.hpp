#pragma once
#include "okapi/api/units/RQuantity.hpp"
#include "okapi/api/units/QLength.hpp"
#include "okapi/api/units/QAngularSpeed.hpp"
#include "okapi/api/units/QAngularAcceleration.hpp"
#include "okapi/api/units/QArea.hpp"
#include "okapi/api/units/QSpeed.hpp"
#include "okapi/api/units/QAcceleration.hpp"
#include "okapi/api/units/QTime.hpp"
#include "okapi/api/units/QAngularJerk.hpp"
#include "okapi/api/units/QJerk.hpp"


namespace okapi{
// Physical quantity types
QUANTITY_TYPE(0, -1, 0, 1, QCurvature);
QUANTITY_TYPE(0, -2, 0, 1, QDCurvatureDs);
QUANTITY_TYPE(0, -1, -1, 1, QDCurvatureDt);

// Predefined Length Units
constexpr QLength tile = 2 * foot;
constexpr QLength court = 12 * foot;

// Predefined Angle Units
constexpr QAngle rotationDeg = degree * 360 / 4096;

// Predefined Curvature Unit
constexpr QCurvature radpm = radian / meter;

// Predefined dCurvature / dS Unit
constexpr QDCurvatureDs radpm2 = radpm / meter;

// Predefined dCurvature / dT Unit  
constexpr QDCurvatureDt radpmps = radpm / second;

// Predefined Angular Acceleration Unit
constexpr QAngularAcceleration radps2 = radps / second;

// Predefined Jerk Unit
constexpr QJerk mps3 = mps2 / second;

// Predefined Angular Jerk Unit
constexpr QAngularJerk radps3 = radps2 / second;

inline namespace literals{
// Length Unit Literals
constexpr QLength operator"" _tile(long double x) { return static_cast<double>(x)*tile; }
constexpr QLength operator"" _tile(unsigned long long int x) { return static_cast<double>(x)*tile; }
constexpr QLength operator"" _court(long double x) { return static_cast<double>(x)*court; }
constexpr QLength operator"" _court(unsigned long long int x) { return static_cast<double>(x)*court; }

// Curvature Unit Literals
constexpr QCurvature operator"" _radpm(long double x) { return static_cast<double>(x)*radpm; }
constexpr QCurvature operator"" _radpm(unsigned long long int x) { return static_cast<double>(x)*radpm; }

// dCurvature / dS literals
constexpr QDCurvatureDs operator"" _radpm2(long double x) { return static_cast<double>(x)*radpm2; }
constexpr QDCurvatureDs operator"" _radpm2(unsigned long long int x) { return static_cast<double>(x)*radpm2; }

// dCurvature / dT literals
constexpr QDCurvatureDt operator"" _radpmps(long double x) { return static_cast<double>(x)*radpmps; }
constexpr QDCurvatureDt operator"" _radpmps(unsigned long long int x) { return static_cast<double>(x)*radpmps; }

// Angular Speed literals
constexpr QAngularSpeed operator"" _radps(long double x) { return static_cast<double>(x)*radps; }
constexpr QAngularSpeed operator"" _radps(unsigned long long int x) { return static_cast<double>(x)*radps; }

// Angular Acceleration literals
constexpr QAngularAcceleration operator"" _radps2(long double x) { return static_cast<double>(x)*radps2; }
constexpr QAngularAcceleration operator"" _radps2(unsigned long long int x) { return static_cast<double>(x)*radps2; }

// Jerk Literals
constexpr QJerk operator"" _mps3(long double x) { return static_cast<double>(x)*mps3; }
constexpr QJerk operator"" _mps3(unsigned long long int x) { return static_cast<double>(x)*mps3; }

// Angular Jerk Literals
constexpr QAngularJerk operator"" _radps3(long double x) { return static_cast<double>(x)*radps3; }
constexpr QAngularJerk operator"" _radps3(unsigned long long int x) { return static_cast<double>(x)*radps3; }

} // namespace literals
} // namespace okapi



