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
	
	
	
	
	
	
	
	
	
	/***********************************Ważne!!!!!*****************************************/
	int current_id = 3212;//Należy ustawić by wszędzie działać na tej samej cząstce
	/**************************************************************************************/
	
	
	
	
	
	
	
	
	/***************************************Yields*********************************************/
	
/*	
	TCanvas *c1 = new TCanvas("c1", "canvas1", 1000, 1000);
	c1->SetGrid();
	c1->SetBottomMargin(0.15);

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
	//Należy podać jaka cząsteczka jest zapisywana w nazwie pliku oraz wpisać jej pid w pętli for
	
	TCanvas *c2 = new TCanvas("c2", "canvas2", 1000, 1000);

	c2->Divide(2, 2);
	
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
		if(Particle.pid==current_id)
		{
			histx->Fill(Particle.x);
			histy->Fill(Particle.y);
			histz->Fill(Particle.z);
			histt->Fill(Particle.t);
		}
	}
	
	c2->cd(1);
	
	//gPad->SetRightMargin(0.001);
	gPad->SetLeftMargin(0.16);
	histx->Draw();
	
	c2->cd(2);
	
	gPad->SetLeftMargin(0.16);
	histy->Draw();
	
	c2->cd(3);
	
	gPad->SetLeftMargin(0.16);
	histz->Draw();
	
	c2->cd(4);
	
	gPad->SetLeftMargin(0.16);
	histt->Draw();
	
	

	/***************************************Czterowektor pędów i Energii*********************************************************/
	//Należy podać jaka cząsteczka jest zapisywana w nazwie pliku oraz wpisać jej pid w pętli for

	TCanvas *c3 = new TCanvas("c3", "canvas3", 1000, 1000);

	c3->Divide(2, 2);
	
	TH1D *histe = new TH1D("e", "E", 100, 0, 1.4);
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
	
	TH1D *histpx = new TH1D("p_x", "p_{x}", 100, -1, 1);
	histpx->SetStats(0000);
	histpx->GetXaxis()->SetTitle("p_{x} [GeV/c]");
	histpx->GetYaxis()->SetTitle("#frac{dN}{dp_{x}}");
	histpx->GetYaxis()->SetTitleOffset(2.2);
	histpx->GetXaxis()->CenterTitle(true);
	histpx->GetYaxis()->CenterTitle(true);
	histpx->SetTitleSize(0.04);
	histpx->SetStats(0000);
	histpx->SetMarkerStyle(20);
	histpx->SetMarkerSize(0.7);
	histpx->Sumw2();
	
	TH1D *histpy = new TH1D("p_y", "p_{y}", 100, -1, 1);
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
	
	TH1D *histpz = new TH1D("p_z", "p_{z}", 100, -1, 1);
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
		if(Particle.pid==current_id)
		{
			histpx->Fill(Particle.px);
			histpy->Fill(Particle.py);
			histpz->Fill(Particle.pz);
			histe->Fill(Particle.e);
		}
	}
	
	c3->cd(1);
	
	//gPad->SetRightMargin(0.001);
	gPad->SetLeftMargin(0.16);
	histpx->Draw();
	
	c3->cd(2);
	
	gPad->SetLeftMargin(0.16);
	histpy->Draw();
	
	c3->cd(3);
	
	gPad->SetLeftMargin(0.16);
	histpz->Draw();
	
	c3->cd(4);
	
	gPad->SetLeftMargin(0.16);
	histe->Draw();
	
	



