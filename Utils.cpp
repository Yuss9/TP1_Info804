// Utils.cpp

#include "Utils.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <ostream>
#include <vector>

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
    return Vecteur((*this)[1] * (other[2]) - (*this)[2] * other[1],
                   (*this)[2] * other[0] - (*this)[0] * other[2],
                   (*this)[0] * other[1] - (*this)[1] * other[0]);
}

// normalise le vecteur
Vecteur Vecteur::normalize()
{
    float norm = sqrt(xyz[0] * xyz[0] + xyz[1] * xyz[1] + xyz[2] * xyz[2]);
    for (int i = 0; i < 3; i++)
    {
        xyz[i] = xyz[i] / norm;
    }
    return *this;
}

// soustraction de vecteurs
Vecteur Vecteur::operator-(Vecteur other) const
{
    return Vecteur((*this)[0] - other[0],
                   (*this)[1] - other[1],
                   (*this)[2] - other[2]);
}

Vecteur Vecteur::operator/(float value) const
{
    return Vecteur((*this)[0] / value, (*this)[1] / value, (*this)[2] / value);
}

// operator +
Vecteur Vecteur::operator+(const Vecteur &other) const
{
    Vecteur res;
    for (int i = 0; i < 3; i++)
    {
        res[i] = xyz[i] + other[i];
    }
    return res;
}

std::ostream &
operator<<(std::ostream &out, Vecteur v)
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
    return u.cross(v).normalize();
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

    std::string str;
    std::string type;

    if (!in.good())
    {
        std::cerr << "Probleme !";
    }
    std::getline(in, str);
    while (std::getline(in, str))
    {
        if (str.c_str()[0] == '#')
        {
            std::getline(in, str);
        } // si on a un commentaire on skip
        else
        {
            float t1x, t1y, t1z, t2x, t2y, t2z, t3x, t3y, t3z;
            std::istringstream istr(str);
            istr >> t1x >> t1y >> t1z >> t2x >> t2y >> t2z >> t3x >> t3y >> t3z;
            Vecteur v1(t1x, t1y, t1z);
            Vecteur v2(t2x, t2y, t2z);
            Vecteur v3(t3x, t3y, t3z);
            Triangle t(v1, v2, v3);
            triangles.push_back(t);
        }
    }
}

// peut etre faire une fonction write
void TriangleSoup::write(std::ostream &out) const
{
    for (std::vector<Triangle>::const_iterator it = triangles.begin(), itE = triangles.end(); it != itE; ++it)
    {
        out << *it << std::endl;
    }
}

void TriangleSoup::boundingBox(Vecteur &low, Vecteur &up) const
{
    low = triangles[0].getSommet1();
    up = triangles[0].getSommet1();

    for (std::vector<Triangle>::const_iterator it = triangles.begin(), itE = triangles.end(); it != itE; ++it)
    {
        for (int i = 0; i < 3; ++i)
        {

            low = low.inf((*it)[i]);
            up = up.sup((*it)[i]);
        }
    }
}

// CellData
void CellData::add(const Vecteur &v)
{
    acc = acc + v;
    nb++;
}

Vecteur CellData::barycenter() const
{
    return acc / nb;
}

// TriangleSoupZipper et Index
TriangleSoupZipper::TriangleSoupZipper(const TriangleSoup &anInput, TriangleSoup &anOutput, Index size)
    : input(anInput), output(anOutput), size(size)
{
    Vecteur low, up;
    input.boundingBox(low, up);
    index2data = std::map<Index, CellData>();
    cellSize = Vecteur((up[0] - low[0]) / size[0],
                       (up[1] - low[1]) / size[1],
                       (up[2] - low[2]) / size[2]);
}

Index TriangleSoupZipper::index(const Vecteur &p) const
{
    Index i;

    i.idx[0] = (int)(p.xyz[0] - low[0]) / cellSize[0];
    i.idx[1] = (int)(p.xyz[1] - low[1]) / cellSize[1];
    i.idx[2] = (int)(p.xyz[2] - low[2]) / cellSize[2];

    return i;
}

Vecteur TriangleSoupZipper::centroid(const Index &idx) const
{
    Vecteur v;

    // calcul du centroid
    v.xyz[0] = idx.idx[0] * cellSize[0] + (cellSize[0] / 2) + low[0];
    v.xyz[1] = idx.idx[1] * cellSize[1] + (cellSize[1] / 2) + low[1];
    v.xyz[2] = idx.idx[2] * cellSize[2] + (cellSize[2] / 2) + low[2];

    return v;
}

void TriangleSoupZipper::zip()
{
    for (std::vector<Triangle>::const_iterator it = input.triangles.begin(), itE = input.triangles.end(); it != itE; ++it)
    {

        Index idx[3];

        for (int i = 0; i < 3; ++i)
        {
            idx[i] = index((*it)[i]);
            index2data[idx[i]].add((*it)[i]);
        }

        if (!(idx[0] == idx[1] || idx[0] == idx[2] || idx[1] == idx[2]))
        {
            Triangle newT;
            for (int i = 0; i < 3; ++i)
            {
                newT[i] = centroid(idx[i]);
            }

            // on l'ajoute
            output.triangles.push_back(newT);
        }
    }
}

void TriangleSoupZipper::smartZip()
{

    index2data.clear();

    zip();

    for (std::vector<Triangle>::iterator it = output.triangles.begin(), itE = output.triangles.end(); it != itE; ++it)
    {

        for (int j = 0; j < 3; ++j)
        {

            (*it)[j] = index2data[index((*it)[j])].barycenter();
        }
    }
}