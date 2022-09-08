#ifndef ConnectedComponent_H_
#define ConnectedComponent_H_
#include <string>
#include <vector>
using namespace std;

// stored in vector or list
class ConnectedComponent
{
public:
   ConnectedComponent();
   ~ConnectedComponent();
   void addCoords(pair<int, int> coords);
   int id;
   int getPixelCount() const;
   vector<pair<int, int>> getCoords() const;
   ConnectedComponent();
   ConnectedComponent(const ConnectedComponent &orig);
   ConnectedComponent &operator=(const ConnectedComponent &orig);

protected:
   static int nextID;

private:
   int pixelCount;
   vector<pair<int, int>> coordinates;
};
#endif