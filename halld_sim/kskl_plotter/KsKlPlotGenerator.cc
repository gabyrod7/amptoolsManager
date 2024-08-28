#include "TLorentzVector.h"
#include "TLorentzRotation.h"
#include "TLorentzVector.h"
#include "TLorentzRotation.h"

#include "KsKlPlotGenerator.h"
#include "IUAmpTools/Histogram1D.h"
#include "IUAmpTools/Kinematics.h"

EtaPiPlotGenerator::EtaPiPlotGenerator( const FitResults& results ) :
PlotGenerator( results )
{
	createHistograms();
}

EtaPiPlotGenerator::EtaPiPlotGenerator( ) :
PlotGenerator( )
{
	createHistograms();
}

void EtaPiPlotGenerator::createHistograms() {
  // calls to bookHistogram go here
  
  //bookHistogram( kEtaPiMass, new Histogram1D( 65, 0.2, 2.8, "Metapi", "Invariant Mass of #eta #pi") );
  bookHistogram( kEtaPiMass, new Histogram1D( 18, 1.10, 2.00, "Mkskl", "Invariant Mass of K_{S}K_{L}") );
  bookHistogram( kEtaPiMass_25MeVBin, new Histogram1D( 36, 1.10, 2.00, "Mkskl_25MeV", "Invariant Mass of K_{S}K_{L}") );
  bookHistogram( kEtaPiMass_10MeVBin, new Histogram1D( 100, 1.00, 2.00, "Mkskl_10MeV", "Invariant Mass of K_{S}K_{L}") );
  bookHistogram( kEtaPiMass_5MeVBin, new Histogram1D( 200, 1.00, 2.00, "Mkskl_5MeV", "Invariant Mass of K_{S}K_{L}") );
  bookHistogram( kEtaPiMass_2MeVBin, new Histogram1D( 50, 1.00, 1.10, "Mkskl_2MeV", "Invariant Mass of K_{S}K_{L}") );
  bookHistogram( kEtaCosTheta, new Histogram1D( 25, -1., 1., "cosTheta", "cos( #theta ) of Resonance Production") );

  bookHistogram( kPhiPi,  new Histogram1D( 25, -3.14, 3.14, "PhiPi",  "#Phi_{K_{L}}" ) );
  bookHistogram( kPhiEta, new Histogram1D( 25, -3.14, 3.14, "PhiPiKs", "#Phi_{K_{S}}" ) );
  bookHistogram( kPhi, new Histogram1D( 25, -3.14, 3.14, "Phi", "#Phi" ) );
  bookHistogram( kphi, new Histogram1D( 25, -3.14, 3.14, "phi", "#phi" ) );
  bookHistogram( kPsi, new Histogram1D( 25, -3.14, 3.14, "psi", "#psi" ) );
  bookHistogram( kt, new Histogram1D( 100, 0, 1.0, "t", "-t" ) );
  //bookHistogram( kPhiPi,  new Histogram1D( 50, -1*PI, PI, "PhiPi",  "#Phi_{K_{L}}" ) );
  //bookHistogram( kPhiEta, new Histogram1D( 50, -1*PI, PI, "PhiPiKs", "#Phi_{K_{S}}" ) );
  //bookHistogram( kPhi, new Histogram1D( 50, -1*PI, PI, "Phi", "#Phi" ) );
  //bookHistogram( kphi, new Histogram1D( 50, -1*PI, PI, "phi", "#phi" ) );
  //bookHistogram( kPsi, new Histogram1D( 50, -1*PI, PI, "psi", "#psi" ) );
  //bookHistogram( kt, new Histogram1D( 100, 0, 1.0, "t", "-t" ) );
}

