#include "object.h"
#include <iostream>
#include <fstream>

extern Object **objs;					//L�ter denna fil k�nna till listan p� objektpekare

using namespace std ;

//load_off: L�ser in en .OFF-fil
bool load_off (char *fname, int num)
{
	ifstream f1(fname);

	if (!f1)					//Kollar om filen gick att �ppna
	{
		cerr << "File error: " << fname << endl;
		return false;
	}

	int np,nv;
	f1 >> np; f1 >> nv;				//L�ser in antalet polygoner, och antal verts

	objs[num] = new Object(np,nv);			//Allokerar minne f�r ett objekt
	for (int foo=0;foo < nv;foo++)			//F�r varje punkt
	{
		f1 >> objs[num]->origverts[foo][0];	//L�s in X...
		f1 >> objs[num]->origverts[foo][1];	//Y...
		f1 >> objs[num]->origverts[foo][2];	//Och Z!
	}
	for (int foo=0;foo < np;foo++)				//F�r varje polygon
	{
		f1 >> nv;					//L�s in antalet punkter i polygonen
		objs[num]->polys[foo].num_verts = nv;
		objs[num]->polys[foo].verts = new (int)[nv];	//Allokera minne
		objs[num]->polys[foo].parent = objs[num];	//L�t polygonen veta vilket objekt den tillh�r

		for (int bar=0;bar < nv;bar++)			//F�r varje punkt i polygonen
		{
			f1 >> objs[num]->polys[foo].verts[bar];	//L�s in vilka punkter som tillh�r polygonen
		}
		objs[num]->polys[foo].Calc_Normal();		//R�kna ut normalen i polygonen
	}
	return true;
}	
