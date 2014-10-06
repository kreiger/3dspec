/************************************************************************
*                                                                       *
*                                                                       *
*                                                                       *
*                       Kreiger's Specialarbete                         *
*                                                                       *
*                                                                       *
*                                                                       *
************************************************************************/
#define VER 3
#define BUILD 47916

#define alleg_math_unused
#include <allegro.h>		//Inkludera allegros grafikrutiner
#include <math.h>		//Inkludera matematiska funktioner (sin/cos, et.c.)
#include <iostream>		//Inkludera funktioner för att skriva till skärmen
#include <fstream>		//Inkludera funktioner för att läsa filer
#include <time.h>		//Inkludera funktioner för att ta reda på tiden
#include "list.h" 		//Inkludera mina häftiga listrutiner!
#include "matrix.h" 		//Inkludera mina häftiga matrisrutiner!
#include "vector.h" 		//Inkludera mina häftiga vektorrutiner!
#include "object.h"

#define EROT 0.01		//Definiera rotationssteg för ögat
#define OROT 0.01		//Definiera rotationssteg för objektet
#define SCRMODE GFX_AUTODETECT	//Definiera skärmläget
#define SCRWIDTH 640		//Definiera skärmvidden
#define SCRHEIGHT 480		//Definiera skärmhöjden
#define HSCRW 320		//Definiera mitten på skärmen
#define HSCRH 240		//Definiera mitten på skärmen
#define COLDEPTH 15		//Definiera färgdjupet

//Definiera ett makro som man kan använda för att komma åt en viss punkt i en viss polygon i ett visst objekt
#define objpolyvert(o,p,v) (objs[(o)]->verts[objs[(o)]->polys[(p)].verts[(v)]])

void initialize();
void shut_down();
bool load_off(char*,int);
