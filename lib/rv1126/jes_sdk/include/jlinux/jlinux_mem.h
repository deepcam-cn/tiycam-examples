/***********************************************************************
 * @file jlinux_mem.h
     JLINUX_MEM
 * @brief   header file
 * @history
 * Date       Version Author    description
 * ========== ======= ========= =======================================
 * 2022-07-28 V1.0    Lucky,lukai@jovision.com   Create
 *
 * @Copyright (C)  2022  Jovision Technology Co., Ltd.
***********************************************************************/
#ifndef __JLINUX_MEM_H__
#define __JLINUX_MEM_H__

#ifdef __cplusplus
extern "C"
{
#endif

void * jmem_map(unsigned int phy_addr, unsigned int size);
int jmem_unmap(void * addr_mapped);

#ifdef __cplusplus
}
#endif
#endif // __JLINUX_MEM_H__
