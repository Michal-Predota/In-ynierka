#include <iostream>
#include <vector>
#include <TH1D.h>
#include <TChain.h>
#include <TCanvas.h>
#include <TFile.h>

using namespace std;

int wykres()
{
	
	double title_size=0.09;
	double title_offset=1.25;
	
	gStyle->SetTitleFontSize(title_size);
	
	TFile *f = new TFile("muAnalysis.root");
	TH1D *p = (TH1D*)f->Get("p");
	TH1D *pT = (TH1D*)f->Get("p_{T}");
	TH1D *phi = (TH1D*)f->Get("#Phi");
	TH1D *eta = (TH1D*)f->Get("#eta");
	TH1D *theta = (TH1D*)f->Get("#Theta");
	TH2D *dEdx_vs_p = (TH2D*)f->Get("dEdx vs p");
	
	TCanvas *c1 = new TCanvas("c1", "c1", 1000, 800);
	c1->cd();
	p->SetLineColor(kBlue+1);
	p->SetNameTitle(" p", " p");
	p->SetStats(000);
	gPad->SetLeftMargin(0.17);
	gPad->SetBottomMargin(0.16);
	p->GetXaxis()->CenterTitle(true);
	p->GetYaxis()->CenterTitle(true);
	p->GetYaxis()->SetTitle("#frac{dN}{dp}");
	p->GetYaxis()->SetTitleOffset(title_offset);
	p->GetXaxis()->SetTitle("p [GeV/c]");
	p->GetXaxis()->SetTitleSize(title_size/1.5);
	p->GetYaxis()->SetTitleSize(title_size/1.5);
	p->Draw();
	c1->SaveAs("./Obrazki/p_analysis.png");
	
	TCanvas *c2 = new TCanvas("c2", "c2", 1000, 800);
	c2->cd();
	pT->SetLineColor(kBlue+1);
	pT->SetNameTitle(" p_{T}", " p_{T}");
	pT->SetStats(000);
	gPad->SetLeftMargin(0.17);
	gPad->SetBottomMargin(0.16);
	pT->GetXaxis()->CenterTitle(true);
	pT->GetYaxis()->CenterTitle(true);
	pT->GetYaxis()->SetTitle("#frac{dN}{dp_{T}}");
	pT->GetYaxis()->SetTitleOffset(title_offset);
	pT->GetYaxis()->SetTitleOffset(title_offset);
	pT->GetXaxis()->SetTitle("p_{T} [GeV/c]");
	pT->GetXaxis()->SetTitleSize(title_size/1.5);
	pT->GetYaxis()->SetTitleSize(title_size/1.5);
	//pT->Set
	pT->Draw();
	c2->SaveAs("./Obrazki/pT_analysis.png");
	
	TCanvas *c3 = new TCanvas("c3", "c3", 1000, 800);
	c3->cd();
	phi->SetLineColor(kBlue+1);
	phi->SetNameTitle(" #Phi", " #Phi");
	phi->SetStats(000);
	gPad->SetLeftMargin(0.17);
	gPad->SetBottomMargin(0.16);
	phi->GetXaxis()->CenterTitle(true);
	phi->GetYaxis()->CenterTitle(true);
	phi->GetYaxis()->SetTitle("#frac{dN}{d#Phi}");
	phi->GetYaxis()->SetTitleOffset(title_offset);
	phi->GetXaxis()->SetTitle("#Phi [rad]");
	phi->GetXaxis()->SetTitleSize(title_size/1.5);
	phi->GetYaxis()->SetTitleSize(title_size/1.5);
	phi->Draw();
	c3->SaveAs("./Obrazki/phi_analysis.png");
	
	TCanvas *c4 = new TCanvas("c4", "c4", 1000, 800);
	c4->cd();
	eta->SetLineColor(kBlue+1);
	eta->SetNameTitle(" #eta", " #eta");
	eta->SetStats(000);
	gPad->SetLeftMargin(0.17);
	gPad->SetBottomMargin(0.16);
	eta->GetXaxis()->CenterTitle(true);
	eta->GetYaxis()->CenterTitle(true);
	eta->GetYaxis()->SetTitle("#frac{dN}{d#eta}");
	eta->GetYaxis()->SetTitleOffset(title_offset);
	eta->GetXaxis()->SetTitle("#eta ");
	eta->GetXaxis()->SetTitleSize(title_size/1.5);
	eta->GetYaxis()->SetTitleSize(title_size/1.5);
	eta->Draw();
	c4->SaveAs("./Obrazki/eta_analysis.png");
	
	TCanvas *c5 = new TCanvas("c5", "c5", 1000, 800);
	c5->cd();
	theta->SetLineColor(kBlue+1);
	theta->SetNameTitle(" #Theta", " #Theta");
	theta->SetStats(000);
	gPad->SetLeftMargin(0.17);
	gPad->SetBottomMargin(0.16);
	theta->GetXaxis()->CenterTitle(true);
	theta->GetYaxis()->CenterTitle(true);
	theta->GetYaxis()->SetTitle("#frac{dN}{d#Theta}");
	theta->GetYaxis()->SetTitleOffset(title_offset);
	theta->GetXaxis()->SetTitle("#Theta [rad]");
	theta->GetXaxis()->SetTitleSize(title_size/1.5);
	theta->GetYaxis()->SetTitleSize(title_size/1.5);
	theta->Draw();
	c5->SaveAs("./Obrazki/theta_analysis.png");
	
	TCanvas *c6 = new TCanvas("c6", "c6", 1000, 800);
	c6->cd();
	//dEdx_vs_p->SetLineColor(kBlue+1);
	dEdx_vs_p->SetNameTitle("dE/dx vs p", " dE/dx vs p");
	dEdx_vs_p->SetStats(000);
	gPad->SetLeftMargin(0.17);
	gPad->SetBottomMargin(0.16);
	dEdx_vs_p->GetXaxis()->CenterTitle(true);
	dEdx_vs_p->GetYaxis()->CenterTitle(true);
	dEdx_vs_p->GetYaxis()->SetTitle("dE/dx");
	dEdx_vs_p->GetYaxis()->SetTitleOffset(title_offset);
	dEdx_vs_p->GetXaxis()->SetTitle("p [GeV/c]");
	dEdx_vs_p->GetXaxis()->SetTitleSize(title_size/1.5);
	dEdx_vs_p->GetYaxis()->SetTitleSize(title_size/1.5);
	c6->SetLogz(true);
	dEdx_vs_p->Draw("colz");
	c6->SaveAs("./Obrazki/dEdx_vs_p_analysis_nonmod.png");
	
	return 0;
}