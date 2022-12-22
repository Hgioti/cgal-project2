#ifndef PROJECT22_P1_POLYGON_H
#define PROJECT22_P1_POLYGON_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/property_map.h>
#include <CGAL/convex_hull_2.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/Arrangement_2.h>
#include <CGAL/property_map.h>
#include <CGAL/intersections.h>
#include <CGAL/Circular_kernel_intersections.h>
#include <CGAL/Convex_hull_traits_adapter_2.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Polygon_2<K> Polygon_2;
typedef K::Segment_2 Segment_2;
typedef K::Point_2 Point_2;
typedef K::Intersect_2 Intersect_2;


class Polygon
{
protected:
    vector<K::Point_2> initialPoints;
    double area,ratio;
    Polygon_2 result;
public:
    Polygon(string inputFileName);
    virtual ~Polygon() {}
    virtual void calculateResult() = 0;
    void printInfo(string,string,int,double);
    void LocalSearchMax(int,double);
    void LocalSearchMin(int,double);
    void getRatio();
    string simpleOrNot();
};
bool edgeVisible(const Segment_2& edge, Point_2 point,Polygon_2 pol);
#endif
