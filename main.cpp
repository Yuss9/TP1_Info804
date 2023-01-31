#include <qapplication.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Viewer.h"

using namespace std;
int main(int argc, char **argv)
{
  // // Read command lines arguments.
  // QApplication application(argc, argv);
  // // Instantiate the viewer.
  // Viewer viewer;
  // // Give a name
  // viewer.setWindowTitle("Viewer triangle soup");
  // // Make the viewer window visible on screen.
  // viewer.show();
  // // Run main loop.
  // application.exec();
  // return 0;


  // question 3.2 part2 affichage avec tref tri

  if (argc < 2)
  {
    std::cerr << "ERROR : missing file name" << std::endl;
    return -1;
  }

  std::ifstream input(argv[1]);
  if (!input.good())
  {
    std::cerr << "ERROR : could not open file" << std::endl;
    return -1;
  }

  QApplication application(argc, argv);
  TriangleSoup iSoup;
  iSoup.read(input);
  Viewer viewer(&iSoup);
  viewer.ptrSoup = &iSoup;
  viewer.setWindowTitle("Viewer triangle soup");
  input.close();
  viewer.show();
  application.exec();

  return 0;
}
