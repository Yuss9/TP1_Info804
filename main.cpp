#include <qapplication.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Viewer.h"
#include "Utils.h"

using namespace std;
int main(int argc, char **argv)
{
  // // Read command lines arguments.
  // QApplication application(argc,argv);
  // // Instantiate the viewer.
  // Viewer viewer;
  // // Give a name
  // viewer.setWindowTitle("Viewer triangle soup");
  // // Make the viewer window visible on screen.
  // viewer.show();
  // // Run main loop.
  // application.exec();
  // return 0;

  if (argc < 2)
  {
    std::cerr << "ERROR : missing file name" << std::endl;
    return -1;
  }

  cout<<argv[1]<<endl;

  std::ifstream input(argv[1]);
  if (!input.good())
  {
    std::cerr << "ERROR : could not open file" << std::endl;
    return -1;
  }

  TriangleSoup soup;
  soup.read(input);

  input.close();

  cout<<"jai fini de lire"<<endl;

  cout<<soup.triangles.size()<<endl;

  return 0;
}
