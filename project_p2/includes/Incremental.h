#ifndef PROJECT22_P1_INCREMENTAL_H
#define PROJECT22_P1_INCREMENTAL_H

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
#include <CGAL/Polygon_2/Polygon_2_edge_iterator.h>
#include "Polygon.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Polygon_2<K> Polygon_2;
typedef K::Segment_2 Segment_2;
typedef K::Point_2 Point_2;

using namespace std;

bool function1(Point_2 p1, Point_2 p2);
bool function2(Point_2 p1, Point_2 p2);
bool function3(Point_2 p1, Point_2 p2);
bool function4(Point_2 p1, Point_2 p2);

class Incremental : public Polygon
{
private:
    vector<Point_2> sortedPoints;
    string sortingMethod;
public:
    Incremental(string inputFileName, string sortingMethod);
    virtual void calculateResult();
};

#endif //PROJECT22_P1_INCREMENTAL_H
