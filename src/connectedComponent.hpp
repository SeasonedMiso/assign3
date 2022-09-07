#ifndef connectedComponent_H_
#define connectedComponent_H_
#include <string>
#include <vector>
using namespace std;

// stored in vector or list
class connectedComponent
{
public:
   connectedComponent();
   ~connectedComponent();
   // getters and setters

private:
   int pixelCount;
   int componentID;
   vector<pair<int, int>> coordinates;
};
#endif