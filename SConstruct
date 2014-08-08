'''
 *  $Id: SConstruct, 2014-08-08 11:17:07 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 24/02/2014
 *---------------------------------------------------
 *      setup install method in this file
 *  1. if you want to install the whole DMPSW, execute
 *      scons
 *      at current directory
 *  2. if you want to re-install some certain packages:
 *      scons package=package_1,package_2,package_3
 *  3. installation layout
 *      prefix/bin
 *      prefix/include
 *      prefix/lib
 *      prefix/share
 *----------------------------------------------------------
'''

import os

# set prefix
#--------------------------------------------------------------------
#prefix='/usr/local'
prefix='NO'
if os.environ.has_key('DMPSWSYS'):
    prefix=os.environ['DMPSWSYS']
prefix=ARGUMENTS.get('prefix',prefix)
if 'NO'==prefix:
    prefix='./Install'
    UsrPrefix=raw_input('Where to install DMPSW (press Enter to use default "%s"):'%prefix)
    if UsrPrefix:   prefix=UsrPrefix
prefix=os.path.abspath(prefix)
print "\n==>Installing DMPSW Framework into:\t%s\n" %prefix


# invoke *.scons file of top-1 packages
#--------------------------------------------------------------------
pkgList='Kernel,Event,Geometry'
#pkgList='Kernel,Event,Geometry,Simulation,RawDataConversion'
#,Analysis,Calibration,Generation,Reconstruction,Visualization'
pkgList=ARGUMENTS.get('package',pkgList)
pkgList=pkgList.split(',')
subScript=[]
for key in pkgList:
    subScript=subScript+[key+'/'+key+'.scons']

SConscript(subScript,exports=['prefix'])


