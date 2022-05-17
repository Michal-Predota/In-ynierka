#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iostream>

#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <TString.h>

using namespace std;

std::ostringstream oss;


#define _PARTICLES_TREE_  "particles"
#define _PARTICLE_BRANCH_ "particle"
#define _PARTICLE_FORMAT_ "ipart/I:pid:px/F:py:pz:e:mass:x:y:z:t"

struct StructParticle {
	int ipart;
	Int_t pid;
	Float_t px, py, pz, e;
	Float_t mass;
	Float_t  x, y, z, t;
	
	
	//Int_t rootpid, eid;
	//UInt_t eventid;
};

#define _EVENTS_TREE_   "events"
#define _EVENTS_BRANCH_ "event"
#define _EVENTS_FORMAT_ "eventid/i:entries:entriesprev"

struct StructEvent{
	UInt_t eventID;
	UInt_t entries;
	UInt_t entriesprev;
};

		



void createUrQMDroot_mult(const char* prefix = "test.f19", const char* suffix = "", int numberOfFiles = 1, const char* path = "",
		const char* multPath = "", const double bMin = 0, const double bMax = 99) {
	int noEvents = 0;
	int noFiles = 0;

	bool started = false;

	ifstream fileIn;
	char tCharBuf[500];
	char tFileName[500];

	TFile* mFile;
    TTree*	mEventTree;
    TTree*	mParticleTree;

	static StructParticle tStructPart;
	static StructEvent tStructEvent;

	Int_t ipart, id;
	Double_t px, py, pz, e, mass;
	Double_t x, y, z, t;



	for(int iFile = 1; iFile <= numberOfFiles; iFile++) {
		oss << prefix;// << iFile << suffix;
		fileIn.open(oss.str().c_str());
		cout << "Reading file " << oss.str() << endl;
		cout << "noEvents: " << noEvents << endl;
		oss.str("");

		fileIn.getline(tCharBuf,500);
		fileIn.getline(tCharBuf,500);
		fileIn.getline(tCharBuf,500);

		// *** Events loop *** //
		for(int event = 0; event < 1000; event++) {

			if((noEvents == 0 && started) || (noEvents == 0 && event == 0 && iFile == 1)) {
				cout << "Create file " << noFiles << endl;
				// *** Create new file for output *** //
				if(multPath != "")
					sprintf(tFileName, "%s%sevent%03i.root", path, multPath, noFiles);
				else
					sprintf(tFileName, "%sevent%03i.root", path, noFiles);

				mFile = new TFile(tFileName, "RECREATE");
				mFile->cd();

				mParticleTree  = new TTree(_PARTICLES_TREE_, "particle tree");    
				mEventTree     = new TTree(_EVENTS_TREE_,    "event tree");

				TBranch* partBranch = mParticleTree->Branch(_PARTICLE_BRANCH_, &tStructPart, _PARTICLE_FORMAT_);
				TBranch* eventBranch = mEventTree->Branch(_EVENTS_BRANCH_, &tStructEvent, _EVENTS_FORMAT_);

				started = false;
			}

			// cout << "Read event "  << event << " information..." << endl;

			// *** Event information *** //
			Int_t eid; // event id (number in UrQMD)
			Int_t nparticles; // number pf particles
			Double_t ipar; // impact parameter
			Double_t eplane; //azimuthal angle phi - rotation of event plane

			fileIn >> eid >> nparticles>> ipar >> eplane;
			eid += time(NULL);

			//if(ipar > bMin && ipar < bMax) {

				// *** Particles loop *** //
				
				//cout<<nparticles<<endl;
				
				for(int part = 0; part < nparticles; part++) {
					// *** Particle information *** //

					fileIn >>ipart >> id >> px >> py >> pz >> e >> mass >> x >> y >> z >> t;

					//cout<<"id: "<<id<<"px: "<<px<<"py: "<<py<<"pz: "<<pz<<"e: "<<e<<"mass: "<<mass<<"x: "<<x<<"y: "<<y<<"z: "<<z<<"t: "<<t<<endl;
					
					tStructPart.ipart = ipart;
					tStructPart.pid = id;
					tStructPart.px = px;
					tStructPart.py = py;
					tStructPart.pz = pz;
					tStructPart.e = e;
					tStructPart.mass = mass;
					tStructPart.x = x;
					tStructPart.y = y;
					tStructPart.z = z;
					tStructPart.t = t;
					
					//tStructPart.rootpid = id;
					//tStructPart.eid = ipart-1;
					//tStructPart.fathereid = -1;
					//tStructPart.decayed = 0;
					//tStructPart.eventid = eid;
					
					mParticleTree->Fill();
				}

				// cout << "END particle loop" << endl;

				tStructEvent.eventID = eid;
				tStructEvent.entries = nparticles;
				tStructEvent.entriesprev = 0;

				mEventTree->Fill();
				noEvents++;
				started = true;
			//} // check impact parameter
			/*else {
				for(int part = 0; part < nparticles; part++) {
					// *** Particle information loop *** //
					// ***** just to get to next event **** //
					fileIn >> ipart >> id >> px >> py >> pz >> e >> mass >> x >> y >> z >> t;
				}
			}*/


			if(event == 999) {
				cout << "End UrQMD file no. " << iFile << endl;
				cout << "Events written: " << noEvents << endl;

				fileIn.close();
			}

			if(noEvents == 1000) {
				cout << "Full file - writing and closing..." << endl;
				noEvents = 0;
				mFile->Write();
				mFile->Close();
				mFile = 0;

				mParticleTree = 0;
				mEventTree = 0;

				noFiles++;
			}
			else if(event == 999 && iFile == numberOfFiles) {
				cout << "End of UrQMD files..." << endl;
				cout << "Files written: " << noFiles << endl;
				cout << "Events written: " << noEvents << endl;


				mFile->Write();
				mFile->Close();
				mFile = 0;

				mParticleTree = 0;
				mEventTree = 0;
			}

		} // event in UrQMD file loop

	} // UrQMD file loop

}


int main(int argc, char* argv[]) {

	char *prefix = "", *suffix = "";
	int numberOfFiles = 0;
	char* path = "test.f19";
	char* multPath = "C:/Users/Michał/Desktop/Inżynierka/"; 
	double bMin = 0, bMax = 0;

	if(argc > 1)
		prefix = argv[1];

	if(argc > 2)
		suffix = argv[2];

	if(argc > 3)
		numberOfFiles = atoi(argv[3]);

	if(argc > 4)
		path = argv[4];

	if(argc > 5)
		multPath = argv[5];

	if(argc > 6)
		bMin = atof(argv[6]);

	if(argc > 7)
		bMax = atof(argv[7]);

	cout << "Prefix: " << prefix << endl;
	cout << "Suffix: " << suffix << endl;
	cout << "Number of files: " << numberOfFiles << endl;
	cout << "Path: " << path << endl;
	cout << "multPath: " << multPath << endl;
	cout << "b: " << bMin << " : " << bMax << endl;


	if(argc > 5) {
		createUrQMDroot_mult(prefix, suffix, numberOfFiles, path, multPath, bMin, bMax);
	}
	else if(argc > 1) {
		createUrQMDroot_mult(prefix, suffix, numberOfFiles, path);
	}
	else {
		createUrQMDroot_mult();
	}

	return 0;
}
