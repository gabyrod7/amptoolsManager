# About

This repo contains several scripts to facilitate running and plotting SDME and PWA fits using the AmpTools framework and the GlueX software stack.
A requisite for these scripts to work is a properly setup GlueX environment, specially ```halld_sim```.
I tried to keep modifications to ```halld_sim``` to a minimum.
There are four changes: (1) ```split_t``` (2) ```getAmpsInBin``` (3) ```phi1020_plotter``` (4) ```kskl_plotter```.
A simple change has made to the ```split_t``` code to save a file called tBins.txt which contains the bin number, bin mean, and bin standard deviation. 
This information is used by the ```drawSDME.C``` script to plot the SDMEs.
```getAmpsInBin``` was written by Lawrence with some minor changes from me and is necessary for plotting the PWA intesities as a function of mass.
The ```phi1020_plotter``` and ```kskl_plotter``` are mainly copy-paste from other plotters.
Remember that if you copy-paste these directories to your ```halld_sim``` (```src/programs/AmplitudeAnalysis/```) then you also need to modify ```SConscript```.

# Notes
* ROOT macros (those ending in .C) are not super general and will often require modifications.
* These are a lot of naiming conventions scattered througout the scripts, be careful changing them.
* Change ```setup_trees.C``` to apply the desired event selectinos. This script applies cuts and divides the data by polarization angle. It is meant as a first pass to flat trees from a DSelector.
* ```example_SDMEfit.py``` is copy of ```amptoolsManager.py``` for doing a PWA fit.
