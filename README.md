# assign3

main.cpp takes user input, and makes sure it is valid, then creates an instance of the PGMimageProcessor class, and calls various methods from it.

The PGMimageProcessor.cpp contains all of the neccessary methods to parse a PGM file, extract components, and write it back out, as well as methods to return the maximum or minimum size components extracted, or return the number of components within a size range.

The components themselves are defined in ConnectedComponents.cpp, which defines unique id numbers for each component as well as methods to add new coordinates, and get the total number of coordinates in the object.

unit tests
catch.hpp

example input:
./out/findcomp - s 1 200000 - t 199 - p - w out.pgm ./resources/examples/penguin.pgm

---

Data Flow
---basic

user
(args, pgmFile)
↓
main
↓
PGMimageProcessor

-

where:
args = {
s = [int minSize, int maxSize],
t = int detectionThresh,
p = bool print?,
w = string outFilename
}

---PGMimageProcessor

getInputFile
↓
extract connectedComponents // pointers in connectedComponentsContainer
↓
{writeComponents(const std: : string & outFileName)
getComponentCount(void)
getLargestSize
getSmallestSize
printComponentData
filterComponentsBySize}
