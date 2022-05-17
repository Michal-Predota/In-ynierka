#include <iostream>
#include <fstream>
#include <ostream>
#include <vector>
#include <string>
#include <typeinfo>
#include "../Parser/funkcje.cpp"
#include <TCanvas.h>
#include <TH1.h>
#include <TMath.h>
#include <algorithm>
#include <TGraph.h>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>

bool sortcol( const vector<double>& v1,
               const vector<double>& v2 ) {
    return v1[1] < v2[1];
}

using namespace std;

struct StructParticle {
	int ipart;
	Int_t pid;
	Float_t px, py, pz, e;
	Float_t mass;
	Float_t  x, y, z, t;
};

vector<double> pid_vec;
vector<vector<double>> do_hist;

int main(void)
{	
	TChain *Chain = new TChain("particles");
	Chain->Add("event000.root");
	StructParticle Particle;
	
	Chain->SetBranchAddress("particle", &Particle);
	
	TCanvas *c1 = new TCanvas("c1", "canvas1", 1000, 1000);
	c1->SetGrid();
	c1->SetBottomMargin(0.15);
	
	/***************************************Yields*********************************************/
	
/*		
	TH1D* yields = new TH1D("h1", "yields", 10, -150, 150);
	
	for(int i=0; i<Chain->GetEntries(); i++)
	{
		Chain->GetEntry(i);
		pid_vec.push_back(Particle.pid);
	}
	

	vector<vector<double>> tmp = ilosc_wystapien(pid_vec);
	std::sort(tmp.begin(), tmp.end(),sortcol);
	reverse(tmp.begin(),tmp.end());
	
	
	for(int i =0; i<10; i++)
	{
		do_hist.push_back(tmp.at(i));
	}
	
	for(int i = 1; i<10+1; i++)
	{
		yields->SetBinContent(i, do_hist.at(i-1).at(1));
	}
	yields->Sumw2();
	yields->SetMarkerStyle(20);
	c1->SetLogy();
	yields->SetStats(000);
	vector<string> nazwy = {"p", "n", "#pi^{0}", "#pi^{+}", "#pi^{-}", "#Sigma^{0}", "K^{0}", "#Sigma^{+}", "K^{+}", "#lambda"};
	for (int i=1; i<=10; i++) yields->GetXaxis()->SetBinLabel(i, nazwy.at(i-1).c_str());
	yields->Draw();
	c1->SaveAs("krotność cząstek.png");
*/


/*****************************************Czterowektor położeń i czasu**************************************************/
/*	
	c1->Divide(2, 2);
	
	TH1D *histx = new TH1D("r_x", "r_{x}", 100, -10, 10);
	histx->SetStats(0000);
	histx->GetXaxis()->SetTitle("x [fm]");
	histx->GetYaxis()->SetTitle("#frac{dN}{dx}");
	histx->GetYaxis()->SetTitleOffset(2.2);
	histx->GetXaxis()->CenterTitle(true);
	histx->GetYaxis()->CenterTitle(true);
	histx->SetTitleSize(0.04);
	histx->SetStats(0000);
	histx->SetMarkerStyle(20);
	histx->SetMarkerSize(0.7);
	histx->Sumw2();
	
	TH1D *histy = new TH1D("r_y", "r_{y}", 100, -10, 10);
	histy->SetStats(0000);
	histy->GetXaxis()->SetTitle("y [fm]");
	histy->GetYaxis()->SetTitle("#frac{dN}{dy}");
	histy->GetYaxis()->SetTitleOffset(2.2);
	histy->GetXaxis()->CenterTitle(true);
	histy->GetYaxis()->CenterTitle(true);
	histy->SetTitleSize(0.04);
	histy->SetStats(0000);
	histy->SetMarkerStyle(20);
	histy->SetMarkerSize(0.7);
	histy->Sumw2();
	
	TH1D *histz = new TH1D("r_z", "r_{z}", 100, -10, 10);
	histz->SetStats(0000);
	histz->GetXaxis()->SetTitle("z [fm]");
	histz->GetYaxis()->SetTitle("#frac{dN}{dz}");
	histz->GetYaxis()->SetTitleOffset(2.2);
	histz->GetXaxis()->CenterTitle(true);
	histz->GetYaxis()->CenterTitle(true);
	histz->SetTitleSize(0.04);
	histz->SetStats(0000);
	histz->SetMarkerStyle(20);
	histz->SetMarkerSize(0.7);
	histz->Sumw2();
	
	TH1D *histt = new TH1D("t", "t", 100, 0, 60);
	histt->SetStats(0000);
	histt->GetXaxis()->SetTitle("t [fm/c]");
	histt->GetYaxis()->SetTitle("#frac{dN}{dt}");
	histt->GetYaxis()->SetTitleOffset(2.2);
	histt->GetXaxis()->CenterTitle(true);
	histt->GetYaxis()->CenterTitle(true);
	histt->SetTitleSize(0.04);
	histt->SetStats(0000);
	histt->SetMarkerStyle(20);
	histt->SetMarkerSize(0.7);
	histt->Sumw2();
	
	for(int i=0; i<Chain->GetEntries(); i++)
	{
		Chain->GetEntry(i);
		if(Particle.pid==2212)
		{
			histx->Fill(Particle.x);
			histy->Fill(Particle.y);
			histz->Fill(Particle.z);
			histt->Fill(Particle.t);
		}
	}
	
	c1->cd(1);
	
	//gPad->SetRightMargin(0.001);
	gPad->SetLeftMargin(0.16);
	histx->Draw();
	
	c1->cd(2);
	
	gPad->SetLeftMargin(0.16);
	histy->Draw();
	
	c1->cd(3);
	
	gPad->SetLeftMargin(0.16);
	histz->Draw();
	
	c1->cd(4);
	
	gPad->SetLeftMargin(0.16);
	histt->Draw();
	
	c1->SaveAs("proton - polozenia i czas.png");
*/
	/***************************************Czterowektor pędów i Energii*********************************************************/
	
	c1->Divide(2, 2);
	
	TH1D *histe = new TH1D("e", "e", 100, 0.5, 2);
	histe->SetStats(0000);
	histe->GetXaxis()->SetTitle("E [GeV]");
	histe->GetYaxis()->SetTitle("#frac{dN}{dE}");
	histe->GetYaxis()->SetTitleOffset(2.2);
	histe->GetXaxis()->CenterTitle(true);
	histe->GetYaxis()->CenterTitle(true);
	histe->SetTitleSize(0.04);
	histe->SetStats(0000);
	histe->SetMarkerStyle(20);
	histe->SetMarkerSize(0.7);
	histe->Sumw2();
	
	TH1D *histpx = new TH1D("p_y", "p_{y}", 100, -2, 2);
	histpx->SetStats(0000);
	histpx->GetXaxis()->SetTitle("p_{y} [GeV/c]");
	histpx->GetYaxis()->SetTitle("#frac{dN}{dp_{y}}");
	histpx->GetYaxis()->SetTitleOffset(2.2);
	histpx->GetXaxis()->CenterTitle(true);
	histpx->GetYaxis()->CenterTitle(true);
	histpx->SetTitleSize(0.04);
	histpx->SetStats(0000);
	histpx->SetMarkerStyle(20);
	histpx->SetMarkerSize(0.7);
	histpx->Sumw2();
	
	TH1D *histpy = new TH1D("p_y", "p_{y}", 100, -2, 2);
	histpy->SetStats(0000);
	histpy->GetXaxis()->SetTitle("p_{y} [GeV/c]");
	histpy->GetYaxis()->SetTitle("#frac{dN}{dp_{y}}");
	histpy->GetYaxis()->SetTitleOffset(2.2);
	histpy->GetXaxis()->CenterTitle(true);
	histpy->GetYaxis()->CenterTitle(true);
	histpy->SetTitleSize(0.04);
	histpy->SetStats(0000);
	histpy->SetMarkerStyle(20);
	histpy->SetMarkerSize(0.7);
	histpy->Sumw2();
	
	TH1D *histpz = new TH1D("p_z", "p_{z}", 100, -2, 2);
	histpz->SetStats(0000);
	histpz->GetXaxis()->SetTitle("p_{z} [GeV/c]");
	histpz->GetYaxis()->SetTitle("#frac{dN}{dp_{z}}");
	histpz->GetYaxis()->SetTitleOffset(2.2);
	histpz->GetXaxis()->CenterTitle(true);
	histpz->GetYaxis()->CenterTitle(true);
	histpz->SetTitleSize(0.04);
	histpz->SetStats(0000);
	histpz->SetMarkerStyle(20);
	histpz->SetMarkerSize(0.7);
	histpz->Sumw2();
	
	for(int i=0; i<Chain->GetEntries(); i++)
	{
		Chain->GetEntry(i);
		if(Particle.pid==2212)
		{
			histpx->Fill(Particle.px);
			histpy->Fill(Particle.py);
			histpz->Fill(Particle.pz);
			histe->Fill(Particle.e);
		}
	}
	
	c1->cd(1);
	
	//gPad->SetRightMargin(0.001);
	gPad->SetLeftMargin(0.16);
	histpx->Draw();
	
	c1->cd(2);
	
	gPad->SetLeftMargin(0.16);
	histpy->Draw();
	
	c1->cd(3);
	
	gPad->SetLeftMargin(0.16);
	histpz->Draw();
	
	c1->cd(4);
	
	gPad->SetLeftMargin(0.16);
	histe->Draw();
	
	c1->SaveAs("proton - pęd i energia.png");
	
	
	
	
	
	return 0;
}

void histogramy()
{
	main();
}