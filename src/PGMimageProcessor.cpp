#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "PGMimageProcessor.hpp"
using namespace std;

PGMimageProcessor::PGMimageProcessor(argStructure args)
{
    ;
}
PGMimageProcessor::~PGMimageProcessor()
{
    ;
}
int PGMimageProcessor::extractComponents(unsigned char threshold, int minValidSize)
{ /* process the input image to extract all the connected components,
based on the supplied threshold (0...255) and excluding any components
of less than the minValidSize. The final number of components that
you store in your container (after discarding undersized one)
must be returned.
*/

    // There are multiple ways to do this. The easiest is to start at the top left pixel of the
    // image and scan along the image rows until you hit a foreground pixel. At that point
    // you can start a Breadth First Search (BFS) to determine all 4-connected foreground
    // pixels that are attached to this (this is effectively a ‘floodfill’ algorithm). Essentially,
    // you check all possible 4-connected neighbours (N/S/E/W) and if a neighbour is 255, and
    // not yet processed, add it to your component, pushing it’s non-tested N/S/E/W neighbour
    // coordinates onto a queue (initially empty). You need to take care to set the current
    // foreground pixel added to your component to 0 in the thresholded image, so you don’t
    // revisit it. The BFS continues, popping off candidate pixel coordinates from the queue,
    // and expanding/testing those, until the queue has been exhausted. Then you can continue
    // scanning from where you initially started building the component, looking for the starting
    // ‘seed’ for next component. Each new component should increase the component identifier
    // (just start at 0). You can optimize the process described above, but it should work well
    // enough as is. Once you have extracted the components, you should delete the
    // memory used to hold the PGM input image, UNLESS you re-use the memory
    // to create the output image.

    ;
    return 0;
}
int PGMimageProcessor::filterComponentsBySize(int minSize, int maxSize)
{
    ;
    /* iterate - with an iterator - though your container of connected
components and filter out (remove) all the components which do not
obey the size criteria pass as arguments. The number remaining
after this operation should be returned.
*/
    return 0;
}
bool PGMimageProcessor::writeComponents(const std::string &outFileName)
{
    ;
    /* create a new PGM file which contains all current components
(255=component pixel, 0 otherwise) and write this to outFileName as a
valid PGM. the return value indicates success of operation
*/
    return false;
}
int PGMimageProcessor::getComponentCount(void) const
{
    ;
    // return number of components
    return 0;
}
int PGMimageProcessor::getLargestSize(void) const
{
    ;
    // return number of pixels in largest component
    return 0;
}
int PGMimageProcessor::getSmallestSize(void) const
{
    ;
    // return number of pixels in smallest component
    return 0;
}
void PGMimageProcessor::printComponentData(const connectedComponent &theComponent) const
{
    ;
    /* print the data for a component to std::cout
    see ConnectedComponent class;
    print out to std::cout: component ID, number of pixels
    */
}
