// openmp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <omp.h>


/* --------------------------------------------------------------------
Implementați un program ce calculează produsul a 2 matrici
cu N linii și N coloane iar apoi paralelizați programul utilizand
OpenMP
Urmati, pe rand, pasii de mai jos.
--------------------------------------------------------------------*/

int _tmain(int argc, _TCHAR* argv[])
{
	// Numarul N de linii/coloane
	int N = 1000;
	// Prima matrice
	int *a;
	// A 2-a matrice
	int *b;
	// Matricea rezultat
	int *c;
	/* --------------------------------------------------------------------
	1. Alocati memorie pe host pentru cele trei matrici:
	0.333 puncte
	--------------------------------------------------------------------*/
	/* ------------------------ REZOLVARE PCT 1 -----------------------------*/
	/* ------------------------ CODUL TAU DE AICI ---------------------------*/
	a = new int[N*N];
	b = new int[N*N];
	c = new int[N*N];    //FARA INT * PT CA E CA SI CAND S-AR DELCARA DIN NOU SI DOAR ASA MERGE



	/* ------------------------ CODUL TAU PANA AICI ---------------------------*/
	/* --------------------------------------------------------------------
	2. Initializați matricile a si b dupa cum urmeaza: elementele de pe prima coloana
	au valoarea 1, elementele de pe a 2-a coloana au valoarea 2, cele de pe a
	3-a au valoarea 4, etc
	0.333 puncte
	--------------------------------------------------------------------*/
	/* ------------------------ REZOLVARE PCT 2 -----------------------------*/
	/* ------------------------ CODUL TAU DE AICI ---------------------------*/
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			a[i*N + j] = j + 1;
			b[i*N + j] = j + 1;    //un singur for ca sunt aceleasi matrici
			c[i*N + j] = 0;
		}
	}




	/* ------------------------ CODUL TAU PANA AICI ---------------------------*/
	/* --------------------------------------------------------------------
	3. Implementați inmultirea celor doua matrici si scrieti rezultatul in
	matiricea c
	0.333 puncte
	--------------------------------------------------------------------*/
	/* ------------------------ REZOLVARE PCT 3 -----------------------------*/
	/* ------------------------ CODUL TAU DE AICI ---------------------------*/
	for (int i = 0; i<N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			for (int x = 0; x < N; x++)
			{
				c[i*N + j] += a[i*N + x] * b[x*N + j];
			}
		}
	}


	/* ------------------------ CODUL TAU PANA AICI ---------------------------*/
	/* --------------------------------------------------------------------
	4. Implementați varianta paralela a calculului de la cerinta precedenta
	Indicatie: doar bucla for exterioara (ce parcurge liniile) se distribuie
	pe mai multe fire de executie
	1 punct
	--------------------------------------------------------------------* /
	/* ------------------------ REZOLVARE PCT 4 -----------------------------*/
	/* ------------------------ CODUL TAU DE AICI ---------------------------*/

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
   //un singur for ca sunt aceleasi matrici
			c[i*N + j] = 0;
		}
	}

	int no_of_threads = 4;
	omp_set_num_threads(no_of_threads);
	#pragma omp parallel 		
	{

		int id = omp_get_thread_num(); 			//obtinere numar thread 
		int startId = id * N / no_of_threads;            //0-250, 251-500, 501-750, 751-1000
		int stopId = (id + 1)*N / no_of_threads;
		for (int i = startId; i < stopId; i++)
		{
			for (int j = 0; j < N; j++)
			{
				for (int x = 0; x < N; x++)
				{
					c[i*N + j] += a[i*N + x] * b[x*N + j];
				}
			}
		}
	}

	for (int i = 0; i<N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			std::cout << c[i*N + j] << " ";
		}
		std::cout << std::endl;
	}
	return 0;


}

