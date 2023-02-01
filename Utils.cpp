// Utils.cpp

#include "Utils.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
using namespace std;

// Class Vecteur

Vecteur::Vecteur(float x, float y, float z)
{
    xyz[0] = x;
    xyz[1] = y;
    xyz[2] = z;
}

Vecteur::Vecteur() : Vecteur(0, 0, 0) {}

float Vecteur::operator[](int i) const { return xyz[i]; }

float &Vecteur::operator[](int i) { return xyz[i]; }

// Retourne le vecteur dont les composantes sont les minima des
// composantes de soi-même et de other.
Vecteur Vecteur::inf(const Vecteur &other) const
{
    Vecteur res;
    for (int i = 0; i < 3; i++)
    {
        res[i] = min(xyz[i], other[i]);
    }
    return res;
}
// Retourne le vecteur dont les composantes sont les maxima des
// composantes de soi-même et de other.
Vecteur Vecteur::sup(const Vecteur &other) const
{
    Vecteur res;
    for (int i = 0; i < 3; i++)
    {
        res[i] = max(xyz[i], other[i]);
    }
    return res;
}

// produit vectoriel
Vecteur Vecteur::cross(const Vecteur &other) const
{
    return Vecteur(
        xyz[1] * other[2] - xyz[2] * other[1],
        xyz[2] * other[0] - xyz[0] * other[2],
        xyz[0] * other[1] - xyz[1] * other[0]);
}

// normalise le vecteur
void Vecteur::normalize()
{
    float norm = sqrt(xyz[0] * xyz[0] + xyz[1] * xyz[1] + xyz[2] * xyz[2]);
    for (int i = 0; i < 3; i++)
    {
        xyz[i] = xyz[i] / norm;
    }
}

// soustraction de vecteurs
Vecteur Vecteur::operator-(const Vecteur &other) const
{
    Vecteur res;
    for (int i = 0; i < 3; i++)
    {
        res[i] = xyz[i] - other[i];
    }
    return res;
}

std::ostream &operator<<(std::ostream &out, Vecteur v)
{
    out << v[0] << " " << v[1] << " " << v[2];
    return out;
}
std::istream &operator>>(std::istream &in, Vecteur &v)
{
    in >> v[0] >> v[1] >> v[2];
    return in;
}

// Class Triangle

Triangle::Triangle(Vecteur s1, Vecteur s2, Vecteur s3) : sommet1(s1), sommet2(s2), sommet3(s3) {}
Triangle::Triangle() : Triangle(Vecteur(), Vecteur(), Vecteur()) {}
Vecteur Triangle::getSommet1() const { return sommet1; }
Vecteur Triangle::getSommet2() const { return sommet2; }
Vecteur Triangle::getSommet3() const { return sommet3; }

Vecteur Triangle::normal() const
{
    // return (sommet2 - sommet1).cross(sommet3 - sommet1);
    Vecteur u = getSommet2() - getSommet1();
    Vecteur v = getSommet3() - getSommet1();
    Vecteur normal = u.cross(v);
    normal.normalize();
    return normal;
}

std::ostream &operator<<(std::ostream &out, Triangle t)
{
    out << t.getSommet1() << " " << t.getSommet2() << " " << t.getSommet3();
    return out;
}

std::istream &operator>>(std::istream &in, Triangle &t)
{
    Vecteur s1, s2, s3;
    in >> s1 >> s2 >> s3;
    t = Triangle(s1, s2, s3);
    return in;
}

TriangleSoup::TriangleSoup() {}
void TriangleSoup::read(std::istream &in)
{
    std::string line;
    while (std::getline(in, line))
    {
        std::istringstream iss(line);
        Triangle t;
        if (iss >> t)
        {
            triangles.push_back(t);
        }
    }
}

void TriangleSoup::boundingBox(Vecteur &low, Vecteur &up) const
{
    low = triangles[0].getSommet1();
    up = triangles[0].getSommet1();
    for (int i = 0; i < triangles.size(); i++)
    {
        low = low.inf(triangles[i].getSommet1());
        low = low.inf(triangles[i].getSommet2());
        low = low.inf(triangles[i].getSommet3());
        up = up.sup(triangles[i].getSommet1());
        up = up.sup(triangles[i].getSommet2());
        up = up.sup(triangles[i].getSommet3());
    }
}

// TriangleSoupZipper et Index

TriangleSoupZipper::TriangleSoupZipper(const TriangleSoup &anInput, TriangleSoup &anOutput, Index size)
    : input(anInput), output(anOutput), size(size)
{
    Vecteur low, up;
    input.boundingBox(low, up);

    // Calcul des tailles réelles de chaque cellule
    xSize = (up[0] - low[0]) / size[0];
    ySize = (up[1] - low[1]) / size[1];
    zSize = (up[2] - low[2]) / size[2];
}

Index TriangleSoupZipper::index(const Vecteur &p) const
{
    Vecteur low, up;
    input.boundingBox(low, up);
    return Index(
        (p[0] - low[0]) / xSize,
        (p[1] - low[1]) / ySize,
        (p[2] - low[2]) / zSize);
}

Vecteur TriangleSoupZipper::centroid(const Index &idx) const
{
    Vecteur low, up;
    input.boundingBox(low, up);
    return Vecteur(
        low[0] + (idx[0] + 0.5) * xSize,
        low[1] + (idx[1] + 0.5) * ySize,
        low[2] + (idx[2] + 0.5) * zSize);
}
