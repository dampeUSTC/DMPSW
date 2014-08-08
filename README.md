DMPSW
=====

##  Requirement

    1.  scons

    2.  root

    3.  boost

    4.  python-devel 

    5.  geant4

##  Installation

    1.  create dictionary of event classes, do:
        ./pre-install.(c)sh

    2.  install DMPSW, do:

        scons [options]

        options list:
            * prefix
                scons prefix=./Install
                    install into ./Install
            * package
                scons package=Kernel,Event
                    only install package Kernel and Event

    3.  source prefix/bin/thisdmpsw.(c)sh


##  NOTE

    More details information about:

    1.  How to setup environment of DMPSW?
        refer to TODO

    2.  How to use DMPSW?
        refer to TODO

    3.  Name convention of DMPSW
        refer to TODO

##  Name convention

1.  use detector names below ANY WHERE (except: data files are all lower case)

        Psd
        Stk
        Bgo
        Nud

2.  Abbreviation of Package

        Calibration:        Cal
        Reconstruction:     Rec
        RawDataConversion:  Rdc
        Simulatin:          Sim
        Visulization:       Vis
        Event:              Evt
        Analysis:           Ana
        Generation:         Gen
        Geometry:           Gem

3.  prefix

        * class name (DmpCore)
            begin with "Dmp"

        * struct name (_FeeDataBuf)
            begin with "_"

        * namespace for enum type
            begin with "DmpE"

        * typedef of a map (typedef std::map<short,_FeeDataBuf> M_FeeDataBuf)
            begin with "M_"

        * typedef of a vector
            begin with "V_"

        * Prefix of any command (dmpNewAlg)
            begin with "dmp"

        * a shared library of DMPSW (libDmpKernel)
            begin with "libDmp"

        * data members (DmpCore::fEventID)
            begin with "f"

4.  file name

    4.1  Readme.md

    4.2  coding file

        *.h    header file, all must in directory "include"
        *.cc    source file, all must in directory "src"
            The main function for create a command in /path/src/Dmp{AP}Main.cc

    4.3  FileName.scons

        compilation files which will be used by build tool "SCons".

    4.4  JobOpt_* file

        running time script. For example: JobOpt_DmpSimulation is used to run simulation

    4.5  FileName.cnct

        dectector <-> FEE, connection information.

