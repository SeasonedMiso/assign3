#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "connectedComponent.hpp"
using namespace std;

int connectedComponent::nextID = 0;
connectedComponent::connectedComponent()
{
    pixelCount = 0;
    vector<pair<int, int>> coordinates;
    id = ++nextID;
    // cout << id;
    // cout << componentID;
}
connectedComponent::connectedComponent(const connectedComponent &orig)
{
    id = orig.id;
}

connectedComponent &connectedComponent::operator=(const connectedComponent &orig)
{
    id = orig.id;
    return (*this);
}
connectedComponent::~connectedComponent()
{
    ;
}
void connectedComponent::addCoords(pair<int, int> coords)
{
    coordinates.push_back(coords);
}