//
//  Helpers.cpp
//  ChampionRun
//
//  Created by MHD Yamen Saraiji on 10/27/13.
//
//

#include "Helpers.h"

float rand01()
{
    return (float)rand()/(float)RAND_MAX;
}
float randRange(float min,float max)
{
    return rand01()*(max-min)+min;
}