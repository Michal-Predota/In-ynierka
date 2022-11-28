#include <iostream>
#include <vector>
#include <TH1D.h>
#include <TChain.h>
#include <TCanvas.h>

using namespace std;

struct StructParticle {
	Float_t mass;
	Float_t t, x, y, z;
	Float_t e, px, py, pz;
	Int_t decayed, pid, fatherpid;
	Int_t rootpid, eid, fathereid;
	UInt_t eventid;
};

char path[100];

int Parser()
{
	TChain *Chain = new TChain("particles");
	TChain *Chainparticle = new TChain("genevents");
	
	int event_id;
	int eventid_curr;
	int particle_counter=0;
	
	TChain *Chain_inz = new TChain("particles");
	
	Chain->Add("event000.root");
	Chainparticle->Add("particles.starsim_50ev.root");
	
	StructParticle Particle;
	
	//cout<<Chainparticle->GetEntries()<<endl;
	int number_of_files = ceil((double)550/500);
	
	Chain->SetBranchAddress("particle", &Particle);
	
	int particle_id=111;
	
	for(int nfile=0; nfile<number_of_files; nfile++)
	{
		if(nfile<=9)
		{
			sprintf(path, "/mnt/c/Users/bumcy/Desktop/Inżynierka/Starsim/event00%d.root", nfile);
		}
		else if(nfile>9&&nfile<=99)
		{
			sprintf(path, "/mnt/c/Users/bumcy/Desktop/Inżynierka/Starsim/event00%d.root", nfile);
		}
		else if(nfile>99&&nfile<=999)
		{
			sprintf(path, "/mnt/c/Users/bumcy/Desktop/Inżynierka/Starsim/event00%d.root", nfile);
		}	
		cout<<path<<endl;
		Chain_inz->Add(path);
	}
	cout<<"Number of files: "<<number_of_files<<endl;
	
	TH1D *h1 = new TH1D("", "", 400, -5, 5);
	
	StructParticle Particle_th;
	Chain_inz->SetBranchAddress("particle", &Particle_th);
	for(int i=0; i<50; i++)
	{
		//cout<<path<<endl;
		
		Chain_inz->GetEntry(particle_counter);
		
		event_id=Particle_th.eventid;
		eventid_curr=Particle_th.eventid;
		
		while(event_id==eventid_curr)
		{
			
			Chain_inz->GetEntry(particle_counter);
			if(Particle_th.pid==2212||Particle_th.pid==111||Particle_th.pid==211||Particle_th.pid==310||Particle_th.pid==130||Particle_th.pid==321||Particle_th.pid==-211||Particle_th.pid==-321||Particle_th.pid==311)
			{
				h1->Fill(Particle_th.pz);
			}
			
			particle_counter++;
			eventid_curr=Particle_th.eventid;
			
		}
		event_id=eventid_curr;
		//cout<<Chain_inz->GetEntries()<<endl;
		//cout<<"event "<<i+1<<" complete"<<endl;		
	}
	
	//cout<<Chain_inz->GetEntries()<<endl;
	int chain_entries = Chain_inz->GetEntries();
	cout<<"chain entries:"<<chain_entries<<endl;
	
	float mPx[23], mPy[23], mPz[23], mEnergy[23], mVx[23], mVy[23], mVz[23], mTof[23];
	int mId[23];
	
	for(int i=0; i<23; i++)
	{
		mPx[i]=i;
	}
	cout<<mPx[2]<<endl;
	
	cout<<"asd"<<endl;
	
	
	Long64_t NEntries=Chainparticle->GetEntries();
	cout<<"NEntries: "<<2<<endl;
	TCanvas *c1 = new TCanvas("c1", "c1", 800, 800);
	gStyle->SetTitleH(0.07);
	c1->Divide(1,2);
	c1->cd(1);
	Chainparticle->Draw("genevents.primaryEvent.mParticles.mPz>>htest(400, -5, 5)");
	TH1D *htest = (TH1D*)gDirectory->Get("htest");
	htest->SetNameTitle("P_{z} coordinate", "P_{z} coordinate from Starsim");
	htest->GetXaxis()->SetTitle("P_{z} [GeV/c]");
	htest->GetYaxis()->SetTitle("#frac{dN}{dP_{z}}");
	htest->GetYaxis()->SetTitleOffset(1.15);
	htest->GetXaxis()->SetTitleOffset(1);
	htest->GetXaxis()->CenterTitle(true);
	htest->GetXaxis()->SetLabelSize(0.05);
	htest->GetXaxis()->SetTitleSize(0.05);
	htest->GetYaxis()->CenterTitle(true);
	htest->GetYaxis()->SetLabelSize(0.05);
	htest->GetYaxis()->SetTitleSize(0.05);
	gPad->SetLeftMargin(0.14);
	gPad->SetRightMargin(0.12);
	gPad->SetBottomMargin(0.12);
	htest->Draw();
	c1->cd(2);
	h1->SetNameTitle("P_{z} coordinate", "P_{z} coordinate from THERMINATOR");
	h1->GetXaxis()->SetTitle("P_{z} [GeV/c]");
	h1->GetYaxis()->SetTitle("#frac{dN}{dP_{z}}");
	h1->GetYaxis()->SetTitleOffset(1.1);
	h1->GetXaxis()->SetTitleOffset(1);
	h1->GetXaxis()->CenterTitle(true);
	h1->GetXaxis()->SetLabelSize(0.05);
	h1->GetXaxis()->SetTitleSize(0.05);
	h1->GetYaxis()->CenterTitle(true);
	h1->GetYaxis()->SetLabelSize(0.05);
	h1->GetYaxis()->SetTitleSize(0.05);
	gPad->SetLeftMargin(0.14);
	gPad->SetRightMargin(0.12);
	gPad->SetBottomMargin(0.12);
	h1->Draw();
	
	c1->SaveAs("./Obrazki/pz-porównanie.png");
	

	
	return 0;
}