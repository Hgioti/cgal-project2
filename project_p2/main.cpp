#include <iostream>
#include <sys/types.h>
#include <sys/time.h>
#include "includes/Incremental.h"
#include "includes/ConvexHull.h"
#include "includes/Polygon.h"
#include <string.h>


using namespace std;

int main(int argc, char** argv)
{
    //Read arguments from user and check them
    string inputFileName,outputFileName,edgeSelection,algorithm,sort,globalopt,annealing;
    int max,min,L;
    double thres;


    if (argc != 17) {
            printf("Please give correct number of arguements\n");
            return -1;
    }

    if( (strcmp(argv[1],"-i") != 0)  || (strcmp(argv[3],"-o") != 0) || (strcmp(argv[5],"-algorithm") != 0) || (strcmp(argv[7],"-L") != 0) || (strcmp(argv[9],"-max") != 0) ||
     (strcmp(argv[11],"-min") != 0) ||  (strcmp(argv[13],"-threshold") != 0) || (strcmp(argv[15],"-annealing") != 0) ){
        cout << "Wrong input" << endl;
        return -1;
    }

    FILE *fp;
    fp = fopen(argv[2], "r");
    if( fp == NULL ) {
       perror("Error: ");
       return(-1);
    }
    fclose(fp);


    inputFileName = argv[2];
    outputFileName = argv[4];
    globalopt = argv[6];
    L = atoi(argv[8]);
    max = atoi(argv[10]);
    min = atoi(argv[12]);
    thres = atoi(argv[14]);
    annealing = argv[16];

    if(((max != 1) && (min != 1)) || (L > 10) || (L < 0)){
        cout << "Wrong input" << endl;
        return -1;
    }



    algorithm = "incremental";
    sort = "1a";

    Polygon *polygon = NULL;
    if (algorithm == "incremental")
        polygon = new Incremental(inputFileName, sort);



    

    //Start timer
    timeval start;
    gettimeofday(&start, NULL);
    //Calculate result
    polygon->calculateResult();
    polygon->getRatio();

    if(globalopt == "local_search"){

            if(max == 1)
                polygon->LocalSearchMax(L,thres);
             else if(min == 1)
                polygon->LocalSearchMin(L,thres);
    }



    //Stop timer
    timeval stop;
    gettimeofday(&stop, NULL);

    //Print information
    

    double elapsedTime = (stop.tv_sec - start.tv_sec) * 1000.0 + (stop.tv_usec - start.tv_usec) / 1000.0;

    polygon->printInfo(outputFileName,globalopt,max,elapsedTime);
    cout << "construction time: " << (int)elapsedTime << endl;


    if (polygon)
        delete polygon;

    return 0;
}