/**********************************************************************************************Różne obliczenia******************************************************************************/

	TCanvas *c4 = new TCanvas("c4", "canvas1", 1000, 1000);
	

	/********************transversal momentum****************************/
	vector<double> p1;
	vector<double> p2;
	
	for(int i=0; i<Chain->GetEntries(); i++)
	{
		Chain->GetEntry(i);
		if(Particle.pid==current_id)
		{
			p1.push_back(Particle.px);
			p2.push_back(Particle.py);
		}
	}
	
	c4->Divide(2, 2);
	
	vector<double> p_T;
	
	for(int i = 0; i<p1.size(); i++)
	{
		p_T.push_back(TMath::Sqrt(TMath::Power(p1.at(i), 2)+TMath::Power(p2.at(i), 2)));
	}
	
	double max1 = *max_element(std::begin(p_T), std::end(p_T));
	double min1 = *min_element(std::begin(p_T), std::end(p_T));
	
	TH1D *histpt = new TH1D("p_T", "p_{T}", 100, min1, 1);
	histpt->SetStats(0000);
	histpt->GetXaxis()->SetTitle("p_{z} [GeV/c]");
	histpt->GetYaxis()->SetTitle("#frac{dN}{dp_{z}}");
	histpt->GetYaxis()->SetTitleOffset(2.2);
	histpt->GetXaxis()->CenterTitle(true);
	histpt->GetYaxis()->CenterTitle(true);
	histpt->SetTitleSize(0.04);
	histpt->SetStats(0000);
	histpt->SetMarkerStyle(20);
	histpt->SetMarkerSize(0.7);
	histpt->Sumw2();
	
	for(int i = 0; i<p_T.size(); i++)
	{
		histpt->Fill(p_T.at(i));
	}
	gPad->SetRightMargin(0.001);
	gPad->SetLeftMargin(0.15);
	
	
	
	//c1->SaveAs("%s - p_T.png", current_name);
	
	
	/********************rapidity****************************/
	
	vector<double> E;
	vector<double> p3;
	
	for(int i=0; i<Chain->GetEntries(); i++)
	{
		Chain->GetEntry(i);
		if(Particle.pid==current_id)
		{
			E.push_back(Particle.e);
			p3.push_back(Particle.pz);
		}
	}
	
	vector<double> rapidity;
	
	for(int i = 0; i<p3.size(); i++)
	{
		rapidity.push_back(0.5*TMath::Log((E.at(i)+p3.at(i))/(E.at(i)-p3.at(i))));
	}
	
	double max2 = *max_element(std::begin(rapidity), std::end(rapidity));
	double min2 = *min_element(std::begin(rapidity), std::end(rapidity));
	
	TH1D *histrap = new TH1D("rapidity", "y", 100, min2, max2);
	histrap->GetXaxis()->SetTitle("y");
	histrap->GetYaxis()->SetTitle("#frac{N}{dy}");
	histrap->GetYaxis()->SetTitleOffset(2.2);
	histrap->GetXaxis()->CenterTitle(true);
	histrap->GetYaxis()->CenterTitle(true);
	histrap->SetTitleSize(0.04);
	histrap->SetStats(0000);
	histrap->SetMarkerStyle(20);
	histrap->SetMarkerSize(0.7);
	histrap->Sumw2();
	
	for(int i = 0; i<rapidity.size(); i++)
	{
		histrap->Fill(rapidity.at(i));
	}
	gPad->SetLeftMargin(0.15);
	
	
	
	//c1->SaveAs("rapidity - %s.png", current_name);
	
	/***************************transversal coordinate*******************************/
	vector<double> r1;
	vector<double> r2;
	
	for(int i=0; i<Chain->GetEntries(); i++)
	{
		Chain->GetEntry(i);
		if(Particle.pid==current_id)
		{
			r1.push_back(Particle.x);
			r2.push_back(Particle.y);
		}
	}
	
	vector<double> r_T;
	
	for(int i = 0; i<r1.size(); i++)
	{
		r_T.push_back(TMath::Sqrt(TMath::Power(r1.at(i), 2)+TMath::Power(r2.at(i), 2)));
	}
	
	double max3 = *max_element(std::begin(r_T), std::end(r_T));
	double min3 = *min_element(std::begin(r_T), std::end(r_T));
	
	TH1D *histrt = new TH1D("r_T", "r_{T}", 100, min3, 20);
	histrt->GetXaxis()->SetTitle("r_{T} [fm]");
	histrt->GetYaxis()->SetTitle("#frac{N}{dr_{T}}");
	histrt->GetYaxis()->SetTitleOffset(2.2);
	histrt->GetXaxis()->CenterTitle(true);
	histrt->GetYaxis()->CenterTitle(true);
	histrt->SetTitleSize(0.04);
	histrt->SetStats(0000);
	histrt->SetMarkerStyle(20);
	histrt->SetMarkerSize(0.7);
	histrt->Sumw2();
	
	for(int i = 0; i<r_T.size(); i++)
	{
		histrt->Fill(r_T.at(i));
	}
	gPad->SetLeftMargin(0.15);
	
	
	
	//c1->SaveAs("transverse coordinate - %s.png", current_name);
	
	
	/**********************************pseudorapidity********************************/
	
	vector<double> pseudorapidity;
	
	for(int i = 0; i<p1.size(); i++)
	{
		pseudorapidity.push_back(0.5*TMath::Log((E.at(i)+p1.at(i))/(E.at(i)-p1.at(i))));
	}
	
	double max4 = *max_element(std::begin(pseudorapidity), std::end(pseudorapidity));
	double min4 = *min_element(std::begin(pseudorapidity), std::end(pseudorapidity));
	
	TH1D *histpseurap = new TH1D("pseudorapidity", "#eta", 100, min4, max4);
	histpseurap->GetXaxis()->SetTitle("#eta");
	histpseurap->GetYaxis()->SetTitle("#frac{N}{d#eta}");
	histpseurap->GetYaxis()->SetTitleOffset(2.2);
	histpseurap->GetXaxis()->CenterTitle(true);
	histpseurap->GetYaxis()->CenterTitle(true);
	histpseurap->SetTitleSize(0.04);
	histpseurap->SetStats(0000);
	histpseurap->SetMarkerStyle(20);
	histpseurap->SetMarkerSize(0.7);
	histpseurap->Sumw2();
	
	for(int i = 0; i<E.size(); i++)
	{
		histpseurap->Fill(pseudorapidity.at(i));
	}
	gPad->SetLeftMargin(0.15);
	
	
	
	c4->cd(1);
	
	//gPad->SetRightMargin(0.001);
	gPad->SetLeftMargin(0.16);
	histpt->Draw();
	
	c4->cd(2);
	
	gPad->SetLeftMargin(0.16);
	histrap->Draw();
	
	c4->cd(3);
	
	gPad->SetLeftMargin(0.16);
	histrt->Draw();
	
	c4->cd(4);
	
	gPad->SetLeftMargin(0.16);
	histpseurap->Draw();
	
	c2->SaveAs("Sigma0 - polozenia i czas.png");
	c3->SaveAs("Sigma0 - pęd i energia.png");
	c4->SaveAs("Sigma0 - dziwne rzeczy.png");
	
	
	
	return 0;
}

void histogramy()
{
	main();
}