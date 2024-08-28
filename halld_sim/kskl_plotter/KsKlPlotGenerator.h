#if !(defined ETAPIPLOTGENERATOR)
#define ETAPIPLOTGENERATOR

#include <vector>
#include <string>

#include "IUAmpTools/PlotGenerator.h"

using namespace std;

class FitResults;
class Kinematics;

class EtaPiPlotGenerator : public PlotGenerator
{
    
public:
  
  // create an index for different histograms
  enum { kEtaPiMass = 0, kEtaPiMass_25MeVBin, kEtaPiMass_10MeVBin, kEtaPiMass_5MeVBin, kEtaPiMass_2MeVBin, kEtaCosTheta, kPhiPi, kPhiEta, kPhi, kphi, kPsi, kt, kNumHists};
  //enum { kEtaPiMass = 0, kEtaPiMass_full_range, kEtaPiMass_20MeVBin, kEtaCosTheta, kPhiPi, kPhiEta, kPhi, kphi, kPsi, kt, kNumHists};
  
  EtaPiPlotGenerator( const FitResults& results );
  EtaPiPlotGenerator( );

  //void projectEvent( Kinematics* kin );
  void projectEvent( Kinematics* kin, const string& reactionName );
  
private:
        
  void createHistograms();
  
};

#endif
