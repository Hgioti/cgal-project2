#include "ConvexHull.h"

ConvexHull::ConvexHull(string inputFileName, string edgeSelection) : Polygon(inputFileName)
{
    //initialize convex hull parameters
    this->edgeSelection = edgeSelection;
}

bool ConvexHull::collinear(Point_2 a, Point_2 b, Point_2 c)
{
    //returns true if a, b, c are collinear. If convex hull area is 0, then a, b and c are collinear
    return true;
}

void ConvexHull::calculateResult()
{

}
