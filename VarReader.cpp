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
	S_SSP SSP;
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

ifstream VarReader::readEnvCore(string filename, string& TitleEnv, double& freq, S_SSP& SSP, S_Bdry& Bdry)
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

	inFile >> SSP.NMedia;
	printf("'Number of media = %i \n\n", SSP);
	getline(inFile, line);

	string TopOpt;
	getline(inFile, TopOpt);

	startPos = TopOpt.find_first_of('\'');
	endPos = TopOpt.find_first_of('\'', startPos + 1);
	Bdry.Top.Opt = TopOpt.substr(startPos + 1, endPos - startPos - 1);
	TopOpt.resize(7, ' ');
	if (Bdry.Top.Opt[4] == '*')
		Bdry.Top.Opt[4] == '~';

	char SSPType = Bdry.Top.Opt[0];
	Bdry.Top.BC = Bdry.Top.Opt[1];
	char AttenUnit[2] = { Bdry.Top.Opt[2] , Bdry.Top.Opt[3] };

	switch (SSPType) {
		case 'N':
			cout << "    N2-Linear approximation to SSP";
			break;
		case 'C':
			cout << "    C-Linear approximation to SSP";
			break;
		case 'P':
			cout << "    PCHIP approximation to SSP";
			break;
		case 'S':
			cout << "    Spline approximation to SSP";
		case 'Q':
			cout << "    Quadrilateral approximation to range-dependent SSP";
			break;
		case 'H':
			cout << "   Hexahedral approximation to range and depth dependent SSP";
			break;
		case 'A':
			cout << "    Analytic SSP option";
			break;
		default:
			inFile.close();
			throw "Fatal error: Unknown option for SSP approximation";
	}

	switch (AttenUnit[0]) {
	case 'N':
		cout << "Attenuation units: nepers/m";
		break;
	case 'F':
		cout << "    Attenuation units: dB/mkHz'";
		break;
	case 'M':
		cout << "    Attenuation units: dB/m";
		break;
	case 'W':
		cout << "    Attenuation units: dB/wavelength";
		break;
	case 'Q':
		cout << "    Attenuation units: Q'";
		break;
	default:
		inFile.close();
		throw "Fatal error: Unknown attenuation units";
	}

	if (Bdry.Top.Opt.length() >= 4) {

	}

	if (Bdry.Top.Opt.length() >= 5) {

	}

	topbot(inFile);

	cout << "\n   z (m)   alphaR (m/s)    betaR     rho (g/cm^3)  alphaI      betaI \n";

// 	SSP.z = [];
// 	SSP.c = [];
// 	SSP.cs = [];
// 	SSP.rho = [];
	ArrayXd Loc;
	for (int medium = 1; medium < SSP.NMedia; medium++) {
		if (medium == 1)
			Loc[medium] = 0;
		else
			Loc[medium] = Loc[medium - 1] + SSP.Npts[medium - 1];

		//number of points in finite - difference grid
		inFile >> SSP.N >> SSP.sigma[medium] >> SSP.depth[medium + 1];

		printf("    ( Number of pts = %i  Roughness = %6.2f  Depth = %8.2f ) \n", SSP.N, SSP.sigma[medium], SSP.depth[medium + 1]);
		getline(inFile, line);

		//read in the SSP
		for (int ii = 1; ii < 999; ii ++)
		{
			double ztmp;
			inFile >> ztmp >> alphaR >> betaR >> rhoR >> alphaI >> betaI;
			printf("%8.2f    %8.2f    %8.2f    %8.2f    %8.4f    %8.4f \n", ztmp, alphaR, betaR, rhoR, alphaI, betaI);


		}

	}
 
// 							cp = crci(alphaR, alphaI, freq, AttenUnit);
// 	cs = crci(betaR, betaI, freq, AttenUnit);
// 	SSP.z = [SSP.z;   ztmp]; % add in to existing vector
// 		SSP.c = [SSP.c;   cp];
// 	SSP.cs = [SSP.cs;  cs];
// 	SSP.rho = [SSP.rho; rhoR];
// 
// 	SSP.raw(medium).z(ii) = ztmp; % add in to existing vector
// 		SSP.raw(medium).alphaR(ii) = alphaR;
// 	SSP.raw(medium).alphaI(ii) = alphaI;
// 	SSP.raw(medium).betaR(ii) = betaR;
// 	SSP.raw(medium).betaI(ii) = betaI;
// 	SSP.raw(medium).rho(ii) = rhoR;
// 
// 	% check for end of this layer
// 		if (ztmp == SSP.depth(medium + 1))
// 			SSP.depth(1) = SSP.z(1);
// 	break
// 		end
// 
// 		if (SSP.N(medium) == 0) % calculate mesh automatically
// 			% choose a reference sound speed
// 			C = alphaR;
// 	if (betaR > 0.0); C = betaR; end% shear ?
// 
// 		deltaz = 0.05 * C / freq; % default sampling: 20 points per wavelength
// 
// 		SSP.N(medium) = round((SSP.depth(medium + 1) - SSP.depth(medium)) / deltaz);
// 	SSP.N(medium) = max(SSP.N(medium), 10); % require a minimum of 10 points
// 		end
// 
// 		fprintf('    Number of pts = %i \n', SSP.N(medium));
// 
// 	% keep track of firstand last acoustic medium
// 		if (~any(cs)) % shear anywhere ?
// 			if (NFirstAcoustic == 0)
// 				NFirstAcoustic = medium;
// 	end
// 		NLastAcoustic = medium;
// 	end
// 
// 		% stuff for Bellhop
// 		if (medium == 1)
// 			HV = diff(SSP.z); % layer thicknesses
// 			SSP.cz = diff(SSP.c) . / HV; % gradient of ssp(centered - difference approximation)
// 			end
// 			SSP.Npts(medium) = ii;
// 	if (medium == 1); SSP.depth(1) = SSP.z(1); end
// 		end
	return inFile;
}

void VarReader::topbot(ifstream&)
{
}
