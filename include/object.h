#ifndef OBJECT_H
#define OBJECT_H

#include "vector.h"

class Entity	//Definiera ett 'väsen'
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

    const Vector front()	//En funktion som ger 'framåtvektorn' hos ett väsen
    {
      Vector foo;
      foo[0]=angles[0][2];
      foo[1]=angles[1][2];
      foo[2]=angles[2][2];
      return foo;
    }
    const Vector up()	//En funktion som ger 'uppåtvektorn' hos ett väsen
    {
      Vector foo;
      foo[0]=angles[0][1];
      foo[1]=angles[1][1];
      foo[2]=angles[2][1];
      return foo;
    }
    const Vector right()	//En funktion som ger 'högervektorn' hos ett väsen
    {
      Vector foo;
      foo[0]=angles[0][0];
      foo[1]=angles[1][0];
      foo[2]=angles[2][0];
      return foo;
    }
    Vector origin;		//Ett väsen ska ha en position i rymden
    Matrix<float> angles;	//Ett väsen ska ha en viss orientation i rymden
    Vector velocity;		//Ett väsen ska ha en hastighet
    Vector avelocity;		//Ett väsen ska ha en rotationshastighet
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
		int num_verts;			//Hur många punkter polygonen består av
		int *verts;			//Lista på vilka punkter den består av
		Vector normal;			//Nuvarande normal
		Vector orignormal;		//Originalnormalen
		Object *parent;			//Pekare till objektet polygonen tillhör
		void Calc_Normal();		//Funktion för att räkna ut normalen
};
class Object : public Entity	//Definierar ett objekt, till att vara ett väsen, som dessutom innehåller följande
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
		int num_polys;		//Antal polygoner objektet består av
		Polygon *polys;		//Lista på polygoner som objektet består av
		int num_verts;		//Antal punkter objektet består av
		Vector *verts;		//Lista på de nuvarande punkterna
		Vector *origverts;	//Lista på originalpunkterna
};

#endif
