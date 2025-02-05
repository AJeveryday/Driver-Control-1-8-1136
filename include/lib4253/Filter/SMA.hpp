/**
 * @file SMA.hpp
 * @author Ryan Liao (23RyanL@students.tas.tw)
 * @brief Simple moving average filter (SMA) (y r there so many filters wtf)
 * @version 0.1
 * @date 2021-05-21
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once
#include "lib4253/Filter/AbstractFilter.hpp"
#include<queue>

namespace lib4253{

  /**
   * @brief Simple moving average filter (SMA) - inherited from Filter
   *
   */
template<int N> 
class SmaFilter : public AbstractFilter<double>{
    public:
    /**
     * @brief Construct a new Sma Filter object
     *
     */
	SmaFilter() = default;

    /**
     * @brief Destroys the Sma Filter object
     * 
     */
    ~SmaFilter() = default;
    
    void initialize() override;

    /**
     * @brief Resets SMA filter
     *
     */
    void reset() override;

    /**
     * @brief filters raw values through SMA filter
     *
     * @param input raw values
     * @return filtered values
     */
    double filter(const double& input) override;

    /**
     * @brief Gets filtered values
     *
     * @return filtered value
     */
    double getOutput() const override;

    private:
    std::queue<double> value; // ngl i was thinking about coding a segment tree
    double total, output;
};
}
