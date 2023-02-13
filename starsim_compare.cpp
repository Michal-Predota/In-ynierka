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

int starsim_compare()
{
	TChain *Chain = new TChain("particles");
	TChain *Chainparticle = new TChain("genevents");
	
	int event_id;
	int eventid_curr;
	int particle_counter=0;
	
	TChain *Chain_inz = new TChain("particles");
	
	Chain->Add("event000.root");
	Chainparticle->Add("particles.starsim130ev.root");
	
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
	
	TH1D *h1 = new TH1D("", "", 100, 0, 2);
	
	StructParticle Particle_th;
	Chain_inz->SetBranchAddress("particle", &Particle_th);
	for(int i=0; i<130; i++)
	{
		//cout<<path<<endl;
		
		Chain_inz->GetEntry(particle_counter);
		
		event_id=Particle_th.eventid;
		eventid_curr=Particle_th.eventid;
		
		while(event_id==eventid_curr)
		{
			
			Chain_inz->GetEntry(particle_counter);
			if(Particle_th.pid==2212||Particle_th.pid==-2212||Particle_th.pid==111||Particle_th.pid==211||Particle_th.pid==310||Particle_th.pid==130||Particle_th.pid==321||Particle_th.pid==-211||Particle_th.pid==-321)
			{
				h1->Fill(Particle_th.mass);
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
	
	
	

	double title_size=0.11;
	gStyle->SetTitleFontSize(title_size);
	
	
	Long64_t NEntries=Chainparticle->GetEntries();
	cout<<"NEntries: "<<2<<endl;
	TCanvas *c1 = new TCanvas("c1", "c1", 1000, 900);
	c1->Divide(1,2);
	c1->cd(1);
	Chainparticle->Draw("genevents.primaryEvent.mParticles.mMass>>htest(100, 0, 2)");
	TH1D *htest = (TH1D*)gDirectory->Get("htest");
	htest->SetNameTitle("mass", "Mass from Starsim");
	htest->GetXaxis()->SetTitle("m [GeV/c^{2}]");
	htest->GetYaxis()->SetTitle("#frac{dN}{dm}");
	htest->GetYaxis()->SetTitleOffset(0.85);
	htest->GetXaxis()->SetTitleOffset(1);
	htest->GetXaxis()->CenterTitle(true);
	htest->GetXaxis()->SetTitleSize(title_size/1.5);
	htest->GetYaxis()->CenterTitle(true);
	htest->GetYaxis()->SetTitleSize(title_size/1.5);
	htest->GetXaxis()->SetLabelSize(0.055);
	htest->GetYaxis()->SetLabelSize(0.055);
	htest->SetStats(000);
	gPad->SetLeftMargin(0.15);
	gPad->SetBottomMargin(0.17);
	gPad->SetTopMargin(0.17);
	htest->Draw();
	c1->cd(2);
	h1->SetNameTitle("mass ", "Mass from THERMINATOR");
	h1->GetXaxis()->SetTitle("m [GeV/c^{2}]");
	h1->GetYaxis()->SetTitle("#frac{dN}{dm}");
	h1->GetYaxis()->SetTitleOffset(0.85);
	h1->GetXaxis()->SetTitleOffset(1);
	h1->GetXaxis()->CenterTitle(true);
	h1->GetXaxis()->SetTitleSize(title_size/1.5);
	h1->GetYaxis()->CenterTitle(true);
	h1->GetYaxis()->SetTitleSize(title_size/1.5);
	h1->GetXaxis()->SetLabelSize(0.055);
	h1->GetYaxis()->SetLabelSize(0.055);
	h1->SetStats(000);
	gPad->SetLeftMargin(0.15);
	gPad->SetBottomMargin(0.17);
	gPad->SetTopMargin(0.17);
	h1->Draw();
	
	c1->SaveAs("./Obrazki/masa-porównanie.png");
	

	
	return 0;
}