#ifndef PGMimageProcessor_H_
#define PGMimageProcessor_H_
#include <string>
#include <vector>
#include "ConnectedComponent.hpp"
using namespace std;

typedef struct argStructure
{
    char *inFilename;
    int sizeArgs[2];
    int threshArg[1];
    bool printArg;
    string writeArg;
} argStructure;
typedef struct PGMImage
{
    char pgmType[3];
    unsigned char **data;
    unsigned int width;
    unsigned int height;
    unsigned int maxValue;
} PGMImage;

class PGMimageProcessor
{
public:
    // what is the big 6?
    PGMimageProcessor(argStructure args);
    ~PGMimageProcessor();
    int extractComponents(unsigned char threshold, int minValidSize);
    int filterComponentsBySize(int minSize, int maxSize);
    bool writeComponents(const string &outFileName);
    int getComponentCount(void) const;
    int getLargestSize(void) const;
    int getSmallestSize(void) const;
    void printComponentData(const ConnectedComponent &theComponent) const;
    bool openPGM(PGMImage *pgm,
                 const char *filename);
    void commentParse(FILE *filePointer);
    bool writePGM(PGMImage *pgm,
                  const char *filename);
    void closePGM(PGMImage *pgm);
    PGMImage *clonePGM(PGMImage *pgm);
    ConnectedComponent *BFS(PGMImage *pgmThresh, int threshold, pair<int, int> coord);

private:
    // container : smart pointers to each ConnectedComponent
    argStructure args;
    PGMImage *pgm;
    vector<ConnectedComponent*> compVec;
};

#endif

// a copy constructor :
//        X(const X &)
// a copy assignment :
//        operator=(const X &)
// a move constructor :
//        X(X &&)
// a move assignment :
//        operator=(X &&)