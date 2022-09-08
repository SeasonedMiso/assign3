#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "ConnectedComponent.hpp"
using namespace std;

int ConnectedComponent::nextID = 0;
ConnectedComponent::ConnectedComponent()
{
    pixelCount = 0;
    vector<pair<int, int>> coordinates;
    // id = ++nextID;
}
ConnectedComponent::ConnectedComponent(const ConnectedComponent &orig)
{
    id = orig.id;
}

ConnectedComponent &ConnectedComponent::operator=(const ConnectedComponent &orig)
{
    id = orig.id;
    return (*this);
}
ConnectedComponent::~ConnectedComponent()
{
    ;
}
void ConnectedComponent::addCoords(pair<int, int> coords)
{
    coordinates.push_back(coords);
    pixelCount++;
}
int ConnectedComponent::getPixelCount() const
{
    return pixelCount;
}
vector<pair<int, int>> ConnectedComponent::getCoords() const
{
    return coordinates;
}
