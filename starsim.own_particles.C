
class St_geant_Maker;
St_geant_Maker *geant_maker = 0;

class StarGenEvent;
StarGenEvent *event = 0;

class StarPrimaryMaker;
StarPrimaryMaker *_primary = 0;

class StarKinematics;
StarKinematics *kinematics = 0;

TRandom* rand;

void geometry( TString tag, Bool_t agml=true )
{
        TString cmd = "DETP GEOM "; cmd += tag;
        if ( !geant_maker ) geant_maker = (St_geant_Maker *)chain->GetMaker("geant");
        geant_maker -> LoadGeometry(cmd);
        //  if ( agml ) command("gexec $STAR_LIB/libxgeometry.so");
}


void command( TString cmd )
{
        if ( !geant_maker ) geant_maker = (St_geant_Maker *)chain->GetMaker("geant");
        geant_maker -> Do( cmd );
}

struct StructParticle {
	Float_t mass;
	Float_t t, x, y, z;
	Float_t e, px, py, pz;
	Int_t decayed, pid, fatherpid;
	Int_t rootpid, eid, fathereid;
	UInt_t eventid;
};


vector<double> mass_vec, t_vec, x_vec, y_vec, z_vec, e_vec, px_vec, py_vec, pz_vec;
vector<int> decayed_vec, pid_vec, fatherpid_vec, rootpid_vec, fathereid_vec, eventid_vec;

char path[100];


void trig(Int_t nevents=1, Float_t filter = 0.5)
{
	TChain *Chain_inz = new TChain("particles");
	int event_id;
	int eventid_curr;
	int particle_counter=0;
	
	int number_of_files = ceil((double)nevents/500);
	
	for(int nfile=0; nfile<number_of_files; nfile++)
	{
		if(nfile<=9)
		{
			sprintf(path, "/star/u/micpre/work/STAR_sim/own/event00%d.root", nfile);
		}
		else if(nfile>9&&nfile<=99)
		{
			sprintf(path, "/star/u/micpre/work/STAR_sim/own/event0%d.root", nfile);
		}
		else if(nfile>99&&nfile<=999)
		{
			sprintf(path, "/star/u/micpre/work/STAR_sim/own/event%d.root", nfile);
		}	
		cout<<path<<endl;
		Chain_inz->Add(path);
	}
	
	cout<<"Number of files: "<<number_of_files<<endl;
	
	if(filter == 0.5)
	{
		for(int i=0; i<nevents; i++)
		{
		
			StructParticle Particle_th;
			Chain_inz->SetBranchAddress("particle", &Particle_th);
		
			Chain_inz->GetEntry(particle_counter);
		
			event_id=Particle_th.eventid;
			eventid_curr=Particle_th.eventid;
		
			while(event_id==eventid_curr)
			{
				chain->Clear();
				Chain_inz->GetEntry(particle_counter);
				if(Particle_th.pid==2212||Particle_th.pid==-2212||Particle_th.pid==111||Particle_th.pid==211||Particle_th.pid==310||Particle_th.pid==130||Particle_th.pid==321||Particle_th.pid==-211||Particle_th.pid==-321)
				{
					StarGenParticle* particle;
					particle = kinematics->AddParticle();
		
					particle->SetId(Particle_th.pid);
					particle->SetMass(Particle_th.mass);
					particle->SetPx(Particle_th.px);
					particle->SetPy(Particle_th.py);
					particle->SetPz(Particle_th.pz);
					particle->SetEnergy(Particle_th.e);
					particle->SetVx(Particle_th.x/(TMath::Power(10, 12)));
					particle->SetVy(Particle_th.y/(TMath::Power(10, 12)));
					particle->SetVz(Particle_th.z/(TMath::Power(10, 12)));
					particle->SetTof(Particle_th.t/(TMath::Power(10, 12)));
					particle->SetFirstMother(Particle_th.fatherpid);
					particle->SetLastMother(Particle_th.fatherpid);
					particle->SetFirstDaughter(-9999);
					particle->SetLastDaughter(-9999);
					particle->SetStatus(1);
				}
				
				particle_counter++;
				eventid_curr=Particle_th.eventid;
			}
			event_id=eventid_curr;
			cout<<"event "<<i+1<<" complete"<<endl;		
			kinematics->Generate();
			chain->Make();
		}
	}
	else
	{
		for(int i=0; i<nevents; i++)
		{
		
			StructParticle Particle_th;
			Chain_inz->SetBranchAddress("particle", &Particle_th);
		
			Chain_inz->GetEntry(particle_counter);
		
			event_id=Particle_th.eventid;
			eventid_curr=Particle_th.eventid;
		
			while(event_id==eventid_curr)
			{
				chain->Clear();
				Chain_inz->GetEntry(particle_counter);
				if(Particle_th.pid==filter)
				{
					StarGenParticle* particle;
					particle = kinematics->AddParticle();
		
					particle->SetId(Particle_th.pid);
					particle->SetMass(Particle_th.mass);
					particle->SetPx(Particle_th.px);
					particle->SetPy(Particle_th.py);
					particle->SetPz(Particle_th.pz);
					particle->SetEnergy(Particle_th.e);
					particle->SetVx(Particle_th.x/(TMath::Power(10, 12)));
					particle->SetVy(Particle_th.y/(TMath::Power(10, 12)));
					particle->SetVz(Particle_th.z/(TMath::Power(10, 12)));
					particle->SetTof(Particle_th.t/(TMath::Power(10, 12)));
					particle->SetFirstMother(Particle_th.fatherpid);
					particle->SetLastMother(Particle_th.fatherpid);
					particle->SetFirstDaughter(-9999);
					particle->SetLastDaughter(-9999);
					particle->SetStatus(1);
				}
				
				particle_counter++;
				eventid_curr=Particle_th.eventid;
			}
			event_id=eventid_curr;
			cout<<"event "<<i+1<<" complete"<<endl;		
			kinematics->Generate();
			chain->Make();
		}
	}
	

}

void Kinematics()
{
	gSystem->Load( "libKinematics.so");
        kinematics = new StarKinematics();

        _primary->AddGenerator(kinematics);
}

void starsim(Int_t nevents=1, Float_t filter = 0.5, Int_t rngSeed=1234)
{

	rand = new TRandom;

	gROOT->ProcessLine(".L bfc.C");
	{
		TString simple = "y2010 geant gstar usexgeom agml ";
		bfc(0, simple);
	}

	gSystem->Load( "libVMC.so");

        gSystem->Load( "StarGeneratorUtil.so" );
        gSystem->Load( "StarGeneratorEvent.so" );
        gSystem->Load( "StarGeneratorBase.so" );

        gSystem->Load( "libMathMore.so"   );
        gSystem->Load( "xgeometry.so"     );


	StarRandom::seed(rngSeed);
        StarRandom::capture();


	_primary = new StarPrimaryMaker();
        {
                _primary -> SetFileName( "particles.starsim.root");
                chain -> AddBefore( "geant", _primary );
        }

	Kinematics();
	_primary -> Init();

	geometry("y2010");
	command("gkine -4 0");
        command("gfile o own.starsim.fzd");

	trig(nevents, filter);

	chain->Finish();
	command("call agexit");


}
