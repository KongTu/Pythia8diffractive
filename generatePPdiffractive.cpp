// main36.cc is a part of the PYTHIA event generator.
// Copyright (C) 2017 Torbjorn Sjostrand.
// PYTHIA is licenced under the GNU GPL version 2, see COPYING for details.
// Please respect the MCnet Guidelines, see GUIDELINES for details.

#include <iostream>
#include <vector>
#include <sstream>
#include <string>

#include "TParticlePDG.h"
#include "TString.h"
#include "TF1.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TMath.h"
#include "TTree.h"
#include "TChain.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TMultiGraph.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TLine.h"
#include "TAxis.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TLorentzVector.h"
#include "TLorentzRotation.h"

#include "Pythia8/Pythia.h"
using namespace Pythia8;
using namespace std;

TH1D* eta_gen = new TH1D("eta_gen",";#eta",200,-10,10);
TH1D* pt_gen = new TH1D("pt_gen",";p_{T} (GeV/c)",200,0,20);

int main() {
    
    // Generator. Process selection. RHIC initialization. Histogram.
    Pythia pythia;
    Event& event = pythia.event;
    pythia.readString("Beams:eCM = 500.");
    pythia.readString("SoftQCD:all = off");
    pythia.readString("HardQCD:all = off");
    pythia.readString("SoftQCD:nonDiffractive = off");
    pythia.readString("SoftQCD:doubleDiffractive = on");
    pythia.readString("SoftQCD:inelastic = off");
    pythia.readString("Tune:pp = 14");

    pythia.init();
 
    // Initialize.
    pythia.init();

    TH1D* Nch_gen_eta[7];
    for(int j=0;j<7;j++){
        Nch_gen_eta[j] = new TH1D(Form("Nch_gen_eta_%d",j),";N",200,0,200);
    }

    int nEvent = 100000;
    // Begin event loop.
    for (int iEvent = 0; iEvent < nEvent; ++iEvent) {
    if (!pythia.next()) continue;

    int nParticles_eta[7]={0,0,0,0,0,0,0};

    // Loop over final particles in the event.
    for (int i = 0; i < event.size(); ++i) if (event[i].isFinal() && event[i].isHadron() && event[i].isCharged() ) {

        double eta = event[i].eta();//change to y for a moment
        double pt = event[i].pT();

        pt_gen->Fill( pt );
        eta_gen->Fill( eta );

        if( pt > 0. && fabs(eta) < 1.0 ){
            nParticles_eta[2]++;
        }
        if( pt > 0. && eta < -2.5 && eta > -5.0 ) nParticles_eta[0]++;
        if( pt > 0. && eta > 2.5 && eta < 5.0 ) nParticles_eta[1]++;
        if( pt > 0. && fabs(eta) > 2.5 && fabs(eta) < 5.0 ) nParticles_eta[3]++;

    }// End of particle loop. 

        if( nParticles_eta[2] > 0 ){
            Nch_gen_eta[2]->Fill( nParticles_eta[2] );
            Nch_gen_eta[0]->Fill( nParticles_eta[0] );
            Nch_gen_eta[1]->Fill( nParticles_eta[1] );
        }
        else{
            Nch_gen_eta[3]->Fill( nParticles_eta[0] );
            Nch_gen_eta[4]->Fill( nParticles_eta[1] );
            Nch_gen_eta[5]->Fill( nParticles_eta[3] );
        }
     
    // End of event loop. Statistics and histograms.
    }

    //pythia.stat();    
    TFile f1("pp_Pythia8_multiplicity_diffractive.root","RECREATE");

    pt_gen->Write();
    eta_gen->Write();

    for(int j = 0; j < 7; j++){
        Nch_gen_eta[j]->Write();
    }

    // Done.
    return 0;
}
