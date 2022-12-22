#ifndef PROJECT22_P1_CONVEXHULL_H
#define PROJECT22_P1_CONVEXHULL_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/convex_hull_2.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/Arrangement_2.h>
#include <CGAL/property_map.h>
#include <CGAL/intersections.h>
#include "Polygon.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Polygon_2<K> Polygon_2;
typedef K::Segment_2 Segment_2;
typedef K::Point_2 Point_2;

using namespace std;


class ConvexHull : public Polygon
{
private:
    string edgeSelection;
    bool collinear(Point_2 a, Point_2 b, Point_2 c);
public:
    ConvexHull(string inputFileName, string edgeSelection);
    virtual void calculateResult();
};

#endif //PROJECT22_P1_CONVEXHULL_H
