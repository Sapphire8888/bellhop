#pragma once

extern	int HV;
extern	int NFirstAcoustic;
extern	int NLastAcoustic;
extern	int alphaR;
extern	int betaR;
extern	int rhoR;
extern	int alphaI;
extern	int betaI;

extern struct S_Bdry  
{
	struct
	{
		double cp;
		double cs;
		double rho;
	} Top;
	struct
	{
		double cp;
		double cs;
		double rho;
	} Bot;
} Bdry;
