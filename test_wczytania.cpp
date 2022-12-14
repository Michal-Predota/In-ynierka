#include <iostream>
#include <vector>
#include <TH1D.h>
#include <TChain.h>
#include <TCanvas.h>

struct StructParticle {
	Float_t mass;
	Float_t t, x, y, z;
	Float_t e, px, py, pz;
	Int_t decayed, pid, fatherpid;
	Int_t rootpid, eid, fathereid;
	UInt_t eventid;
};

struct StructEvent{
	UInt_t eventID;
	UInt_t entries;
	UInt_t entriesprev;
};

const int ArrEntries = 99999;

using namespace std;
int test_wczytania()
{
	int particle_id=111;


	TChain *event_starsim = new TChain("genevents");
	event_starsim->Add("particles.starsim_50ev.root");

	TChain *chain_starsim = new TChain("genevents");
    chain_starsim->Add("particles.starsim_50ev.root");
    Float_t mPx[ArrEntries], mPy[ArrEntries], mPz[ArrEntries], mEnergy[ArrEntries], mVx[ArrEntries], mVy[ArrEntries], mVz[ArrEntries], mTof[ArrEntries];
    Int_t mId[ArrEntries];

	vector<double> x_vec, y_vec, z_vec, t_vec, m_vec, e_vec, px_vec, py_vec, pz_vec;
	vector<int> id_vec;


	TChain *chain_th = new TChain("particles");
	chain_th->Add("event000.root");

	TH1D *th = new TH1D("py th", "py th", 100, -2, 2);

	StructParticle Particle;
	int event_id;
	int eventid_curr;
	int particle_counter=0;

	chain_th->SetBranchAddress("particle", &Particle);

	for(int i=0; i<50; i++)
	{
		//cout<<path<<endl;

		chain_th->GetEntry(particle_counter);

		event_id=Particle.eventid;
		eventid_curr=Particle.eventid;

		while(event_id==eventid_curr)
		{

			chain_th->GetEntry(particle_counter);
			if(Particle.pid==particle_id)
			{
				th->Fill(Particle.py);

				x_vec.push_back(Particle.x);
				y_vec.push_back(Particle.y);
				z_vec.push_back(Particle.z);
				t_vec.push_back(Particle.t);
				m_vec.push_back(Particle.mass);
				e_vec.push_back(Particle.e);
				px_vec.push_back(Particle.px);
				py_vec.push_back(Particle.py);
				pz_vec.push_back(Particle.pz);
				id_vec.push_back(Particle.pid);

			}

			particle_counter++;
			eventid_curr=Particle.eventid;

		}
		event_id=eventid_curr;
	}


	chain_starsim->SetBranchAddress("mParticles.mPx", mPx);
    chain_starsim->SetBranchAddress("mParticles.mPy", mPy);
    chain_starsim->SetBranchAddress("mParticles.mPz", mPz);
   chain_starsim->SetBranchAddress("mParticles.mEnergy", mEnergy);
    chain_starsim->SetBranchAddress("mParticles.mVx", mVx);
    chain_starsim->SetBranchAddress("mParticles.mVy", mVy);
    chain_starsim->SetBranchAddress("mParticles.mVz", mVz);
    chain_starsim->SetBranchAddress("mParticles.mTof", mTof);
    chain_starsim->SetBranchAddress("mParticles.mId", mId);

    Long64_t NEntries=chain_starsim->GetEntries();

    cout << "Entries: " << NEntries << endl;


    TH2D* hist = new TH2D("pz starsim", "pz starsim", 100, -2, 2, 100, -2, 2);

    TLeaf* leafNumParticles = (TLeaf*) chain_starsim->GetLeaf("mNumParticles");

    TLeaf* leafPy = (TLeaf*) chain_starsim->GetLeaf("mParticles.mPz");
    cout << leafPy << endl;

	int counter=0;
    for(Long64_t i=0; i<NEntries; i++)
    {
        Int_t totBytes = chain_starsim->GetEntry(i);

        Int_t nParticles = leafNumParticles->GetValue();
        //cout << i+1 <<" event/ particles: " << nParticles << endl;

        for(Int_t j=0; j<nParticles; j++)
        {
            if(mId[j]==particle_id)
			{
                hist->Fill(leafPy->GetValue(j),pz_vec.at(counter)-leafPy->GetValue(j));
				counter++;
            }
        }
    }
	cout<<counter<<endl;




	TCanvas *c1 = new TCanvas("c1", "c1", 800, 800);
	c1->Divide(2,2);
	c1->cd(1);
	hist->GetXaxis()->SetTitle("pz starsim");
	hist->GetYaxis()->SetTitle("roznica pz_th-pz_starsim");
	gPad->SetLeftMargin(0.14);
	hist->Draw("colz");
	c1->cd(3);
	TH1D *hist_projectionX = hist->ProjectionX("pz", 0, -1);
	hist_projectionX->SetNameTitle("X projection", "X projection");
	hist_projectionX->Draw("");
	c1->cd(2);
	TH1D *hist_projectionY = hist->ProjectionY("pz", 0, -1);
	hist_projectionY->SetNameTitle("Y projection", "Y projection");
	//px_hist_projectionY->Draw("hbar");
	TGraph *graph_projectionY = new TGraph(hist_projectionY);
	//px_graph_projectionY->Draw();
	TGraph *projection_flipped = new TGraph();
	for(int i=0; i<graph_projectionY->GetN(); i++)
	{
		projection_flipped->AddPoint(graph_projectionY->GetPointY(i), graph_projectionY->GetPointX(i));
	}
	projection_flipped->SetLineColor(graph_projectionY->GetLineColor());
	projection_flipped->SetMinimum(-2);
	projection_flipped->SetMaximum(2);
	projection_flipped->Draw();
	c1->cd(4);
	th->Draw();

	return 0;
}