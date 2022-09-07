// #include ".hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "PGMimageProcessor.hpp"

using namespace std;

// ./out/findcomp -s 1 2 -t 3 -p -w out.pgm
struct argStructure
{
    char *inFilename;
    int argsRead;
    int sizeArgs[2];
    int threshArg[1];
    bool printArg;
    string writeArg;
};

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
    // char *inFilename = argv[1];
    // int argsRead = 2;
    // int sizeArgs[2];
    // int threshArg[1];
    // bool printArg;
    // string writeArg;
    argStructure args;
    for (int i = 0; i < 2; i++)
    {
        args.sizeArgs[i] = 0;
    }
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-t") == 0)
        {
            args.argsRead += 2;
            if (argc < args.argsRead)
            {
                badArg();
            }
            if (checkIntArgs(1, i, argv, args.threshArg))
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
            args.argsRead += 3;
            if (argc < args.argsRead)
            {
                badArg();
            }
            if (checkIntArgs(2, i, argv, args.sizeArgs))
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
            args.argsRead++;
            if (argc < args.argsRead)
            {
                badArg();
            }
            args.writeArg = argv[i + 1];
        }
        if (strcmp(argv[i], "-p") == 0)
        {
            args.argsRead++;
            if (argc < args.argsRead)
            {
                badArg();
            }
            args.printArg = argv[i + 1];
        }
    }
    cout << "sArgs:" << endl;
    for (int i = 0; i < 2; i++)
    {
        cout << args.sizeArgs[i] << endl;
    }
    PGMimageProcessor *a = new PGMimageProcessor(args);

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