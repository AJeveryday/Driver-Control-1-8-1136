/**
 * @file Slew.hpp
 * @author Ryan Liao (23RyanL@students.tas.tw)
 * @brief Slew controller
 * @version 0.1
 * @date 2021-05-20
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once
#include <cmath>
#include "lib4253/Controller/AbstractVelocityController.hpp"
#include "lib4253/Utility/Math.hpp"

namespace lib4253{

struct SlewGain {
    double accStep, decStep;
};

/**
 * @brief Slew controller class
 *
 */
class Slew : public AbstractVelocityController<SlewGain> {
    protected:
    double speed;
    SlewGain gain;
    
    public:  
    /**
     * @brief Construct a new Slew Controller object
     *
     */
    Slew() = default;
    
    /**
     * @brief Construct a new Slew Controller object
     *
     * @param accel acceleration step (how much the velocity increases everytime the robot refreshes)
     * @param decel deceleration step (^ vise versa)
     */
    Slew(const SlewGain& gain);

    /**
     * @brief Destroys the Slew Controller object
     * 
     */
    ~Slew() = default;
    
    
    /**
     * @brief Resets slew controller
     * 
     */
    void reset() override;

    void initialize() override;
    
    /**
     * @brief Calculates output power
     *
     * @param val target power
     * @return (possibly) modified power
     */
    double step(const double& val) override;
};
}