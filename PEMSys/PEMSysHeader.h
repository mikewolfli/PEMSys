/*
PEMSysHeader.h
*/
#if !defined _PEMSYS_HEADER_H_
#define _PEMSYS_HEADER_H_

#define _PEMSYS_REPLACE_MINIFRAME
//#define _PEMSYS_MINIFRAME_CAPTION
#include "./pinoutbar/sizecbar.h"
#include "./pinoutbar/scbarg.h"
#include "./pinoutbar/scbarcf.h"
//#define baseCMyBar CSizingControlBarCF

#include "./pinoutbar/PinDockBar.h"
#include "./pinoutbar/DrawFrame.h"
#include "./pinoutbar/AutoHideBar.h"

#include "./pinoutbar/appface.h"
extern CAppFace g_af ;

#include "gfxgroupedit.h"
#include "gfxoutbarctrl.h"
#include "gfxpopupmenu.h"
#include "./pinoutbar/MyBar.h"

#endif // _PEMSYS_HEADER_H_
