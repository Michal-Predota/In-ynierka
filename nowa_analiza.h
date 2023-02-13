#ifndef nowa_analiza_h     
#define nowa_analiza_h
//
//  Include files
#include "StMaker.h"
#include <string>
#include "StRoot/StMuAnalysisMaker/StMuAnalysisMaker.h"
//
//  Forward declarations
class StMuTrack;
class TFile;
class TH1D;
class TH2D;

#ifndef ST_NO_NAMESPACES
using std::string;
#endif
//
//  The class declaration. It innherits from StMaker.
class NowaAnaliza:public StMuAnalysisMaker
{
public:
	NowaAnaliza(const Char_t *name="muAnalysis");   // constructor
	
    ~NowaAnaliza();      
	
	 virtual const char *GetCVS() const {
      static const char cvs[]="Tag $Name:  $ $Id: StMuAnalysisMaker.h,v 1.2 2014/08/06 11:43:31 jeromel Exp $ built " __DATE__ " " __TIME__ ; 
      return cvs;
    }
	
	Int_t Init() ;
	
	
	Int_t Make() ;
	
	
	Int_t Finish() ;
	
	void Clear(Option_t *option="");
	
private:
	
	int        mEventCounter;  //!
    string     mFileName;      //!
    TFile      *mFile;         //!

	TH1D *momentum;           //!
    TH1D *transversal_momentum;          //!
    TH1D *Phi;               //!
    TH1D *eta;            //!
	TH1D *theta;
	TH2D *dEdx_vs_p;
//	TH2D *rapidity_vs_pT;
	TH2D *mass_squared_vs_p;
	TH2D *one_over_beta_vs_p;
	
	bool accept(StMuTrack*);            // and this is used to select tracks

    ClassDef(NowaAnaliza,0)
	
};
#endif
