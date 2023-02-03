#include <qapplication.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Viewer.h"

using namespace std;

// int originalMain(int argc, char **argv)
// {
//   // Read command lines arguments.
//   QApplication application(argc, argv);
//   // Instantiate the viewer.
//   Viewer viewer = Viewer();
//   // Give a name
//   viewer.setWindowTitle("Viewer triangle soup");
//   // Make the viewer window visible on screen.
//   viewer.show();
//   // Run main loop.
//   application.exec();
//   return 0;
// }

int PrintQ1(int argc, char **argv)
{
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

  cout << "le nombre de triangles est : " << iSoup.triangles.size() << endl;

  return 0;
}

int PrintQ2(int argc, char **argv)
{
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
  TriangleSoup iSoupOut;
  Index size = Index(50, 50, 50);
  iSoup.read(input);
  // question 3.3 compression bunny

  TriangleSoupZipper zipper = TriangleSoupZipper(iSoup, iSoupOut, size);
  zipper.smartZip();

  Viewer viewer(&iSoupOut);

  viewer.setWindowTitle("Viewer triangle soup");

  input.close();
  viewer.show();
  application.exec();

  return 0;
}

int main(int argc, char **argv)
{
  PrintQ1(argc, argv);
  //PrintQ2(argc, argv);
}
