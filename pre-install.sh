#! /bin/bash
:<<EOF
 *  $Id: pre-install.sh, 2014-10-29 23:46:58 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 26/12/2013
 *---------------------------------------------------
 *  Description:
 *      1. check basic environment
 *      2. create all dictionaries
 *---------------------------------------------------
EOF


#+ functions
#----------------------------------------------------
CheckEnv(){
  for var in $@;do
    if [[ `env | grep $var | wc -l` -lt 1 ]];then
      echo "    ERROR:  no shell variable \$$var"
      exit 1
    fi
  done
}

echo "---->   Checking Environment..."
CheckEnv ROOTSYS G4INSTALL G4LIB_USE_GDML

#----------------------------------------------------

for dir in {"Kernel","BaseLib","Event"}
do
  pushd $dir 1>/dev/null
  /bin/rm -f ./*/Dictionary* >&/dev/null
  #echo "---->   Creating Dictionary of $dir ..."
  ./createDictionary
  popd  1>/dev/null
done


