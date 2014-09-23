#! /usr/bin/python
'''
 *  $Id: DMPSW.py, 2014-08-08 12:36:50 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
 *-----------------------------------------------------
 *      All jop option files need import this file
 *-----------------------------------------------------
'''

#-------------------------------------------------------------------
# Load basic environment of DAMPE software
import sys
sys.setdlopenflags(0x100|0x2)
import libDmpKernel as DmpKernel

#-------------------------------------------------------------------
# load core
Core = DmpKernel.DmpCore.GetInstance()

#-------------------------------------------------------------------
# get managers
SvcMgr = Core.ServiceManager()
AlgMgr = Core.AlgorithmManager()

#-------------------------------------------------------------------
# environments
SysPath = os.environ["DMPSWSYS"]
WorkPath = os.environ["DMPSWWORK"]

#-------------------------------------------------------------------
# get default service
RootIOSvc = SvcMgr.Get("DmpRootIOSvc")


