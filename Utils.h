// Utils.h
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

struct Vecteur
{
    float xyz[3];                       // les composantes
    Vecteur(float x, float y, float z); // constructeur
    Vecteur();                          // constructeur par defaut
    float operator[](int i) const;      // accesseur en lecture
    float &operator[](int i);           // accesseur en ecriture
};
std::ostream &operator<<(std::ostream &out, Vecteur v);
std::istream &operator>>(std::istream &in, Vecteur &v);

class Triangle
{
public:
    Triangle(Vecteur s1, Vecteur s2, Vecteur s3);
    Triangle();
    Vecteur getSommet1() const;
    Vecteur getSommet2() const;
    Vecteur getSommet3() const;

private:
    Vecteur sommet1, sommet2, sommet3;
};

std::ostream &operator<<(std::ostream &out, Triangle t);
std::istream &operator>>(std::istream &in, Triangle &t);

struct TriangleSoup
{
    std::vector<Triangle> triangles; // les triangles
    TriangleSoup();
    void read(std::istream &in);
};