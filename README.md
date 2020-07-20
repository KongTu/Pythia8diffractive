# Pythia8diffractive

Pythia 8 documentation can be found here, 
http://home.thep.lu.se/~torbjorn/pdfdoc/pythia8200.pdf.
One can find general introduction of Pythia program and what processes are implemented. For diffraction, one can look at 2.3 Soft processes. 

Soft QCD processes are documented here where one can specify process other than the default. 
http://home.thep.lu.se/~torbjorn/pythia81html/QCDProcesses.html

For more general diffraction processes/parameters, here is the link, 
http://home.thep.lu.se/~torbjorn/pythia82html/Welcome.html. 

# How to get started

- The example code in this documentation is 
"generatePPdiffractive.cpp"

- For installation of Pythia 8 please see the general installation guide, http://home.thep.lu.se/Pythia/. The latest version is 8.3. 

- After successful installation, check out this github under the main directory of pythia program, .../pythia83xx/, by

	git clone https://github.com/KongTu/Pythia8diffractive.git

- go to Pythia8diffractive and do:

	g++  -std=c++11 -m64 generatePPdiffractive.cpp -o generatePPdiffractive -I../include -O2  -pedantic -W -Wall -Wshadow -fPIC -L../lib -Wl,-rpath,../lib -lpythia8 -ldl `root-config --cflags --glibs`

- to run it, 

	./generatePPdiffractive