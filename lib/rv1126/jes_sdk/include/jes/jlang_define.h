/***********************************************************************
 * @file jlang_define.h
 * @author Lucky(lukai@jovision.com)
 * @brief  header file
 * @version 0.1
 * @date 2022-12-03
 *
 * @copyright @ Jovision Technology Co.,Ltd. 2022-. All rights reserved
***********************************************************************/
#ifndef __JLANG_DEFINE_H__
#define __JLANG_DEFINE_H__

#include <locale.h>
#include <libintl.h>
#ifndef _
#define _(str) gettext(str)
#endif

#endif // __JLANG_DEFINE_H__
