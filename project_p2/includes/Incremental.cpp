#include "Incremental.h"
//typedef std::vector<Point_2>::iterator pveciterator;

Incremental::Incremental(string inputFileName, string sortingMethod) : Polygon(inputFileName)
{
    sortedPoints = initialPoints;

    //initiliaze class inputs (sorting method)
    this->sortingMethod = sortingMethod;

    if(sortingMethod == "1a")
        sort(sortedPoints.begin(), sortedPoints.end(), function1);
    else if(sortingMethod == "1b")
        sort(sortedPoints.begin(), sortedPoints.end(), function2);
    else if(sortingMethod == "2a")
        sort(sortedPoints.begin(), sortedPoints.end(), function3);
    else if(sortingMethod == "2b")
        sort(sortedPoints.begin(), sortedPoints.end(), function4);

    //for(auto it = sortedPoints.begin(); it!= sortedPoints.end(); ++it)
     //   std::cout << *it << std::endl;
}




bool function1(Point_2 p1, Point_2 p2)
{
    return p1.x() < p2.x();
}

bool function2(Point_2 p1, Point_2 p2)
{
    return p1.x() > p2.x();
}

bool function3(Point_2 p1, Point_2 p2)
{
    return p1.y() < p2.y();
}

bool function4(Point_2 p1, Point_2 p2)
{
    return p1.y() > p2.y();
}



void Incremental::calculateResult()
{

    vector<K::Segment_2> redSegments;
    vector<K::Segment_2> SegmentstoBreak;
    vector<K::Segment_2> behindSegments;

    //for the first 3 points of sortedPoints, create convex hull polygon in result
    for(int i = 0; i<3;i++ )
        result.push_back(sortedPoints[i]);

    vector<K::Point_2> chull;
    const Polygon_2::Vertices& range = result.vertices();
    CGAL::convex_hull_2(range.begin(), range.end(), std::back_inserter(chull));

    result.clear();
    for(auto iter = chull.begin(); iter!= chull.end();++iter)
        result.push_back(*iter);

    int c=0;
    for(auto it = sortedPoints.begin(); it!= sortedPoints.end(); ++it, c++){

        chull.clear();

        if(c>2){

            //construct convex hull from result polygon
            const Polygon_2::Vertices& range = result.vertices();
            CGAL::convex_hull_2(range.begin(), range.end(), std::back_inserter(chull));

            Polygon_2 cpoints;
            for(auto iter = chull.begin(); iter!= chull.end();++iter)
                cpoints.push_back(*iter);


            //for all edges of convex hull if visible from point[i] add to redSegments
            redSegments.clear();
            for(const Segment_2& e  : cpoints.edges()){

                if(edgeVisible(e, *it, cpoints)){
                    redSegments.push_back(e);
                  //  std::cout << e << " added to red Segments" << std::endl;
                }
            }



            // for all edges in result if exist in redSegmenτ add it to segmentsToBreak
            SegmentstoBreak.clear();
            for(const Segment_2& e  : result.edges()){

                for(const Segment_2& rs  : redSegments){

                    if(e == rs){
                        SegmentstoBreak.push_back(e);
                      //  std::cout << e << " added to Segments to break" << std::endl;
                        break;
                    }
                }
            }

            int flag=0;
            //if segmentsToBreak is empty, do
            if (SegmentstoBreak.empty()){

                for(const Segment_2& rs  : redSegments){

                    //Adding edges from behind the (convex hull) red edge
                    int eflag=0;
                    for(const Segment_2& e  : result.edges()){

                        if(e.source() == rs.source())
                            eflag=1;

                        if(eflag==1){

                            behindSegments.push_back(e);
                            if(e.target() == rs.target()){
                                eflag==0;
                                break;
                            }
                        }
                    }

                    //Checking for a behind red Segment edge and visible
                    for(const Segment_2& e  : result.edges()){

                        if((std::find(behindSegments.begin(), behindSegments.end(), e) != behindSegments.end()) && (edgeVisible(e,*it,result))){
                            SegmentstoBreak.push_back(e);
                            flag=1;
                            break;
                        }
                    }

                    behindSegments.clear();
                    if(flag==1)
                        break;
                }
            }


            //remove segmentsToBreak[0] add point[i] add segmentsToBreak[0]


            std::vector<Point_2>::iterator iter;
            for (iter=result.begin(); iter!=result.end(); ++iter){

                if(*iter == SegmentstoBreak[0].target()){

                    result.erase(iter);
                    result.insert(iter,*it);

                    iter++;
                    result.insert(iter,SegmentstoBreak[0].target());

                    break;
                }
            }
        }
    }

}
