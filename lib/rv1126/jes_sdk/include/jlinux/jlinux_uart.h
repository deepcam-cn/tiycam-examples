/***********************************************************************
 * @file jlinux_uart.h
     JLINUX_UART
 * @brief   header file
 * @history
 * Date       Version Author    description
 * ========== ======= ========= =======================================
 * 2022-07-27 V1.0    Lucky,lukai@jovision.com   Create
 *
 * @Copyright (C)  2022  Jovision Technology Co., Ltd.
***********************************************************************/
#ifndef __JLINUX_UART_H__
#define __JLINUX_UART_H__

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct _uart_ctx *juart_hdl_t;

typedef struct
{
	int baudrate;   //波特率:1200/2400/4800/9600/19200/38400/57600/115200/230400/380400/460800/921600
	int datawidth;  //数据位宽度:5/6/7/8
	int stopbit;    //停止位宽度:1/2
	int parity;		//奇偶校验:0无校验，1奇校验，2偶校验
}JUartAttr_t;

/**
 *@brief 打开串口设备设备，如果是485设备请配合jctrl_rs485相关接口使用
 *@param name 设备名称，如：/dev/ttyS0
 *@return 句柄
 */
juart_hdl_t juart_open(const char *name);

/**
 *@brief 关闭串口
 *@param handle 句柄
 */
int juart_close(juart_hdl_t handle);

/**
 *@brief 配置串口属性
 *@param handle 句柄
 *@param attr 属性
 */
int juart_set_attr(juart_hdl_t handle, JUartAttr_t *attr);

/**
 *@brief 通过串口发送数据
 *@param handle 句柄
 *@param data 数据buffer
 *@param len 数据长度
 *@return 0成功
 */
int juart_send(juart_hdl_t handle, char *data, int len);

/**
 *@brief 通过串口接受数据
 *@param handle 句柄
 *@param data 数据buffer
 *@param len buffer的长度
 *@return 收到数据的长度
 */
int juart_recv(juart_hdl_t handle, char *data, int len);

/**
 *@brief 接收串口数据扩展接口，从收到start开始接收，到收到stop返回
 *@param handle 句柄
 *@param data 接收数据缓存
 *@param len 缓存大小
 *@param start 数据头标志：前nstart个字节
 *@param nstart 数据头字节数
 *@param stop 数据截止标志：后nstop个字节
 *@param nstop 数据截止标志的字节数
 */
int juart_recv_ex(juart_hdl_t handle, char *data, int len, char *start, int nstart, char *stop, int nstop);


#ifdef __cplusplus
}
#endif
#endif // __JLINUX_UART_H__
