#ifndef PGMimageProcessor_H_
#define PGMimageProcessor_H_
#include <string>
#include <vector>
#include "connectedComponent.hpp"
using namespace std;

class PGMimageProcessor
{
public:
    // what is the big 6?
    PGMimageProcessor(string inputFilename);
    ~PGMimageProcessor();
    int extractComponents(unsigned char threshold, int minValidSize);
    int filterComponentsBySize(int minSize, int maxSize);
    bool writeComponents(const std::string &outFileName);
    int getComponentCount(void) const;
    int getLargestSize(void) const;
    int getSmallestSize(void) const;
    void printComponentData(const connectedComponent &theComponent) const;

private:
    // container : smart pointers to each ConnectedComponent
};

#endif

// iterate(with a container iterator) through your collection of detected components
//     and write them back out to produce a PGM image with only the selected components
//     present(as pixels values = 255 and all other values set to pixel value = 0)
//         .

// a copy constructor :
//        X(const X &)
// a copy assignment :
//        operator=(const X &)
// a move constructor :
//        X(X &&)
// a move assignment :
//        operator=(X &&)