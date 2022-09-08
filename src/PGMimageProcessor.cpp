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
        ;
    }
}
PGMimageProcessor::~PGMimageProcessor()
{
    closePGM(pgm);
    delete (pgm);
    for (int i = 0; i < compVec.size() - 1; i++)
    {
        delete (compVec.at(i));
    }
}
int PGMimageProcessor::extractComponents(unsigned char threshold, int minValidSize)
{
    PGMImage *copy = clonePGM(pgm);
    for (int y = 0; y < pgm->height; y++)
    {
        for (int x = 0; x < pgm->width; x++)
        {
            if ((int)pgm->data[y][x] >= (int)threshold && copy->data[y][x] == 255)
            {
                pair<int, int> coords = {y, x};
                compVec.push_back(BFS(copy, (int)threshold, coords));
            }
        }
    }
    closePGM(copy);
    delete (copy);
    return 0;
}
int PGMimageProcessor::filterComponentsBySize(int minSize, int maxSize)
{
    int count = 0;
    for (int i = 0; i < compVec.size() - 1; i++)
    {
        if (compVec.at(i)->getPixelCount() > minSize && compVec.at(i)->getPixelCount() < maxSize)
        {
            count++;
        }
    }
    return count;
}
bool PGMimageProcessor::writeComponents(const string &outFileName)
{
    try
    {
        PGMImage *copy = clonePGM(pgm);
        for (int i = 0; i < compVec.size() - 1; i++)
        {
            vector<pair<int, int>> currentComponent = compVec.at(i)->getCoords();
            for (int j = 0; j < compVec.at(i)->getPixelCount() - 1; j++)
            {
                pair<int, int> currentCoord = currentComponent[j];
                copy->data[currentCoord.first][currentCoord.second] = (u_char)0;
            }
        }
        writePGM(copy, ("./out/" + args.writeArg).c_str());
        closePGM(copy);
        delete (copy);
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
}
int PGMimageProcessor::getComponentCount(void) const
{
    return compVec.size();
}
int PGMimageProcessor::getLargestSize(void) const
{
    int maxSize = 0;
    for (int i = 0; i < compVec.size() - 1; i++)
    {
        if (compVec.at(i)->getPixelCount() > maxSize)
        {
            maxSize = compVec.at(i)->getPixelCount();
        }
    }
    return maxSize;
}
int PGMimageProcessor::getSmallestSize(void) const
{
    int minSize = compVec.at(0)->getPixelCount();
    for (int i = 1; i < compVec.size() - 1; i++)
    {
        if (compVec.at(i)->getPixelCount() < minSize)
        {
            minSize = compVec.at(i)->getPixelCount();
        }
    }
    return minSize;
}
void PGMimageProcessor::printComponentData(const ConnectedComponent &theComponent) const
{
    cout << "id: " << theComponent.id << endl;
    cout << "pixel count: " << theComponent.getPixelCount() << endl;
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
    newPgm->height = pgm->height;
    newPgm->maxValue = pgm->maxValue;
    newPgm->width = pgm->width;
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
ConnectedComponent *PGMimageProcessor::BFS(PGMImage *pgmChecked, int threshold, pair<int, int> coordInit)
{
    queue<pair<int, int>> coordQueue;
    coordQueue.push(coordInit);
    ConnectedComponent *newCC = new ConnectedComponent;
    pair<int, int> coord = coordQueue.front();
    newCC->addCoords({coord.first, coord.second});
    pgmChecked->data[coord.first][coord.second] = (u_char)0;

    while (coordQueue.size() > 0)
    {
        coord = coordQueue.front();
        if ((coord.first + 1 < pgmChecked->height - 1))
        {
            if ((pgmChecked->data[coord.first + 1][coord.second] == (u_char)255) && ((int)pgm->data[coord.first + 1][coord.second] >= threshold))
            {
                newCC->addCoords({coord.first + 1, coord.second});
                coordQueue.push({coord.first + 1, coord.second});
                pgmChecked->data[coord.first + 1][coord.second] = (u_char)0;
            }
        }
        if ((coord.first - 1 > 0))
        {
            if ((pgmChecked->data[coord.first - 1][coord.second] == (u_char)255) && ((int)pgm->data[coord.first - 1][coord.second] >= threshold))
            {
                newCC->addCoords({coord.first - 1, coord.second});
                coordQueue.push({coord.first - 1, coord.second});
                pgmChecked->data[coord.first - 1][coord.second] = (u_char)0;
            }
        }
        if (coord.second + 1 < pgmChecked->width - 1)
        {
            if ((pgmChecked->data[coord.first][coord.second + 1] == (u_char)255) && ((int)pgm->data[coord.first][coord.second + 1] >= threshold))
            {
                newCC->addCoords({coord.first, coord.second + 1});
                coordQueue.push({coord.first, coord.second + 1});
                pgmChecked->data[coord.first][coord.second + 1] = (u_char)0;
            }
        }
        if (coord.second - 1 > 0)
        {
            if ((pgmChecked->data[coord.first][coord.second - 1] == (u_char)255) && ((int)pgm->data[coord.first][coord.second - 1] >= threshold))
            {
                newCC->addCoords({coord.first, coord.second - 1});
                coordQueue.push({coord.first, coord.second - 1});
                pgmChecked->data[coord.first][coord.second - 1] = (u_char)0;
            }
        }
        coordQueue.pop();
    }
    return newCC;
}