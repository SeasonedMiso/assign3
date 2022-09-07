// #include ".hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "PGMimageProcessor.hpp"

using namespace std;

// ./out/findcomp -s 1 2 -t 3 -p -w out.pgm

bool fileExists(char *fileName)
{
    ifstream infile(fileName);
    return infile.good();
}
void badArg()
{
    cout << "error: user provided bad arguement";
    exit(1);
}
void badIn()
{
    cout << "error: bad input file";
    exit(1);
}
bool checkIntArgs(int argNum, int i, char *argv[], int *resArray)
{
    bool badConversion = false;
    for (int j = 1; j < argNum + 1; j++)
    {
        if (strcmp(to_string(atoi(argv[i + j])).c_str(), argv[i + j]) == 0)
        {
            resArray[j - 1] = atoi(argv[i + j]);
        }
        else
        {
            badConversion = true;
        }
    }
    if (!badConversion)
    {
        for (int j = 0; j < argNum; j++)
        {
            return true;
        }
    }
    return false;
}
int main(int argc, char *argv[])
{
    char *inFilename = argv[1];
    int argsRead = 2;
    int sArgs[2];
    int tArg[1];
    bool pArg;
    string wArg;
    for (int i = 0; i < 2; i++)
    {
        sArgs[i] = 0;
    }
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-t") == 0)
        {
            argsRead += 2;
            if (argc < argsRead)
            {
                badArg();
            }
            if (checkIntArgs(1, i, argv, tArg))
            {
                i += 1;
            }
            else
            {
                badArg();
            }
        }
        if (strcmp(argv[i], "-s") == 0)
        {
            argsRead += 3;
            if (argc < argsRead)
            {
                badArg();
            }
            if (checkIntArgs(2, i, argv, sArgs))
            {
                i += 2;
            }
            else
            {
                badArg();
            }
        }
        if (strcmp(argv[i], "-w") == 0)
        {
            argsRead++;
            if (argc < argsRead)
            {
                badArg();
            }
            wArg = argv[i + 1];
        }
        if (strcmp(argv[i], "-p") == 0)
        {
            argsRead++;
            if (argc < argsRead)
            {
                badArg();
            }
            pArg = argv[i + 1];
        }
    }
    cout << "sArgs:" << endl;
    for (int i = 0; i < 2; i++)
    {
        cout << sArgs[i] << endl;
    }
    PGMimageProcessor *a = new PGMimageProcessor(inFilename);

    // a->makeFrames(tResultArr, sResultArr, wResultVecArray, inFilename);
    // cout << (int)a->imageSequence[0][0][0];
    delete (a);
}

// findcomp[options]<inputPGMfile>
// where<inputPGMfile> is a valid PGM image and valid options

// - s<int><int>(-s min max); set the minimum and maximum valid components size
// [min default = 3, max = image width*img height i.e. unlimited]

// -t <int> set the threshold for component detection (default=128, limit to [0. . . 255])

// -p print out all the component data (entries do not have to be sorted) as well as the total
// component number and the sizes of the smallest and largest components.

// -w <outPGMfile> write out all retained components (as foreground/background pixels)
// to a new PGM file, <outPGMfile>