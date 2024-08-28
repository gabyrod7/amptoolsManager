# About

The main script in this repo is ```amptoolsManager.py```.
It provides a command-line interface (CLI) for doing and plotting SDME and PWA (only two pseudoscalar implemented).

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
* The default was set to  python3 by using the shebang ```#!/bin/python3```.

# Example
The ```amptoolsManager.py``` is the main script but we use the ```example_SDMEfit.py``` script since it is a full fledge example doing an SDME fit.
Make ```example_SDMEfit.py``` executable by running
```
chmod +x example_SDMEfit.py
```
A CLI (command-line interface) is procided by ```example_SDMEfit.py``` check what you can do by running
```
./example_SDMEfit.py -h
```
You will see something like this
```
usage: AmpTools Manager [-h] [-s] [-d] [-S] [-f [FIT [FIT ...]]] [-r] [-D]
                        [-p] [-q] [-b] [-B] [-R]

Run AmpTools fits and plot results. The flags can be provided in any order.
For the initial fit run ./amptoolsManager.py -s -d -S -f -r -D to setup, run
and draw SDMEs.

optional arguments:
  -h, --help            show this help message and exit
  -s, --setupTrees      Take flat trees from DSelector and apply cuts and
                        divide data by polarization angle.
  -d, --divideData      Setup directories and data
  -S, --setupFit        Setup config files for fits
  -f [FIT [FIT ...]], --fit [FIT [FIT ...]]
                        Run fit in (default) all bins of (optional) specific
                        bins
  -r, --readFit         Run readSDMEs()
  -D, --draw            Make plot of SDMEs or PWA mass intensities
  -p, --runPlotter      Run runPlotter()
  -q, --drawAngles      Make plots of angles
  -b, --plotBins        Run plotBins()
  -B, --bootstrap       Run bootstrap
  -R, --rmAmpToolsCfg   Remove amptools.cfg file from all bins
```
If everything is set properly the following line will setup all the data, fit the data and make a plot of the SDMEs.
```
./example_SDMEfit.py -s -d -S -f -r -D
```
