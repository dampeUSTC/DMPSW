/*
 *  $Id: DmpKernelLinkDef.h, 2014-11-01 00:13:35 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 29/10/2014
*/

#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link off all namespaces;

#pragma link C++ namespace DmpTimeConvertor;
#pragma link C++ class DmpAlgorithmManager;
#pragma link C++ class DmpServiceManager;
#pragma link C++ class DmpCore;
#pragma link C++ class DmpRootIOSvc;
#pragma link C++ class DmpDataBuffer;
#pragma link C++ global gCore;
#pragma link C++ global gDataBuffer;
#pragma link C++ global gRootIOSvc;

#endif
