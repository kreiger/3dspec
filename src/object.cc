#include "object.h"

void Polygon::Calc_Normal()	//Funktion som r�knar ut normalen p� en polygon
{
	Vector v1,v2;			//Tv� tempor�ra vektorer
	v1=(parent->origverts[verts[0]])-(parent->origverts[verts[1]]);	//Vektorn mellan 1:a och 2:a punkten i polygonen
	v2=(parent->origverts[verts[2]])-(parent->origverts[verts[1]]);	//Vektorn mellan 3:e och 2:a punkten i polygonen
	orignormal=v1&v2;	//Ta vektorprodukten av vektorerna
	orignormal.Normalize();	//Normera resultatet
}
