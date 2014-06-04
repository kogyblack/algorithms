#ifndef SAMPLEBIASED_H
#define SAMPLEBIASED_H

#include "basictypes.h"

//class Point;
class Map;

/*
// Typedefs
typedef Point (*Sample)(Map const&);
//typedef int (*Nearest)(Graph const&, Point const&);
//typedef Point (*Steer)(Point const&, Point const&, double);
//typedef bool (*ObstacleFree)(Map const&, Point const&, Point const&);
//typedef std::vector<int> (*Near)(const Graph&, int, double);

Point sampleGoal(Map const&);
Sample sampleBiased(double bias);
*/

class SampleBiased
{
public:
  SampleBiased(double bias);
  Point operator() (Map const&);
private:
  double bias_;
};

#endif

