#include "bellhopM.h"
#include "VarReader.h"
#include "Global.h"

int HV;
int NFirstAcoustic;
int NLastAcoustic;
int alphaR;
int betaR;
int rhoR;
int alphaI;
int betaI;

S_Bdry Bdry;

void bellhopM(string filename)
{
	VarReader reader(filename);

	reader.readEnv("BELLHOP");	// read environment variables

	// filenames
	string envfil = filename + ".env";		// input environmental file
	string shdfil = filename + ".shd.mat";	// output file name(pressure)
	string arrfil = filename + ".arr.mat";	// output file name(arrivals)
	string btyfil = filename + ".bty";		// input bathymetry
	string atifil = filename + ".ati";		// input altimetry
	string sbpfil = filename + ".sbp";		// input source beam pattern
	string trcfil = filename;				// input top    reflection coefficient
	string brcfil = filename;				// input bottom reflection coefficient

}
