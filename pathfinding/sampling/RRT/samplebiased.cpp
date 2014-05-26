#include <iostream>

#include <chrono>
#include <random>

#include "samplebiased.h"
#include "generator.h"
#include "plan.h"
#include "basictypes.h"
#include "map.h"

/*
Point sampleGoal(Map const& rrtmap)
{
  Point goalMin = rrtmap.getGoalRect().min_corner(),
        goalMax = rrtmap.getGoalRect().max_corner();

  double dx = goalMax.get(0) - goalMin.get(0),
          dy = goalMax.get(1) - goalMin.get(1);

  double x = goalMin.get(0) + dx * generator();
  double y = goalMin.get(1) + dy * generator();

  return Point(x, y);
}

Sample sampleBiased(double bias)
{
  if (generator() < bias)
    return sampleGoal;
  else
    return rrtbase::default_functions::sample;
}
*/

SampleBiased::SampleBiased(double bias) : bias_(bias)
{}

Point SampleBiased::operator() (Map const& rrtmap)
{
  if (generator() < bias_)
  {
    Point goalMin = rrtmap.getGoalRect().min_corner(),
          goalMax = rrtmap.getGoalRect().max_corner();

    double dx = goalMax.get(0) - goalMin.get(0),
            dy = goalMax.get(1) - goalMin.get(1);

    double x = goalMin.get(0) + dx * generator();
    double y = goalMin.get(1) + dy * generator();

    return Point(x, y);
  }
  else
    return rrtbase::default_functions::sample(rrtmap);
}
