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
    void normalize();

    // Retourne le vecteur dont les composantes sont les minima des
    // composantes de soi-même et de other.
    Vecteur inf(const Vecteur &other) const;
    // Retourne le vecteur dont les composantes sont les maxima des
    // composantes de soi-même et de other.
    Vecteur sup(const Vecteur &other) const;
    Vecteur cross(const Vecteur &other) const;
    Vecteur operator-(const Vecteur &other) const;
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
    Vecteur normal() const;

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
    void boundingBox(Vecteur &low, Vecteur &up) const;
};

/// Définit un index sur 3 entiers. Toutes les opérations usuelles
/// sont surchargées (accès, comparaisons, égalité).
struct Index
{
    int idx[3];
    Index() {}
    Index(int i0, int i1, int i2)
    {
        idx[0] = i0;
        idx[1] = i1;
        idx[2] = i2;
    }
    Index(int indices[])
    {
        idx[0] = indices[0];
        idx[1] = indices[1];
        idx[2] = indices[2];
    }
    int operator[](int i) const { return idx[i]; }
    int &operator[](int i) { return idx[i]; }
    bool operator<(const Index &other) const
    {
        return (idx[0] < other.idx[0]) || ((idx[0] == other.idx[0]) && ((idx[1] < other.idx[1]) || ((idx[1] == other.idx[1]) && (idx[2] < other.idx[2]))));
    }
};

struct TriangleSoupZipper
{

    // methode
    TriangleSoupZipper(const TriangleSoup &anInput, TriangleSoup &anOutput, Index size);
    // zip la soupe de triangles en entrée vers la soupe de triangles en sortie
    void zip();

    /// return l'index de la cellule dans laquelle tombe p.
    Index index(const Vecteur &p) const;
    /// return le centroïde de la cellule d'index idx (son "centre").
    Vecteur centroid(const Index &idx) const;

    // variable
    const TriangleSoup &input;
    TriangleSoup &output;
    Index size;
    int xSize;
    int ySize;
    int zSize;
};