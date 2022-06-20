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


int korelacja(void)
{
	TCanvas *c1 = new TCanvas("c1", "canvas1", 800, 800);

	TFile *f = new TFile("outfilecf43p0	.root");

	TH1D * h1 = new TH1D("h1","korelacja #pi^{+}-#pi^{+}" , 100, 0, 1);
	h1 = (TH1D*)f->Get("cnumn1da");

	TH1D * h2 = new TH1D("h2","h2" , 100, 0, 1);

	h2 = (TH1D*)f->Get("cdenn1da");	

	
	h1->Divide(h2);
	
	h1->SetTitle("korelacja #pi^{+}-#pi^{+}" );
	
	h1->SetStats(000);
	
	gPad->SetLeftMargin(0.14);
	
	h1->GetXaxis()->SetTitle("k^{*} [GeV/c]");
	h1->GetYaxis()->SetTitle("C (k^{*})");
	h1->GetXaxis()->CenterTitle(true);
	h1->GetYaxis()->CenterTitle(true);
	h1->GetXaxis()->SetTitleOffset(1.3);

	
	//h3->GetYaxis()->SetRangeUser(0.8,2);
	//h3->GetXaxis()->SetRangeUser(0,0.3);
	
	h1->Draw();
	
	c1->SaveAs("Korelacja pi+pi+ case 43 - urqmd.png");

	return 0;
}