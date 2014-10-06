#include "object.h"
#include <iostream>
#include <fstream>

extern Object **objs;					//Låter denna fil känna till listan på objektpekare

using namespace std ;

//load_off: Läser in en .OFF-fil
bool load_off (char *fname, int num)
{
	ifstream f1(fname);

	if (!f1)					//Kollar om filen gick att öppna
	{
		cerr << "File error: " << fname << endl;
		return false;
	}

	int np,nv;
	f1 >> np; f1 >> nv;				//Läser in antalet polygoner, och antal verts

	objs[num] = new Object(np,nv);			//Allokerar minne för ett objekt
	for (int foo=0;foo < nv;foo++)			//För varje punkt
	{
		f1 >> objs[num]->origverts[foo][0];	//Läs in X...
		f1 >> objs[num]->origverts[foo][1];	//Y...
		f1 >> objs[num]->origverts[foo][2];	//Och Z!
	}
	for (int foo=0;foo < np;foo++)				//För varje polygon
	{
		f1 >> nv;					//Läs in antalet punkter i polygonen
		objs[num]->polys[foo].num_verts = nv;
		objs[num]->polys[foo].verts = new (int)[nv];	//Allokera minne
		objs[num]->polys[foo].parent = objs[num];	//Låt polygonen veta vilket objekt den tillhör

		for (int bar=0;bar < nv;bar++)			//För varje punkt i polygonen
		{
			f1 >> objs[num]->polys[foo].verts[bar];	//Läs in vilka punkter som tillhör polygonen
		}
		objs[num]->polys[foo].Calc_Normal();		//Räkna ut normalen i polygonen
	}
	return true;
}	
