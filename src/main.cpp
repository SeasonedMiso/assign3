// #include ".hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    ;
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