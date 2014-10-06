#ifndef OBJECT_H
#define OBJECT_H

#include "vector.h"

class Entity	//Definiera ett 'v�sen'
{
  public:
    Entity()
    :angles(3,3)
    {
      origin.Set(0,0,0);
      angles.Unit();
      velocity.Set(0,0,0);
      avelocity.Set(0,0,0);
    }
    Entity(float ox, float oy, float oz)
    :angles(3,3)
    {
      origin.Set(ox,oy,oz);
      angles.Unit();
      velocity.Set(0,0,0);
      avelocity.Set(0,0,0);
    }
    Entity(Entity& E)
    :angles(3,3)
    {
      origin=E.origin;
      angles=E.angles;
      velocity=E.velocity;
      avelocity=E.avelocity;
    }
    float& operator[] (int foo)
    {
      return origin[foo];
    }

    const Vector front()	//En funktion som ger 'fram�tvektorn' hos ett v�sen
    {
      Vector foo;
      foo[0]=angles[0][2];
      foo[1]=angles[1][2];
      foo[2]=angles[2][2];
      return foo;
    }
    const Vector up()	//En funktion som ger 'upp�tvektorn' hos ett v�sen
    {
      Vector foo;
      foo[0]=angles[0][1];
      foo[1]=angles[1][1];
      foo[2]=angles[2][1];
      return foo;
    }
    const Vector right()	//En funktion som ger 'h�gervektorn' hos ett v�sen
    {
      Vector foo;
      foo[0]=angles[0][0];
      foo[1]=angles[1][0];
      foo[2]=angles[2][0];
      return foo;
    }
    Vector origin;		//Ett v�sen ska ha en position i rymden
    Matrix<float> angles;	//Ett v�sen ska ha en viss orientation i rymden
    Vector velocity;		//Ett v�sen ska ha en hastighet
    Vector avelocity;		//Ett v�sen ska ha en rotationshastighet
};

class Object;
class Polygon;

class Polygon	//Definierar en polygon
{
	public:
		~Polygon()
		{
			delete[] verts;
		}
		int num_verts;			//Hur m�nga punkter polygonen best�r av
		int *verts;			//Lista p� vilka punkter den best�r av
		Vector normal;			//Nuvarande normal
		Vector orignormal;		//Originalnormalen
		Object *parent;			//Pekare till objektet polygonen tillh�r
		void Calc_Normal();		//Funktion f�r att r�kna ut normalen
};
class Object : public Entity	//Definierar ett objekt, till att vara ett v�sen, som dessutom inneh�ller f�ljande
{
	public:
		Object(int np,int nv)
		{
			num_polys=np;
			num_verts=nv;
			verts = new Vector[nv];
			origverts = new Vector[nv];
			polys = new Polygon[np];
		}
		~Object()
		{
			delete[] verts;
			delete[] polys;
		}		
		int num_polys;		//Antal polygoner objektet best�r av
		Polygon *polys;		//Lista p� polygoner som objektet best�r av
		int num_verts;		//Antal punkter objektet best�r av
		Vector *verts;		//Lista p� de nuvarande punkterna
		Vector *origverts;	//Lista p� originalpunkterna
};

#endif
