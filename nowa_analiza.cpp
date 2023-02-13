#include "nowa_analiza.h"
#include<iostream>

#include "StMuDSTMaker/COMMON/StMuTrack.h"
#include "StMuDSTMaker/COMMON/StMuDst.h"
#include "StMuDSTMaker/COMMON/StMuDebug.h"

#include <TH2D.h>

using namespace std;

void muEventInfo(StMuEvent&, const int&);

ClassImp(NowaAnaliza)

// The constructor. Initialize data members here.
NowaAnaliza::NowaAnaliza(const Char_t *name): StMuAnalysisMaker(name)
{ mEventCounter = 0; mFile = 0; }

NowaAnaliza::~NowaAnaliza() { /* noop */ }

Int_t NowaAnaliza::Init() 
	{
		//  Output file and histogram booking
		mFileName = "muAnalysis.root";
	
		momentum = new TH1D("p","p",100,0.,3.);
		transversal_momentum = new TH1D("p_{T}","p_{T}",100,0.,3.);
		Phi = new TH1D("#Phi","#Phi",100,-3.5,3.5);
		eta = new TH1D("#eta","#eta",100,-2.2,2.2);
		theta = new TH1D("#Theta","#Theta",100,0.,3.);
		dEdx_vs_p = new TH2D("dEdx vs p", "dEdx vs p", 400, 0, 5, 400, -0, 2*TMath::Power(10, -5));
		mass_squared_vs_p = new TH2D("m^{2} vs p", "m^{2} vs p", 100, 0, 10, 100, -50, 2);
		one_over_beta_vs_p = new TH2D("1/#beta vs p", "1/#beta vs p", 100, 0, 10, 100, -0.1, 0.0001);
	//	rapidity_vs_pT = new TH2D("rapidity vs pT", "rapidity vs pT", 100, -10, 10, 100, -10, 10);
		
		
    
		return StMaker::Init();
	}
	
void NowaAnaliza::Clear(Option_t *opt)
	{
		StMaker::Clear();
	}	
	
Int_t NowaAnaliza::Make() 
	{
		mEventCounter++;  // increase counter

		DEBUGVALUE2(mEventCounter);
//  	Get MuDst
		StMuDst* mu; 
		mu =  (StMuDst*) GetInputDS("MuDst"); 
		DEBUGVALUE2(mu);

		if (!mu){
			gMessMgr->Warning() << "NowaAnaliza::Make : No MuDst" << endm;
				return kStOK;        // if no event, we're done
	}
// 	
// 	 Check track branches
		StMuTrack* muTrack; 
		int nTracks;
		nTracks= mu->primaryTracks()->GetEntries();
		printf("Global track # = %d\n",nTracks);
		for (int l=0; l<nTracks; l++) { 
			muTrack =  (StMuTrack*) mu->primaryTracks(l); 
			if(muTrack) if (accept(muTrack)) momentum->Fill(muTrack->momentum().mag());
		}
		
		nTracks= mu->primaryTracks()->GetEntries();
		printf("Primary track # = %d\n",nTracks);
		
		for (int l=0; l<nTracks; l++) { 
			muTrack =  (StMuTrack*) mu->primaryTracks(l); 
			if(muTrack) if (accept(muTrack)) transversal_momentum->Fill(muTrack->pt());
		}
		
		nTracks= mu->primaryTracks()->GetEntries();
		printf("L3 track # = %d\n",nTracks);
		
		for (int l=0; l<nTracks; l++) { 
			muTrack =  (StMuTrack*) mu->primaryTracks(l); 
			if(muTrack) if (accept(muTrack)) Phi->Fill(muTrack->phi());
		}
		
		nTracks= mu->primaryTracks()->GetEntries();
		printf("L3 track # = %d\n",nTracks);
		
		for (int l=0; l<nTracks; l++) { 
			muTrack =  (StMuTrack*) mu->primaryTracks(l); 
			if(muTrack) if (accept(muTrack)) eta->Fill(muTrack->eta());
		}
		
		
		nTracks= mu->primaryTracks()->GetEntries();
		printf("Primary track # = %d\n",nTracks);
		
		for (int l=0; l<nTracks; l++) { 
			muTrack =  (StMuTrack*) mu->primaryTracks(l); 
			if(muTrack) if (accept(muTrack)) dEdx_vs_p->Fill( muTrack->momentum().mag(), muTrack->dEdx());
		}
		
		nTracks= mu->primaryTracks()->GetEntries();
		printf("Primary track # = %d\n",nTracks);
		
		for (int l=0; l<nTracks; l++) { 
			muTrack =  (StMuTrack*) mu->primaryTracks(l); 
			if(muTrack) if (accept(muTrack)) mass_squared_vs_p->Fill(muTrack->momentum().mag(), muTrack->momentum().mag()*muTrack->momentum().mag()*(1/(muTrack->btofPidTraits().beta()*muTrack->btofPidTraits().beta())-1));
		}
		
		for (int l=0; l<nTracks; l++) { 
			muTrack =  (StMuTrack*) mu->primaryTracks(l); 
			if(muTrack) if (accept(muTrack)) theta->Fill(2*TMath::ATan(TMath::Exp(-muTrack->eta())));
		}
		
		for (int l=0; l<nTracks; l++) { 
			muTrack =  (StMuTrack*) mu->primaryTracks(l); 
			if(muTrack) if (accept(muTrack)) one_over_beta_vs_p->Fill(muTrack->momentum().mag(), 1/muTrack->btofPidTraits().beta());
		}
		
		nTracks= mu->primaryTracks()->GetEntries();
		printf("Primary track # = %d\n",nTracks);
		
		
		
//	
//	  Printout information of StMuEvent 
//		if(muEvent)  muEventInfo(*muEvent, mEventCounter);  //zakomentowane z powodu bledu z wskaźnikiem "error: no match for 'operator*' (operand type is 'muDstTypes')"
	
		return kStOK;
		
	}
	
	
	Int_t NowaAnaliza::Finish() 
	{
// 	 	Summarize the run.
		cout << "NowaAnaliza::Finish()\n";
		cout << "\tProcessed " << mEventCounter << " events." << endl;
//
// 	 Output histograms
		mFile =  new TFile(mFileName.c_str(), "RECREATE");
		cout << "\tHistograms will be stored in file '"
			<<  mFileName.c_str() << "'" << endl;
	
		momentum->Write();
		transversal_momentum->Write();
		Phi->Write();
		eta->Write();
		dEdx_vs_p->Write();
		//mass_squared_vs_p->Write();
		theta->Write();
		//one_over_beta_vs_p->Write();
//
// 	 Write histos to file and close it.
		if( mFile){
			mFile->Write();  
			mFile->Close();
		}

		return kStOK;
	}

bool NowaAnaliza::accept(StMuTrack* track)
{
//  check for positive flags.
    return track && track->flag() >= 0;
}
