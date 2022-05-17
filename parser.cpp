#include <iostream>
#include <fstream>
#include <ostream>
#include <vector>
#include <string>
#include <typeinfo>
#include "funkcje.cpp"
#include <TCanvas.h>
#include <TH1.h>
#include <TMath.h>
#include <algorithm>
#include <TGraph.h>

using namespace std;

bool sortcol( const vector<double>& v1,
               const vector<double>& v2 ) {
    return v1[1] < v2[1];
}

int main()
{
	ifstream inFile;
	inFile.open("test.f19");
	
	if (!inFile) {
    cerr << "Unable to open file datafile.txt"<<endl;
    exit(1);   // call system to stop
	}
	
	vector<double> particle_counter;
	vector<double> ID;
	vector<double> p_x;
	vector<double> p_y;
	vector<double> p_z;
	vector<double> Energia;
	vector<double> masa;
	vector<double> r_x;
	vector<double> r_y;
	vector<double> r_z;
	vector<double> czas;
	
	vector<int> liczba_sczytan;
	
	
	double n1, n2, n3, n4, n5, n6, n7, n8, n9, n10, n11;
	
	GotoLine(inFile, 4);
	
	int liczba_danych;
	int liczba_przejsc = 1;
	int current_line = 4;
	int a;
	string line;

	for(int j = 0; j < 1000; j++)
		{
		//GotoLine(inFile, current_line);
		inFile>>a>>liczba_danych;
		std::getline(inFile, line);
		//GotoLine(inFile, current_line+1);
		liczba_sczytan.push_back(liczba_danych);
		
		for(int i = 0; i<liczba_danych; i++)
		{
			
			inFile>>n1>>n2>>n3>>n4>>n5>>n6>>n7>>n8>>n9>>n10>>n11;
			particle_counter.push_back(n1);
			ID.push_back(n2);	
			p_x.push_back(n3);
			p_y.push_back(n4);
			p_z.push_back(n5);
			Energia.push_back(n6);
			masa.push_back(n7);
			r_x.push_back(n8);
			r_y.push_back(n9);
			r_z.push_back(n10);
			czas.push_back(n11);
		}
		
		current_line+=(liczba_danych+1);
		
		liczba_przejsc++;
		}
		
		//if(inFile.eof())
		//{
		//	break;
		//}
	
	vector<vector<double>> do_hist;
	vector<vector<double>> tmp = ilosc_wystapien(ID);
	std::sort(tmp.begin(), tmp.end(),sortcol);
	reverse(tmp.begin(),tmp.end());
	
	for(int i =0; i<10; i++)
	{
		do_hist.push_back(tmp.at(i));
	}
	 
	
	TCanvas *c1 = new TCanvas("c1", "canvas1", 1000, 1000);
	

	c1->SetGrid();
	c1->SetBottomMargin(0.15);
	
	int rozmiar = do_hist.size();
	
	TH1D* h1 = new TH1D("h1", "yields", rozmiar, -150, 150);
	
	h1->SetMarkerStyle(20);
	
	/**********************************************************************************krotności***********************************************************************************/
	
	/*
	c1->SetLogy();
	
	for(int i = 1; i<rozmiar+1; i++)
	{
		h1->SetBinContent(i, do_hist.at(i-1).at(1));
		//h1->SetBinError(i, TMath::Sqrt(do_hist.at(i-1).at(1)));
	}
	
	h1->Sumw2(1);	
	
	cout<<h1->GetBinError(1)<<endl;
	
	h1->SetStats(0000);
	
	vector<string> nazwy = {"p", "n", "#pi^{0}", "#pi^{+}", "#pi^{-}", "#Sigma^{0}", "K^{0}", "#Sigma^{+}", "K^{+}", "#lambda"};
	
	for (int i=1; i<=rozmiar; i++) h1->GetXaxis()->SetBinLabel(i, nazwy.at(i-1).c_str());
	
	
	h1->SetLabelSize(0.045);
	
	
	h1->Draw();
	c1->SaveAs("krotność cząstek.png");*/
	
	
	/******************************************************************stosunki cząstka - antycząstka*******************************************************************************/
	
	/*
	c1->SetLogy();
	
	vector<double> stosunki;
	vector<double> stosunki_err;


	double pion_pion = wybierz_czastke(tmp, 211).at(0).at(1)/wybierz_czastke(tmp, -211).at(0).at(1);
	double Kaon0_Kaon0 = wybierz_czastke(tmp, 311).at(0).at(1)/wybierz_czastke(tmp, -311).at(0).at(1);
	double Kaonp_Kaonm = wybierz_czastke(tmp, 321).at(0).at(1)/wybierz_czastke(tmp, -321).at(0).at(1);
	
	stosunki.push_back(pion_pion);
	stosunki.push_back(Kaon0_Kaon0);	
	stosunki.push_back(Kaonp_Kaonm);
	
	double pion_pion_err = TMath::Sqrt(wybierz_czastke(tmp, 211).at(0).at(1)/TMath::Power(wybierz_czastke(tmp, -211).at(0).at(1), 2)+TMath::Power(wybierz_czastke(tmp, 211).at(0).at(1), 2)/TMath::Power(wybierz_czastke(tmp, -211).at(0).at(1), 3));	
	double Kaon0_Kaon0_err = TMath::Sqrt(wybierz_czastke(tmp, 311).at(0).at(1)/TMath::Power(wybierz_czastke(tmp, -311).at(0).at(1), 2)+TMath::Power(wybierz_czastke(tmp, 311).at(0).at(1), 2)/TMath::Power(wybierz_czastke(tmp, -311).at(0).at(1), 3));	
	double Kaonp_Kaonm_err = TMath::Sqrt(wybierz_czastke(tmp, 321).at(0).at(1)/TMath::Power(wybierz_czastke(tmp, -321).at(0).at(1), 2)+TMath::Power(wybierz_czastke(tmp, 321).at(0).at(1), 2)/TMath::Power(wybierz_czastke(tmp, -321).at(0).at(1), 3));	
	
	stosunki_err.push_back(pion_pion_err);
	stosunki_err.push_back(Kaon0_Kaon0_err);
	stosunki_err.push_back(Kaonp_Kaonm_err);
	
	
	int ile_stosunkow = stosunki.size();
	
	TH1D* h2 = new TH1D("h2", "stosunki czastka/anty czastka", ile_stosunkow, 0, 4);
	
	h2->SetStats(0000);
	
	h2->SetMarkerStyle(20);
	
	for(int i = 1; i<ile_stosunkow+1; i++)
	{
		h2->SetBinContent(i, stosunki.at(i-1));
		h2->SetBinError(i, stosunki_err.at(i-1));
	}
	
	const char *nazwy_os[4]  = {"#pi^{+}/#pi^{-}", "kaon 0/anty kaon 0", "Kaon+/Kaon-"};
	
	for (int i=1;i<=ile_stosunkow;i++) h2->GetXaxis()->SetBinLabel(i, nazwy_os[i-1]);
	
	h2->Draw();*/
	
	//c1->SaveAs("Stosunki cząstka anty cząstka.png");
	
	/******************************************************************Histogramy pędów/położeń/czasów...*******************************************************************************/
	
	/**********************************************************************Czterowektor położeń i czasu********************************************************************************/
	
	//Należy rysować jeden czterowektor na raz, nieużywany należy zakomentować
	
	/*vector<double> g1 = wybierz_dane(ID, r_x, 311);
	vector<double> g2 = wybierz_dane(ID, r_y, 311);
	vector<double> g3 = wybierz_dane(ID, r_z, 311);
	vector<double> g4 = wybierz_dane(ID, czas, 311);
	
	double max1 = *max_element(std::begin(g1), std::end(g1));
	double min1 = *min_element(std::begin(g1), std::end(g1));
	
	double max2 = *max_element(std::begin(g2), std::end(g2));
	double min2 = *min_element(std::begin(g2), std::end(g2));
	
	double max3 = *max_element(std::begin(g3), std::end(g3));
	double min3 = *min_element(std::begin(g3), std::end(g3));	
	
	double max4 = *max_element(std::begin(g4), std::end(g4));
	double min4 = *min_element(std::begin(g4), std::end(g4));	
	
	TH1D *h13 = new TH1D("r_x ", "", 100, -10, 10);
	h13->SetStats(0000);
	h13->GetXaxis()->SetTitle("x [fm]");
	h13->GetYaxis()->SetTitle("#frac{N}{x}");
	h13->GetXaxis()->CenterTitle(true);
	h13->GetYaxis()->CenterTitle(true);
	h13->SetTitleSize(0.04);
	h13->SetStats(0000);
	h13->SetMarkerStyle(20);
	h13->SetMarkerSize(0.7);
	h13->Sumw2();
	
	TH1D *h23 = new TH1D("r_y ", "", 100, -10, 10);
	h23->GetXaxis()->SetTitle("y [fm]");
	h23->GetYaxis()->SetTitle("#frac{N}{y}");
	h23->GetXaxis()->CenterTitle(true);
	h23->GetYaxis()->CenterTitle(true);
	h23->SetTitleSize(0.04);
	h23->SetStats(0000);
	h23->SetMarkerStyle(20);
	h23->SetMarkerSize(0.7);
	h23->Sumw2();
	
	TH1D *h33 = new TH1D("r_z ", "", 100, -10, 10);
	h33->GetXaxis()->SetTitle("z [fm]");
	h33->GetYaxis()->SetTitle("#frac{N}{z}");
	h33->GetXaxis()->CenterTitle(true);
	h33->GetYaxis()->CenterTitle(true);
	h33->SetTitleSize(0.04);
	h33->SetStats(0000);
	h33->SetMarkerStyle(20);
	h33->SetMarkerSize(0.7);
	h33->Sumw2();
	
	TH1D *h43 = new TH1D("t ", "", 100, 0, 30);
	h43->GetXaxis()->SetTitle("t [#frac{fm}{c}]");
	h43->GetYaxis()->SetTitle("#frac{N}{t}");
	h43->GetXaxis()->CenterTitle(true);
	h43->GetYaxis()->CenterTitle(true);
	h43->SetTitleSize(0.04);
	h43->SetStats(0000);
	h43->SetMarkerStyle(20);
	h43->SetMarkerSize(0.7);
	h43->Sumw2();
	
	for(int i = 0; i<g1.size(); i++)
	{
		h13->Fill(g1.at(i));
		h23->Fill(g2.at(i));
		h33->Fill(g3.at(i));
		h43->Fill(g4.at(i));
	}
	
	c1->Divide(2, 2);
	
	c1->cd(1);
	
	gPad->SetRightMargin(0.001);
	gPad->SetLeftMargin(0.15);
	h13->Draw();
	
	c1->cd(2);
	
	gPad->SetLeftMargin(0.15);
	h23->Draw();
	
	c1->cd(3);
	
	gPad->SetLeftMargin(0.15);
	h33->Draw();
	
	c1->cd(4);
	
	gPad->SetLeftMargin(0.15);
	h43->Draw();

	c1->SaveAs("Kaon0 położenia i czas.png");*/
	
	/**********************************************************************Czterowektor pędów i Energii********************************************************************************/
	/*
	vector<double> g1 = wybierz_dane(ID, p_x, 311);
	vector<double> g2 = wybierz_dane(ID, p_y, 311);
	vector<double> g3 = wybierz_dane(ID, p_z, 311);
	vector<double> g4 = wybierz_dane(ID, Energia, 311);
	
	double max1 = *max_element(std::begin(g1), std::end(g1));
	double min1 = *min_element(std::begin(g1), std::end(g1));
	
	double max2 = *max_element(std::begin(g2), std::end(g2));
	double min2 = *min_element(std::begin(g2), std::end(g2));
	
	double max3 = *max_element(std::begin(g3), std::end(g3));
	double min3 = *min_element(std::begin(g3), std::end(g3));	
	
	double max4 = *max_element(std::begin(g4), std::end(g4));
	double min4 = *min_element(std::begin(g4), std::end(g4));
	
	TH1D *h13 = new TH1D("p_x", "", 100, (int)min1, (int)max1);
	h13->GetXaxis()->SetTitle("p_{x} [#frac{GeV}{c}]");
	h13->GetYaxis()->SetTitle("#frac{N}{p_{x}}");
	h13->GetXaxis()->CenterTitle(true);
	h13->GetYaxis()->CenterTitle(true);
	h13->SetTitleSize(0.04);
	h13->SetStats(0000);
	h13->SetMarkerStyle(20);
	h13->SetMarkerSize(0.7);
	h13->Sumw2();
	
	TH1D *h23 = new TH1D("p_y ", "", 100, (int)min2, (int)max2);
	h23->GetXaxis()->SetTitle("p_{y} [#frac{GeV}{c}]");
	h23->GetYaxis()->SetTitle("#frac{N}{p_{y}}");
	h23->GetXaxis()->CenterTitle(true);
	h23->GetYaxis()->CenterTitle(true);
	h23->SetTitleSize(0.04);
	h23->SetStats(0000);
	h23->SetMarkerStyle(20);
	h23->SetMarkerSize(0.7);
	h23->Sumw2();
	
	TH1D *h33 = new TH1D("p_z ", "", 100, (int)min3, (int)max3);
	h33->GetXaxis()->SetTitle("p_{z} [#frac{GeV}{c}]");
	h33->GetYaxis()->SetTitle("#frac{N}{p_{z}}");
	h33->GetXaxis()->CenterTitle(true);
	h33->GetYaxis()->CenterTitle(true);
	h33->SetTitleSize(0.04);
	h33->SetStats(0000);
	h33->SetMarkerStyle(20);
	h33->SetMarkerSize(0.7);
	h33->Sumw2();
	
	TH1D *h43 = new TH1D("E ", "", 100, 0.5,(int)max4);
	h43->GetXaxis()->SetTitle("E [GeV]");
	h43->GetYaxis()->SetTitle("#frac{N}{E}");
	h43->GetXaxis()->CenterTitle(true);
	h43->GetYaxis()->CenterTitle(true);
	h43->SetTitleSize(0.04);
	h43->SetStats(0000);
	h43->SetMarkerStyle(20);
	h43->SetMarkerSize(0.7);
	h43->Sumw2();
	
	
	for(int i = 0; i<g1.size(); i++)
	{
		h13->Fill(g1.at(i));
		h23->Fill(g2.at(i));
		h33->Fill(g3.at(i));
		h43->Fill(g4.at(i));
	}
	
	c1->Divide(2, 2);
	
	c1->cd(1);
	
	gPad->SetRightMargin(0.001);
	gPad->SetLeftMargin(0.15);
	h13->Draw();
	
	c1->cd(2);
	
	gPad->SetLeftMargin(0.15);
	h23->Draw();
	
	c1->cd(3);
	
	gPad->SetLeftMargin(0.15);
	h33->Draw();
	
	c1->cd(4);
	
	gPad->SetLeftMargin(0.15);
	h43->Draw();

	c1->SaveAs("Kaon0 Pędy i energia.png");*/
	
/**********************************************************************************************Różne obliczenia******************************************************************************/
	int obecne_id = 311;

	/********************transversal momentum****************************/
	vector<double> p1 = wybierz_dane(ID, p_x, obecne_id);
	vector<double> p2 = wybierz_dane(ID, p_y, obecne_id);
	
	c1->Divide(2, 2);
	c1->cd(1);
	
	vector<double> p_T;
	
	for(int i = 0; i<p1.size(); i++)
	{
		p_T.push_back(TMath::Sqrt(TMath::Power(p1.at(i), 2)+TMath::Power(p2.at(i), 2)));
	}
	
	double max1 = *max_element(std::begin(p_T), std::end(p_T));
	double min1 = *min_element(std::begin(p_T), std::end(p_T));
	
	TH1D *hist1 = new TH1D("p_T", "", 100, min1, 1);
	
	/*for(int i = 1; i<p1.size()+1; i++)
	{
		hist1->SetBinError(i, TMath::Sqrt(TMath::Power(p1.at(i-1)*TMath::Sqrt(p1.at(i-1))/(TMath::Sqrt(TMath::Power(p1.at(i-1), 2)+TMath::Power(p2.at(i-1), 2))), 2)));
	}*/
	
	hist1->GetXaxis()->SetTitle("p_{T} [GeV/c]");
	hist1->GetYaxis()->SetTitle("#frac{N}{p_{T}}");
	hist1->GetXaxis()->CenterTitle(true);
	hist1->GetYaxis()->CenterTitle(true);
	hist1->SetTitleSize(0.04);
	hist1->SetStats(0000);
	hist1->SetMarkerStyle(20);
	hist1->SetMarkerSize(0.7);
	hist1->Sumw2();
	
	for(int i = 0; i<p_T.size(); i++)
	{
		hist1->Fill(p_T.at(i));
	}
	gPad->SetRightMargin(0.001);
	gPad->SetLeftMargin(0.15);
	
	hist1->Draw();
	 
	
	//c1->SaveAs("proton - p_T.png");
	
	
	/********************rapidity****************************/
	
	c1->cd(2);
	
	vector<double> E = wybierz_dane(ID, Energia, obecne_id);
	vector<double> p3 = wybierz_dane(ID, p_z, obecne_id);
	
	vector<double> rapidity;
	
	for(int i = 0; i<p3.size(); i++)
	{
		rapidity.push_back(0.5*TMath::Log((E.at(i)+p3.at(i))/(E.at(i)-p3.at(i))));
	}
	
	double max2 = *max_element(std::begin(rapidity), std::end(rapidity));
	double min2 = *min_element(std::begin(rapidity), std::end(rapidity));
	
	TH1D *hist2 = new TH1D("rapidity", "", 100, min2, max2);
	
	hist2->GetXaxis()->SetTitle("y");
	hist2->GetYaxis()->SetTitle("#frac{N}{y}");
	hist2->GetXaxis()->CenterTitle(true);
	hist2->GetYaxis()->CenterTitle(true);
	hist2->SetTitleSize(0.04);
	hist2->SetStats(0000);
	hist2->SetMarkerStyle(20);
	hist2->SetMarkerSize(0.7);
	hist2->Sumw2();
	
	for(int i = 0; i<rapidity.size(); i++)
	{
		hist2->Fill(rapidity.at(i));
	}
	gPad->SetLeftMargin(0.15);
	
	hist2->Draw();
	
	//c1->SaveAs("rapidity - Kaon 0.png");
	
	/***************************transversal coordinate*******************************/
	vector<double> r1 = wybierz_dane(ID, r_x, obecne_id);
	vector<double> r2 = wybierz_dane(ID, r_y, obecne_id);
	
	c1->cd(3);
	
	vector<double> r_T;
	
	for(int i = 0; i<r1.size(); i++)
	{
		r_T.push_back(TMath::Sqrt(TMath::Power(r1.at(i), 2)+TMath::Power(r2.at(i), 2)));
	}
	
	double max3 = *max_element(std::begin(r_T), std::end(r_T));
	double min3 = *min_element(std::begin(r_T), std::end(r_T));
	
	TH1D *hist3 = new TH1D("r_T", "", 100, min3, 20);
	
	hist3->GetXaxis()->SetTitle("r_{T} [fm]");
	hist3->GetYaxis()->SetTitle("#frac{N}{r_{T}}");
	hist3->GetXaxis()->CenterTitle(true);
	hist3->GetYaxis()->CenterTitle(true);
	hist3->SetTitleSize(0.04);
	hist3->SetStats(0000);
	hist3->SetMarkerStyle(20);
	hist3->SetMarkerSize(0.7);
	hist3->Sumw2();
	
	for(int i = 0; i<r_T.size(); i++)
	{
		hist3->Fill(r_T.at(i));
	}
	gPad->SetLeftMargin(0.15);
	
	hist3->Draw();
	
	//c1->SaveAs("Transversal coordinate - Kaon 0.png");
	
	
	/**********************************pseudorapidity********************************/
	
	c1->cd(4);
	
	vector<double> pseudorapidity;
	
	for(int i = 0; i<p1.size(); i++)
	{
		pseudorapidity.push_back(0.5*TMath::Log((E.at(i)+p1.at(i))/(E.at(i)-p1.at(i))));
	}
	
	double max4 = *max_element(std::begin(pseudorapidity), std::end(pseudorapidity));
	double min4 = *min_element(std::begin(pseudorapidity), std::end(pseudorapidity));
	
	TH1D *hist4 = new TH1D("pseudorapidity", "", 100, min4, max4);
	
	hist4->GetXaxis()->SetTitle("#eta");
	hist4->GetYaxis()->SetTitle("#frac{N}{#eta}");
	hist4->GetXaxis()->CenterTitle(true);
	hist4->GetYaxis()->CenterTitle(true);
	hist4->SetTitleSize(0.04);
	hist4->SetStats(0000);
	hist4->SetMarkerStyle(20);
	hist4->SetMarkerSize(0.7);
	hist4->Sumw2();
	
	for(int i = 0; i<E.size(); i++)
	{
		hist4->Fill(pseudorapidity.at(i));
	}
	gPad->SetLeftMargin(0.15);
	
	hist4->Draw();
	
	c1->SaveAs("Kaon0 - dziwne rzeczy.png");
	
	inFile.close();
	return 0;
}

void parser(){
	main();
}