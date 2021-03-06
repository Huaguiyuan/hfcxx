/**************************************************************************
 *   molecule.cpp  --  This file is part of HFCXX.                        *
 *                                                                        *
 *   Copyright (C) 2012, Ivo Filot                                        *
 *                                                                        *
 *   HFCXX is free software:                                              *
 *   you can redistribute it and/or modify it under the terms of the      *
 *   GNU General Public License as published by the Free Software         *
 *   Foundation, either version 3 of the License, or (at your option)     *
 *   any later version.                                                   *
 *                                                                        *
 *   HFCXX is distributed in the hope that it will be useful,             *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty          *
 *   of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.              *
 *   See the GNU General Public License for more details.                 *
 *                                                                        *
 *   You should have received a copy of the GNU General Public License    *
 *   along with this program.  If not, see http://www.gnu.org/licenses/.  *
 *                                                                        *
 **************************************************************************/

#include "molecule.h"

/* default constructor */
Molecule::Molecule() {
    nrat = 0;
}

void Molecule::addAtom(const Atom &at) {
    atoms.push_back(at);
    nrat++;
}

void Molecule::addAtom(const std::string symbolin, const double xx, const double yy, const double zz) {
    Atom at(symbolin, xx, yy, zz, basis);
    atoms.push_back(at);
    nrat++;
}

void Molecule::addAtom(const unsigned int Zz, const double xx, const double yy, const double zz) {
    Atom at(Zz, xx, yy, zz, basis);
    atoms.push_back(at);
    nrat++;
}

std::ostream & operator << (std::ostream &os, const Molecule &rhs) {
    for(unsigned int i=0; i<rhs.atoms.size();i++) {
        os << "(" << i+1 << ")\t" << rhs.atoms[i] << std::endl;
    }

    return os;
}

const unsigned int Molecule::nratoms() const{
    return nrat;
}

const Atom& Molecule::operator[](const unsigned int i) const {
  return atoms[i];
}

void Molecule::read(std::string file) {
    InputFile fp(file);
    std::vector<std::string> lines;
    std::vector<std::string> pieces;
    fp.readFile(lines);
    std::string line, dat, units;
    unsigned int pos, nrat;
    double un;

    /* grab basisset from first line 1 */
    line = strtrim(lines[0]);
    pos = strpos(line,"=");
    dat = substr(line,pos+1);
    basisset = strtrim(dat);
    basis.setType(basisset);
    //std::cout << basisset << std::endl;

    /* grab charge from line 2 */
    line = strtrim(lines[1]);
    pos = strpos(line,"=");
    dat = substr(line,pos+1);
    charge = atoi(strtrim(dat).c_str() );
    //std::cout << charge << std::endl;

    /* grab number of atoms from line 3 */
    line = strtrim(lines[2]);
    pos = strpos(line,"=");
    dat = substr(line,pos+1);
    nrat = atoi(strtrim(dat).c_str() );
    //std::cout << nrat << std::endl;

    /* grab length unit from first line 4 */
    line = strtrim(lines[3]);
    pos = strpos(line,"=");
    dat = substr(line,pos+1);
    units = strtrim(dat);
    if(units.compare("bohr")==0) {
        un = 1;
    }
    if(units.compare("angstrom")==0) {
        un = 1.0 / 0.52917721092;
    }
    //std::cout << units << std::endl;

    double x, y, z;
    std::string element;
    for(unsigned int i=0; i<nrat; i++) {
        line = strtrim(lines[4+i]);
        pieces = explode(" ",line);
        element = strtrim(pieces[0]);
        x = atof(pieces[1].c_str() ) * un;
        y = atof(pieces[2].c_str() ) * un;
        z = atof(pieces[3].c_str() ) * un;
        addAtom(element, x, y, z);
    }
}
