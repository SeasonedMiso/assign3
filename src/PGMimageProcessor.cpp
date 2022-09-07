#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include "PGMimageProcessor.hpp"
using namespace std;

PGMimageProcessor::PGMimageProcessor(argStructure inArgs)
{
    args.inFilename = inArgs.inFilename;
    args.printArg = inArgs.printArg;
    args.writeArg = inArgs.writeArg;
    args.threshArg[0] = inArgs.threshArg[0];
    for (int i = 0; i < 2; i++)
    {
        args.sizeArgs[i] = inArgs.sizeArgs[i];
    }
    pgm = (PGMImage *)malloc(sizeof(PGMImage));
    if (openPGM(pgm, inArgs.inFilename))
    {
        closePGM(pgm);
    }
}
PGMimageProcessor::~PGMimageProcessor()
{
    delete (pgm);
}
int PGMimageProcessor::extractComponents(unsigned char threshold, int minValidSize)
{
    PGMImage *copy = clonePGM(pgm);

    pair<int, int> coordinate = {20, 20};
    BFS(copy, (int)threshold, coordinate);
    // for (int y = 0; y < pgm->height; y++)
    // {
    //     for (int x = 0; x < pgm->width; x++)
    //     {
    //         // copy pgm
    //         if ((int)pgm->data[y][x] >= (int)threshold)
    //         {
    //             // conenctedCoords coordinates
    // pair<int, int> coordinate = {y, x};
    // BFS(copy, (int)threshold, coordinate);
    //         }
    //         // inputs >= threshold value
    //     }
    //     // closePGM(copy);
    //     // delete (copy);
    // }
    // start at the top left pixel of the image
    // scan along the image rows until you hit a foreground pixel
    // start a Breadth First Search (BFS):
    // determine all 4-connected foreground pixels that are attached to this
    // (this is effectively a ‘floodfill’ algorithm).
    // you check all possible 4-connected neighbours (N/S/E/W)
    // if a neighbour is 255, and not yet processed,
    // add it to your component, pushing it’s non-tested N/S/E/W neighbour
    // coordinates onto a queue (initially empty).
    // set the current foreground pixel added to your component to 0 in the thresholded image
    //  The BFS continues, popping off candidate pixel coordinates from the queue,
    // and expanding/testing those, until the queue has been exhausted.

    // Then you can continue
    // scanning from where you initially started building the component, looking for the starting
    // ‘seed’ for next component. Each new component should increase the component identifier
    // (just start at 0). You can optimize the process described above, but it should work well
    // enough as is. Once you have extracted the components, you should delete the
    // memory used to hold the PGM input image, UNLESS you re-use the memory
    // to create the output image.

    /* process the input image to extract all the connected components,
based on the supplied threshold (0...255) and excluding any components
of less than the minValidSize. The final number of components that
you store in your container (after discarding undersized one)
must be returned.
*/

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

bool PGMimageProcessor::writePGM(PGMImage *pgm,
                                 const char *filename)
{
    // write header
    ofstream myfile(filename, ios::binary);
    myfile.write("P5\n", 3);
    myfile.write(to_string(pgm->width).c_str(), to_string(pgm->width).length());
    myfile.put(' ');
    myfile.write(to_string(pgm->height).c_str(), to_string(pgm->height).length());
    myfile.write("\n255\n", 5);
    // write contents
    for (int i = 0;
         i < pgm->height; i++)
    {
        myfile.write((char *)pgm->data[i], (pgm->width));
    }
    myfile.close();
    return false;
}
void PGMimageProcessor::commentParse(FILE *filePointer)
{
    int ch;
    char line[100];
    // Ignore any blank lines or comments
    while ((ch = fgetc(filePointer)) != EOF && isspace(ch))
    {
        ;
    }
    if (ch == '#')
    {
        fgets(line, sizeof(line), filePointer);
        commentParse(filePointer);
    }
    else
        fseek(filePointer, -1, SEEK_CUR);
}

bool PGMimageProcessor::openPGM(PGMImage *pgm,
                                const char *filename)
{
    FILE *pgmFile = fopen(filename, "rb");
    // Check for file
    if (pgmFile == NULL)
    {
        printf("File not found\n");
        return false;
    }
    commentParse(pgmFile);

    // Parse header
    fscanf(pgmFile, "%s",
           pgm->pgmType);
    commentParse(pgmFile);
    fscanf(pgmFile, "%d %d",
           &(pgm->width),
           &(pgm->height));
    commentParse(pgmFile);
    fscanf(pgmFile, "%d", &(pgm->maxValue));
    commentParse(pgmFile);

    // Allocate memory
    pgm->data = (unsigned char **)malloc(pgm->height * sizeof(unsigned char *));
    // Store data
    if (pgm->pgmType[1] == '5')
    {
        fgetc(pgmFile);
        for (int i = 0;
             i < pgm->height; i++)
        {
            pgm->data[i] = (unsigned char *)malloc(pgm->width * sizeof(unsigned char));
            if (pgm->data[i] == NULL)
            {
                fprintf(stderr,
                        "malloc failed\n");
                exit(1);
            }
            fread(pgm->data[i],
                  sizeof(unsigned char),
                  pgm->width, pgmFile);
        }
    }
    fclose(pgmFile);
    return true;
}
void PGMimageProcessor::closePGM(PGMImage *pgm)
{
    // deallocate image;
    for (int i = 0; i < pgm->height; i++)
    {
        delete (pgm->data[i]);
    }
    delete (pgm->data);
    return;
}

PGMImage *PGMimageProcessor::clonePGM(PGMImage *pgm)
{
    PGMImage *newPgm = (PGMImage *)malloc(sizeof(PGMImage));
    newPgm->data = (unsigned char **)malloc(pgm->height * sizeof(unsigned char *));
    for (int i = 0; i < pgm->height; i++)
    {
        newPgm->data[i] = (unsigned char *)malloc(pgm->width * sizeof(unsigned char));
        for (int j = 0; j < pgm->width; j++)
        {
            newPgm->data[i][j] = (u_char)255;
        }
    }
    return newPgm;
}
// PGMImage *PGMimageProcessor::clonePGM(PGMImage *pgm)
// {
//     PGMImage *newPgm = (PGMImage *)malloc(sizeof(PGMImage));
//     newPgm->data = (unsigned char **)malloc(pgm->height * sizeof(unsigned char *));
//     for (int i = 0; i < pgm->height; i++)
//     {
//         newPgm->data[i] = (unsigned char *)malloc(pgm->width * sizeof(unsigned char));
//     }
// }
void PGMimageProcessor::BFS(PGMImage *pgmChecked, int threshold, pair<int, int> coordInit)
{
    queue<pair<int, int>> coordQueue;
    coordQueue.push(coordInit);
    // pgm[coord.second][coord.first];
    // pgmChecked->data[coord.second][coord.first] = (u_char)0;
    connectedComponent *newCC = new connectedComponent;
    // queue
    pgmChecked->data[coordInit.first][coordInit.second] = (u_char)0;
    while (coordQueue.size() > 0)
    {
        pair<int, int> coord = coordQueue.front();
        // check not gong out of data bounds
        if ((coord.first + 1 <= pgmChecked->width) && (pgmChecked->data[coord.first + 1][coord.second] == (u_char)255) && ((int)pgm->data[coord.first + 1][coord.second] <= threshold))
        {
            pgmChecked->data[coord.first][coord.second] = (u_char)0;
            newCC->addCoords({coord.first + 1, coord.second});
            coordQueue.push({coord.first + 1, coord.second});
        }
        cout << coordQueue.back().first << " " << coordQueue.back().second << endl;
        if ((coord.first - 1 >= 0) && (pgmChecked->data[coord.first - 1][coord.second] == (u_char)255) && ((int)pgm->data[coord.first - 1][coord.second] <= threshold))
        {
            pgmChecked->data[coord.first - 1][coord.second] = (u_char)0;
            newCC->addCoords({coord.first - 1, coord.second});
            coordQueue.push({coord.first - 1, coord.second});
        }
        cout << coordQueue.back().first << " " << coordQueue.back().second << endl;
        if ((coord.second + 1 <= pgmChecked->height) && (pgmChecked->data[coord.first][coord.second + 1] == (u_char)255) && ((int)pgm->data[coord.first][coord.second + 1] <= threshold))
        {
            pgmChecked->data[coord.first][coord.second + 1] = (u_char)0;
            newCC->addCoords({coord.first, coord.second + 1});
            coordQueue.push({coord.first, coord.second + 1});
        }
        cout << coordQueue.back().first << " " << coordQueue.back().second << endl;
        if ((coord.second - 1 >= 0) && (pgmChecked->data[coord.first][coord.second - 1] == (u_char)255) && ((int)pgm->data[coord.first][coord.second - 1] <= threshold))
        {
            pgmChecked->data[coord.first][coord.second - 1] = (u_char)0;
            newCC->addCoords({coord.first, coord.second - 1});
            coordQueue.push({coord.first, coord.second - 1});
        }
        coordQueue.pop();
        // cout << coordQueue.back().first
        cout << coordQueue.back().first << " " << coordQueue.back().second << endl;

        // check all 4 directions for if not checked and if above threshold
        // add it to your component,
        // pushing it’s non - tested N / S / E / W neighbour coordinates onto a queue(initially empty).
    }
}