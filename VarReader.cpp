#include "VarReader.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Global.h"

void to_upper(char& ch) {
	ch = toupper(static_cast<unsigned char>(ch));
}

VarReader::VarReader(string filename)
{
	m_Filename = filename;
}

bool VarReader::readEnv(string model)
{
	std::cout << "-----------------------------------";

	string envFile = m_Filename;
	if (envFile != "ENVFIL")
		envFile += ".env";

	for_each(model.begin(), model.end(), to_upper);

	ifstream inFile;
	string TitleEnv;
	double freq;
	int SSP;
	S_Bdry Bdry;
	inFile = readEnvCore(envFile, TitleEnv, freq, SSP, Bdry);

	return false;
}

bool VarReader::readati()
{
	return false;
}

bool VarReader::readbty()
{
	return false;
}

bool VarReader::readrc()
{
	return false;
}

bool VarReader::readpat()
{
	return false;
}

ifstream VarReader::readEnvCore(string filename, string& TitleEnv, double& freq, int& SSP, S_Bdry& Bdry)
{
	alphaR = 1500; // defaults
	betaR = 0;
	rhoR = 1;
	alphaI = 0;
	betaI = 0;

	NFirstAcoustic = 0;

	Bdry.Top.cp = 0.0;
	Bdry.Top.cs = 0.0;
	Bdry.Top.rho = 0.0;
	Bdry.Bot.cp = 2000.0;
	Bdry.Bot.cs = 0.0;
	Bdry.Bot.rho = 2.0;

	ifstream inFile;
	string line;
	inFile.open(filename);
	if (!inFile.is_open())
		throw "Unable to open environmental file readenv\n";

	getline(inFile, TitleEnv);
	int startPos = TitleEnv.find_first_of('\'');
	int endPos = TitleEnv.find_first_of('\'', startPos + 1);
	TitleEnv = TitleEnv.substr(startPos + 1, endPos - startPos - 1);
	cout << TitleEnv << endl;

	inFile >> freq;
	printf("Frequency = %f Hz \n", freq);
	getline(inFile, line);

	inFile >> SSP;
	printf("'Number of media = %i \n\n", SSP);
	getline(inFile, line);

	return inFile;
}
