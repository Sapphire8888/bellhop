#pragma once

#include "Eigen/Core"
using namespace Eigen;

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
		std::string Opt;
		char BC;
	} Top;
	struct
	{
		double cp;
		double cs;
		double rho;
		std::string Opt;
	} Bot;
} Bdry;

struct S_SSP
{
	int NMedia;
	ArrayXd Npts;
	int N;
	ArrayXd sigma;
	ArrayXd depth;
};