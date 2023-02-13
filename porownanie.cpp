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
int porownanie()
{
	int particle_id=111;



	TChain *chain_starsim = new TChain("StMiniMcTree");
    chain_starsim->Add("own.minimc130ev.root");
    Float_t mPx[ArrEntries], mPy[ArrEntries], mPz[ArrEntries], mEnergy[ArrEntries], mVx[ArrEntries], mVy[ArrEntries], mVz[ArrEntries], mTof[ArrEntries];
    Int_t mId[ArrEntries];
	Float_t mPzMc[ArrEntries];
	Float_t mPzPr[ArrEntries];
	Float_t mEtaPr[ArrEntries];
	Float_t mEtaMc[ArrEntries];
	Float_t mPhiPr[ArrEntries];
	Float_t mPhiMc[ArrEntries];
	Float_t mPtPr[ArrEntries];
	Float_t mPtMc[ArrEntries];

	TH1D *theta = new TH1D("#eta_{th}", "#eta_{th}", 100, -4, 4);
	TH1D *thphi = new TH1D("#Phi_{th}", "#Phi_{th}", 100, -3.5, 3.5);
	TH1D *thpt = new TH1D("pT_{th}", "pT_{th}", 100, 0, 3);
	TH1D *thpz = new TH1D("pz_{th}", "pz_{th}", 100, 0, 3.5);

	
    Long64_t NEntries=chain_starsim->GetEntries();

    cout << "Entries: " << NEntries << endl;


    TH2D* histeta = new TH2D("", "", 100, -4, 4, 100, -4, 4);
    TH2D* histphi = new TH2D("", "", 100, -3.5, 3.5, 100, -0.2, 0.2);
    TH2D* histpt = new TH2D("", "", 100, 0, 3, 100, -0.5, 0.5);
    TH2D* histpz = new TH2D("", "", 100, 0, 3.5, 100, -0.2, 0.2);

    TLeaf* leafNumParticles = (TLeaf*) chain_starsim->GetLeaf("mMcMult");

	chain_starsim->SetBranchAddress("mMatchedPairs.mPhiMc", mPhiMc);
	chain_starsim->SetBranchAddress("mMatchedPairs.mPhiPr", mPhiPr);
	chain_starsim->SetBranchAddress("mMatchedPairs.mPzMc", mPzMc);
	chain_starsim->SetBranchAddress("mMatchedPairs.mPzPr", mPzPr);
	chain_starsim->SetBranchAddress("mMatchedPairs.mEtaMc", mEtaMc);
	chain_starsim->SetBranchAddress("mMatchedPairs.mEtaPr", mEtaPr);
	chain_starsim->SetBranchAddress("mMatchedPairs.mPtPr", mPtPr);
	chain_starsim->SetBranchAddress("mMatchedPairs.mPtMc", mPtMc);

    for(Long64_t i=0; i<NEntries; i++)
    {
        Int_t totBytes = chain_starsim->GetEntry(i);

        Int_t nParticles = leafNumParticles->GetValue();
        cout << i+1 <<" event/ particles: " << nParticles << endl;

        for(Int_t j=0; j<nParticles; j++)
        {
			//if(mPtPr[j]>0.2 && mPtPr[j]<3)
			//{
                histpt->Fill(mPtMc[j], mPtPr[j]-mPtMc[j]);
				thpt->Fill(mPtPr[j]);
                histeta->Fill(mEtaMc[j], mEtaPr[j]-mEtaMc[j]);
				theta->Fill(mEtaPr[j]);
                histpz->Fill(mPzMc[j], mPzPr[j]-mPzMc[j]);
				thpz->Fill(mPzPr[j]);
                histphi->Fill(mPhiMc[j], mPhiPr[j]-mPhiMc[j]);
				thphi->Fill(mPhiPr[j]);
			//}
        }
    }


	double title_size=0.1;
	
	gStyle->SetTitleFontSize(title_size);
	
	
	TCanvas *c1 = new TCanvas("c1", "c1", 1200, 900);
	c1->Divide(2,2);
	c1->cd(1);
	histphi->GetXaxis()->SetTitle("#Phi_{reco} ");
	histphi->GetYaxis()->SetTitle("#Phi_{th}-#Phi_{reco}");
	histphi->SetStats(000);
//	histpz->SetTitleSize(0.04);
	histphi->GetXaxis()->SetTitleSize(title_size/1.5);
	histphi->GetYaxis()->SetTitleSize(title_size/1.5);
	histphi->GetYaxis()->CenterTitle(true);
	histphi->GetXaxis()->CenterTitle(true);
	gPad->SetLeftMargin(0.16);
	gPad->SetBottomMargin(0.16);
	gPad->SetTopMargin(0.16);
	histphi->Draw("colz");
	c1->cd(3);
	TH1D *hist_projectionXphi = histphi->ProjectionX("#Phi_{reco} ", 0, -1);
	hist_projectionXphi->SetNameTitle("X projection", "X projection");
	hist_projectionXphi->SetStats(000);
//	hist_projectionXphi->SetTitleSize(0.04);
	hist_projectionXphi->GetXaxis()->CenterTitle(true);
	hist_projectionXphi->GetXaxis()->SetTitleSize(title_size/1.5);
	hist_projectionXphi->GetYaxis()->CenterTitle(true);
	hist_projectionXphi->GetYaxis()->SetTitleSize(title_size/1.5);
	gPad->SetBottomMargin(0.16);
	gPad->SetLeftMargin(0.16);
	gPad->SetTopMargin(0.16);
	hist_projectionXphi->GetXaxis()->SetTitle("#Phi_{reco}");
	hist_projectionXphi->GetYaxis()->SetTitle("dN/#Phi_{reco}");
	hist_projectionXphi->Draw("");
	c1->cd(2);
	TH1D *hist_projectionYphi = histphi->ProjectionY("#Phi ", 0, -1);
	hist_projectionYphi->SetNameTitle("Y projection", "Y projection");
	hist_projectionYphi->SetStats(000);
	TGraph *graph_projectionYphi = new TGraph(hist_projectionYphi);
	TGraph *projection_flippedphi= new TGraph();
	for(int i=0; i<graph_projectionYphi->GetN(); i++)
	{
		projection_flippedphi->AddPoint(graph_projectionYphi->GetPointY(i), graph_projectionYphi->GetPointX(i));
	}
	projection_flippedphi->SetNameTitle("Y projection", "Y projection");
	projection_flippedphi->SetLineColor(graph_projectionYphi->GetLineColor());
	projection_flippedphi->SetMinimum(-0.2);
	projection_flippedphi->SetMaximum(0.2);
//	projection_flipped->SetTitleSize(0.04);
	projection_flippedphi->GetXaxis()->CenterTitle(true);
	projection_flippedphi->GetXaxis()->SetTitleSize(title_size/1.5);
	projection_flippedphi->GetYaxis()->CenterTitle(true);
	projection_flippedphi->GetYaxis()->SetTitleSize(title_size/1.5);
	gPad->SetBottomMargin(0.17);
	gPad->SetLeftMargin(0.16);
	gPad->SetTopMargin(0.16);
	projection_flippedphi->GetXaxis()->SetTitle("dN/d(#Phi_{th}-#Phi_{reco})");
	projection_flippedphi->GetYaxis()->SetTitle("#Phi_{th}-#Phi_{reco}");
	projection_flippedphi->Draw();
	c1->cd(4);
	thphi->SetStats(000);
	thphi->GetXaxis()->SetTitleSize(title_size/1.5);
	thphi->GetYaxis()->SetTitleSize(title_size/1.5);
	gPad->SetLeftMargin(0.14);
	gPad->SetBottomMargin(0.16);
	gPad->SetTopMargin(0.16);
//	thphi->SetTitleSize(0.04);
	thphi->GetYaxis()->CenterTitle(true);
	thphi->GetXaxis()->CenterTitle(true);
	thphi->GetXaxis()->SetTitle("#Phi_{th}");
	thphi->GetYaxis()->SetTitle("dN/#Phi_{th}");
	thphi->Draw();
	
	c1->SaveAs("./Obrazki/Phi_porownanie_all.png");
	
	
	
	
	TCanvas *c2 = new TCanvas("c2", "c2", 1200, 900);
	c2->Divide(2,2);
	c2->cd(1);
	histpz->GetXaxis()->SetTitle("pz [GeV/c]");
	histpz->GetYaxis()->SetTitle("pz_{th}-pz_{reco} [GeV/c]");
	histpz->SetStats(000);
//	histpz->SetTitleSize(0.04);
	histpz->GetXaxis()->SetTitleSize(title_size/1.5);
	histpz->GetYaxis()->SetTitleSize(title_size/1.5);
	histpz->GetYaxis()->CenterTitle(true);
	histpz->GetXaxis()->CenterTitle(true);
	gPad->SetLeftMargin(0.16);
	gPad->SetBottomMargin(0.16);
	gPad->SetTopMargin(0.16);
	histpz->Draw("colz");
	c2->cd(3);
	TH1D *hist_projectionXpz = histpz->ProjectionX("pz_{reco} [GeV/c] ", 0, -1);
	hist_projectionXpz->SetNameTitle("X projection", "X projection");
	hist_projectionXpz->SetStats(000);
//	hist_projectionXeta->SetTitleSize(0.04);
	hist_projectionXpz->GetXaxis()->CenterTitle(true);
	hist_projectionXpz->GetXaxis()->SetTitleSize(title_size/1.5);
	hist_projectionXpz->GetYaxis()->CenterTitle(true);
	hist_projectionXpz->GetYaxis()->SetTitleSize(title_size/1.5);
	gPad->SetBottomMargin(0.16);
	gPad->SetLeftMargin(0.16);
	gPad->SetTopMargin(0.16);
	hist_projectionXpz->GetXaxis()->SetTitle("pz_{reco} [GeV]");
	hist_projectionXpz->GetYaxis()->SetTitle("dN/pz_{reco}");
	hist_projectionXpz->Draw("");
	c2->cd(2);
	TH1D *hist_projectionYpz = histpz->ProjectionY("pz [GeV/c] ", 0, -1);
	hist_projectionYpz->SetNameTitle("Y projection", "Y projection");
	hist_projectionYpz->SetStats(000);
	TGraph *graph_projectionYpz = new TGraph(hist_projectionYpz);
	TGraph *projection_flippedpz= new TGraph();
	for(int i=0; i<graph_projectionYpz->GetN(); i++)
	{
		projection_flippedpz->AddPoint(graph_projectionYpz->GetPointY(i), graph_projectionYpz->GetPointX(i));
	}
	projection_flippedpz->SetNameTitle("Y projection", "Y projection");
	projection_flippedpz->SetLineColor(graph_projectionYpz->GetLineColor());
	projection_flippedpz->SetMinimum(-0.2);
	projection_flippedpz->SetMaximum(0.2);
//	projection_flipped->SetTitleSize(0.04);
	projection_flippedpz->GetXaxis()->CenterTitle(true);
	projection_flippedpz->GetXaxis()->SetTitleSize(title_size/1.5);
	projection_flippedpz->GetYaxis()->CenterTitle(true);
	projection_flippedpz->GetYaxis()->SetTitleSize(title_size/1.5);
	gPad->SetBottomMargin(0.17);
	gPad->SetLeftMargin(0.16);
	gPad->SetTopMargin(0.16);
	projection_flippedpz->GetXaxis()->SetTitle("dN/d(pz_{th}-pz_{reco})");
	projection_flippedpz->GetYaxis()->SetTitle("pz_{th}-pz_{reco} [GeV]");
	projection_flippedpz->Draw();
	c2->cd(4);
	thpz->SetStats(000);
	thpz->GetXaxis()->SetTitleSize(title_size/1.5);
	thpz->GetYaxis()->SetTitleSize(title_size/1.5);
	gPad->SetLeftMargin(0.14);
	gPad->SetBottomMargin(0.16);
	gPad->SetTopMargin(0.16);
//	thpz->SetTitleSize(0.04);
	thpz->GetYaxis()->CenterTitle(true);
	thpz->GetXaxis()->CenterTitle(true);
	thpz->GetXaxis()->SetTitle("pz_{th} [GeV]");
	thpz->GetYaxis()->SetTitle("dN/dpz_{th}");
	thpz->Draw();
	
	c2->SaveAs("./Obrazki/pz_porownanie_all.png");
	
	
	
	
	TCanvas *c3 = new TCanvas("c3", "c3", 1200, 900);
	c3->Divide(2,2);
	c3->cd(1);
	histpt->GetXaxis()->SetTitle("pT_{reco} [GeV/c]");
	histpt->GetYaxis()->SetTitle("pT_{th}-pT_{reco} [GeV/c]");
	histpt->SetStats(000);
//	histpz->SetTitleSize(0.04);
	histpt->GetXaxis()->SetTitleSize(title_size/1.5);
	histpt->GetYaxis()->SetTitleSize(title_size/1.5);
	histpt->GetYaxis()->CenterTitle(true);
	histpt->GetXaxis()->CenterTitle(true);
	gPad->SetLeftMargin(0.16);
	gPad->SetBottomMargin(0.16);
	gPad->SetTopMargin(0.16);
	histpt->Draw("colz");
	c3->cd(3);
	TH1D *hist_projectionXpt = histpt->ProjectionX("pT_{reco} [GeV/c] ", 0, -1);
	hist_projectionXpt->SetNameTitle("X projection", "X projection");
	hist_projectionXpt->SetStats(000);
//	hist_projectionXeta->SetTitleSize(0.04);
	hist_projectionXpt->GetXaxis()->CenterTitle(true);
	hist_projectionXpt->GetXaxis()->SetTitleSize(title_size/1.5);
	hist_projectionXpt->GetYaxis()->CenterTitle(true);
	hist_projectionXpt->GetYaxis()->SetTitleSize(title_size/1.5);
	gPad->SetBottomMargin(0.16);
	gPad->SetLeftMargin(0.16);
	gPad->SetTopMargin(0.16);
	hist_projectionXpt->GetXaxis()->SetTitle("pT_{reco} [GeV]");
	hist_projectionXpt->GetYaxis()->SetTitle("dN/pT_{reco}");
	hist_projectionXpt->Draw("");
	c3->cd(2);
	TH1D *hist_projectionYpt = histpt->ProjectionY("pT [GeV/c] ", 0, -1);
	hist_projectionYpt->SetNameTitle("Y projection", "Y projection");
	hist_projectionYpt->SetStats(000);
	TGraph *graph_projectionYpt = new TGraph(hist_projectionYpt);
	TGraph *projection_flippedpt= new TGraph();
	for(int i=0; i<graph_projectionYpt->GetN(); i++)
	{
		projection_flippedpt->AddPoint(graph_projectionYpt->GetPointY(i), graph_projectionYpt->GetPointX(i));
	}
	projection_flippedpt->SetNameTitle("Y projection", "Y projection");
	projection_flippedpt->SetLineColor(graph_projectionYpt->GetLineColor());
	projection_flippedpt->SetMinimum(-1);
	projection_flippedpt->SetMaximum(1);
//	projection_flipped->SetTitleSize(0.04);
	projection_flippedpt->GetXaxis()->CenterTitle(true);
	projection_flippedpt->GetXaxis()->SetTitleSize(title_size/1.5);
	projection_flippedpt->GetYaxis()->CenterTitle(true);
	projection_flippedpt->GetYaxis()->SetTitleSize(title_size/1.5);
	gPad->SetBottomMargin(0.17);
	gPad->SetLeftMargin(0.16);
	gPad->SetTopMargin(0.16);
	projection_flippedpt->GetXaxis()->SetTitle("dN/d(pT_{th}-pT_{reco})");
	projection_flippedpt->GetYaxis()->SetTitle("pT_{th}-pT_{reco} [GeV]");
	projection_flippedpt->Draw();
	c3->cd(4);
	thpt->SetStats(000);
	thpt->GetXaxis()->SetTitleSize(title_size/1.5);
	thpt->GetYaxis()->SetTitleSize(title_size/1.5);
	gPad->SetLeftMargin(0.14);
	gPad->SetBottomMargin(0.16);
	gPad->SetTopMargin(0.16);
//	thpt->SetTitleSize(0.04);
	thpt->GetYaxis()->CenterTitle(true);
	thpt->GetXaxis()->CenterTitle(true);
	thpt->GetXaxis()->SetTitle("pT_{th} [GeV]");
	thpt->GetYaxis()->SetTitle("dN/dpT_{th}");
	thpt->Draw();
	
	c3->SaveAs("./Obrazki/pt_porownanie_all.png");
	
	
	
	TCanvas *c4 = new TCanvas("c4", "c4", 1200, 900);
	c4->Divide(2,2);
	c4->cd(1);
	histeta->GetXaxis()->SetTitle("#eta_{reco}");
	histeta->GetYaxis()->SetTitle("#eta_{th}-#eta_{reco}");
	histeta->SetStats(000);
//	histpz->SetTitleSize(0.04);
	histeta->GetXaxis()->SetTitleSize(title_size/1.5);
	histeta->GetYaxis()->SetTitleSize(title_size/1.5);
	histeta->GetYaxis()->CenterTitle(true);
	histeta->GetXaxis()->CenterTitle(true);
	gPad->SetLeftMargin(0.16);
	gPad->SetBottomMargin(0.14);
	gPad->SetTopMargin(0.16);
	gPad->SetRightMargin(0.16);
	histeta->Draw("colz");
	c4->cd(3);
	TH1D *hist_projectionXeta = histeta->ProjectionX("#eta_{reco}", 0, -1);
	hist_projectionXeta->SetNameTitle("X projection", "X projection");
	hist_projectionXeta->SetStats(000);
//	hist_projectionXeta->SetTitleSize(0.04);
	hist_projectionXeta->GetXaxis()->CenterTitle(true);
	hist_projectionXeta->GetXaxis()->SetTitleSize(title_size/1.5);
	hist_projectionXeta->GetYaxis()->CenterTitle(true);
	hist_projectionXeta->GetYaxis()->SetTitleSize(title_size/1.5);
	gPad->SetBottomMargin(0.14);
	gPad->SetLeftMargin(0.16);
	gPad->SetTopMargin(0.16);
	hist_projectionXeta->GetXaxis()->SetTitle("#eta_{reco}");
	hist_projectionXeta->GetYaxis()->SetTitle("dN/d#eta_{reco}");
	hist_projectionXeta->Draw("");
	c4->cd(2);
	TH1D *hist_projectionYeta = histeta->ProjectionY("#eta", 0, -1);
	hist_projectionYeta->SetNameTitle("Y projection", "Y projection");
	hist_projectionYeta->SetStats(000);
	TGraph *graph_projectionYeta = new TGraph(hist_projectionYeta);
	TGraph *projection_flippedeta= new TGraph();
	for(int i=0; i<graph_projectionYeta->GetN(); i++)
	{
		projection_flippedeta->AddPoint(graph_projectionYeta->GetPointY(i), graph_projectionYeta->GetPointX(i));
	}
	projection_flippedeta->SetNameTitle("Y projection", "Y projection");
	projection_flippedeta->SetLineColor(graph_projectionYeta->GetLineColor());
	projection_flippedeta->SetMinimum(-4);
	projection_flippedeta->SetMaximum(4);
//	projection_flipped->SetTitleSize(0.04);
	projection_flippedeta->GetXaxis()->CenterTitle(true);
	projection_flippedeta->GetXaxis()->SetTitleSize(title_size/1.5);
	projection_flippedeta->GetYaxis()->CenterTitle(true);
	projection_flippedeta->GetYaxis()->SetTitleSize(title_size/1.5);
	gPad->SetBottomMargin(0.15);
	gPad->SetLeftMargin(0.16);
	gPad->SetTopMargin(0.16);
	projection_flippedeta->GetXaxis()->SetTitle("dN/d(#eta_{th}-#eta_{reco})");
	projection_flippedeta->GetYaxis()->SetTitle("#eta_{th}-#eta_{reco}");
	projection_flippedeta->Draw();
	c4->cd(4);
	theta->SetStats(000);
	theta->GetXaxis()->SetTitleSize(title_size/1.5);
	theta->GetYaxis()->SetTitleSize(title_size/1.5);
	gPad->SetLeftMargin(0.14);
	gPad->SetBottomMargin(0.14);
	gPad->SetTopMargin(0.14);
//	thpt->SetTitleSize(0.04);
	theta->GetYaxis()->CenterTitle(true);
	theta->GetXaxis()->CenterTitle(true);
	theta->GetXaxis()->SetTitle("#eta_{th}");
	theta->GetYaxis()->SetTitle("dN/d#eta_{th}");
	theta->Draw();
	
	c4->SaveAs("./Obrazki/eta_porownanie_all.png");
	
	TCanvas *c5 = new TCanvas("c5", "c5", 1200, 900);
	gPad->SetLeftMargin(0.15);
	gPad->SetBottomMargin(0.15);
	gPad->SetTopMargin(0.15);
	histphi->GetXaxis()->SetTitleOffset(0.8);
	histphi->Draw("colz");
	c5->SaveAs("./Obrazki/phi_roznica_all.png");
	TCanvas *c6 = new TCanvas("c6", "c6", 1200, 900);
	gPad->SetLeftMargin(0.15);
	gPad->SetBottomMargin(0.15);
	gPad->SetTopMargin(0.15);
	histeta->GetXaxis()->SetTitleOffset(0.8);
	histeta->Draw("colz");
	c6->SaveAs("./Obrazki/eta_roznica_all.png");
	TCanvas *c7 = new TCanvas("c7", "c7", 1200, 900);
	gPad->SetLeftMargin(0.15);
	gPad->SetBottomMargin(0.15);
	gPad->SetTopMargin(0.15);
	histpt->GetXaxis()->SetTitleOffset(0.8);
	histpt->Draw("colz");
	c7->SaveAs("./Obrazki/pt_roznica_all.png");
	TCanvas *c8 = new TCanvas("c8", "c8", 1200, 900);
	gPad->SetLeftMargin(0.16);
	gPad->SetBottomMargin(0.15);
	gPad->SetTopMargin(0.15);
	histpz->GetXaxis()->SetTitleOffset(0.8);
	histpz->Draw("colz");
	c8->SaveAs("./Obrazki/pz_roznica_all.png");

	return 0;
}
