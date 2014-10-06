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
#include <iostream>		//Inkludera funktioner f�r att skriva till sk�rmen
#include <fstream>		//Inkludera funktioner f�r att l�sa filer
#include <time.h>		//Inkludera funktioner f�r att ta reda p� tiden
#include "list.h" 		//Inkludera mina h�ftiga listrutiner!
#include "matrix.h" 		//Inkludera mina h�ftiga matrisrutiner!
#include "vector.h" 		//Inkludera mina h�ftiga vektorrutiner!
#include "object.h"

#define EROT 0.01		//Definiera rotationssteg f�r �gat
#define OROT 0.01		//Definiera rotationssteg f�r objektet
#define SCRMODE GFX_AUTODETECT	//Definiera sk�rml�get
#define SCRWIDTH 640		//Definiera sk�rmvidden
#define SCRHEIGHT 480		//Definiera sk�rmh�jden
#define HSCRW 320		//Definiera mitten p� sk�rmen
#define HSCRH 240		//Definiera mitten p� sk�rmen
#define COLDEPTH 15		//Definiera f�rgdjupet

//Definiera ett makro som man kan anv�nda f�r att komma �t en viss punkt i en viss polygon i ett visst objekt
#define objpolyvert(o,p,v) (objs[(o)]->verts[objs[(o)]->polys[(p)].verts[(v)]])

void initialize();
void shut_down();
bool load_off(char*,int);
