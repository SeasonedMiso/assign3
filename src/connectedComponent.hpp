#ifndef connectedComponent_H_
#define connectedComponent_H_
#include <string>
#include <vector>
using namespace std;

// stored in vector or list
class connectedComponent
{
public:
   // connectedComponent();
   ~connectedComponent();
   void addCoords(pair<int, int> coords);
   int id;
   int getPixelCount() const;
   vector<pair<int, int>> getCoords() const;
   connectedComponent();
   connectedComponent(const connectedComponent &orig);
   connectedComponent &operator=(const connectedComponent &orig);
   // void IDincrement();
   // getters and setters
protected:
   static int nextID;

private:
   int pixelCount;
   vector<pair<int, int>> coordinates;
};
#endif