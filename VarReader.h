#pragma once

#include <string>
#include "Global.h"
using namespace std;

class VarReader
{
public:
	VarReader(string filename);
	bool readEnv(string model);
	bool readati();
	bool readbty();
	bool readrc();
	bool readpat();
	ifstream readEnvCore(string filename, string& TitleEnv, double& freq, int& SSP, S_Bdry& Bdry);

private:
	string m_Filename;
};