void
EtaPiPlotGenerator::projectEvent( Kinematics* kin, const string& reactionName ){
  //cout << cfgInfo()->amplitudeList( reactionName, "", "").at(0)->factors().at(0).at(5) << endl;
  double polAngle=stod(cfgInfo()->amplitudeList( reactionName, "", "").at(0)->factors().at(0).at(5));

  // Our reaction has the order 14 7 17 when using tree_to_amptools. so its proton pi0 eta 
  TLorentzVector beam   = kin->particle( 0 );
  TLorentzVector recoil = kin->particle( 1 );
  TLorentzVector p1 = kin->particle( 2 );
  TLorentzVector p2 = kin->particle( 3 );
  TLorentzVector target(0,0,0,0.9382719);
  TLorentzVector resonance = p1 + p2; 

  /// ************************************************
  // This should be calculating the angles in the helictiy frame
  /// ************************************************
  //TLorentzRotation resonanceBoost( -resonance.BoostVector() );
  //TLorentzVector recoil_res = resonanceBoost * recoil;
  //TLorentzVector p1_res = resonanceBoost * p1;
  //TLorentzVector p2_res = resonanceBoost * p2;
  //// normal to the production plane
  //TVector3 y = (beam.Vect().Unit().Cross(-recoil.Vect().Unit())).Unit();
  ////// z-axis opposite recoil proton in rho rest frame
  //TVector3 z = -1. * recoil_res.Vect().Unit();
  //TVector3 x = y.Cross(z).Unit();
  
  /// ************************************************
  // This should be calculating the angles in the GJ frame
  /// ************************************************
  TLorentzVector cm=beam+target;
  TLorentzRotation cmBoost( -cm.BoostVector() );
  TLorentzVector beam_cm=cmBoost*beam;
  TLorentzVector recoil_cm=cmBoost*recoil;
  TLorentzVector pi0_cm=cmBoost*p1;
  TLorentzVector eta_cm=cmBoost*p2;
  TLorentzVector resonance_cm=pi0_cm+eta_cm;

  TLorentzRotation resonanceBoost( -resonance_cm.BoostVector() );
  TLorentzVector beam_res = resonanceBoost*beam_cm;
  TLorentzVector recoil_res = resonanceBoost*recoil_cm;
  TLorentzVector eta_res = resonanceBoost*eta_cm;
  TLorentzVector pi0_res = resonanceBoost*pi0_cm;

   
  /////////////////////
  // MY OLD CODE 
  //TVector3 z = beam_res.Vect().Unit();
  //// this y should be the normal of the production plane. If we do a boost in a direction in the production plane the perp direction doesn't change. We could use the beam and the recoiled proton to define the
  //// production plane in this new frame. Let us define it in the CM frame. 
  //TVector3 y = resonance_cm.Vect().Cross(beam_cm.Vect()).Unit();
  //////////////////////
  /////////////////////
  // NEW CODE TAKEN FROM ZLM.CC
  TVector3 z = -1. * recoil_res.Vect().Unit();
  // or GJ frame?
  // TVector3 z = beam_res.Vect().Unit();
  // normal to the production plane
  TVector3 y = (beam.Vect().Unit().Cross(-recoil.Vect().Unit())).Unit();
  /////////////////////
  TVector3 x = y.Cross(z).Unit();
  TVector3 angles(   (eta_res.Vect()).Dot(x),
                     (eta_res.Vect()).Dot(y),
                     (eta_res.Vect()).Dot(z) );
  GDouble cosTheta = angles.CosTheta();
  
  GDouble phi = angles.Phi();
  
  TVector3 eps(TMath::Cos(polAngle*0.01745), TMath::Sin(polAngle*0.01745), 0.0); // beam polarization vector
  GDouble Phi = atan2(y.Dot(eps), beam.Vect().Unit().Dot(eps.Cross(y)));

  GDouble psi = phi - Phi;
  if(psi < -1*PI) psi += 2*PI;
  if(psi > PI) psi -= 2*PI;

  // compute invariant t
  GDouble t = - 2* recoil.M() * (recoil.E()-recoil.M());

  // calls to fillHistogram go here
  fillHistogram( kEtaPiMass, ( resonance ).M() );
  fillHistogram( kEtaPiMass_25MeVBin, ( resonance ).M() );
  fillHistogram( kEtaPiMass_10MeVBin, ( resonance ).M() );
  fillHistogram( kEtaPiMass_5MeVBin, ( resonance ).M() );
  fillHistogram( kEtaPiMass_2MeVBin, ( resonance ).M() );
//  fillHistogram( kEtaPiMass_full_range, ( resonance ).M() );
//  fillHistogram( kEtaPiMass_20MeVBin, ( resonance ).M() );
  fillHistogram( kEtaCosTheta, cosTheta );
  fillHistogram( kPhiPi,  p1.Phi() );
  fillHistogram( kPhiEta, p2.Phi() );
  fillHistogram( kPhi, Phi );
  fillHistogram( kphi, phi );
  fillHistogram( kPsi, psi );
  fillHistogram( kt, -t );      // fill with -t to make positive
}
