//###########################################################################
//
// FILE:   F28x_Project.h
//
// TITLE:  F28x Project Headerfile and Examples Include File
//
//###########################################################################
// $TI Release: F2837xD Support Library v200 $
// $Release Date: Tue Jun 21 13:00:02 CDT 2016 $
// $Copyright: Copyright (C) 2013-2016 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#ifndef F28X_PROJECT_H
#define F28X_PROJECT_H

//
// Included Files
//
#include "F2837xD_Cla_typedefs.h"  // F2837xD CLA Type definitions
#include "F2837xD_device.h"        // F2837xD Headerfile Include File
#include "F2837xD_Examples.h"      // F2837xD Examples Include File
#include "math.h"
extern Uint16 read;
extern void InitCpu2(void);
extern void InitCtrl(void);
extern void UartRead(void);
extern void UartSend(void);
extern void ReadData(void);
extern void Detection(void);
extern void CallOutMapping(void);
extern void Ethercat_PDO(void);

extern void Foc_Err(void);
extern void Foc_Init(void);
extern void Foc_calc(void);
extern void Loc_pid(void);
extern void Spd_pid(void);
extern void I_pid(void);
extern void InitZero(void);
extern void svgen(void);

extern interrupt void adc1_isr(void);
extern interrupt void sciarx_isr(void);


typedef struct
{
  float Angle;                   //!< 闭环控制计算使用的角度
  float Spd;                     //!< 电机实际转速
  float  Ia;                  //!< 主轴电机A相电流
  float  Ib;                  //!< 主轴电机B相电流
  float  Ic;                  //!< 主轴电机C相电流
  float LocKp;   //!< 速度环比例系数--14
  float LocKi;   //!< 速度环积分系数--15
  float SpdKp;   //!< 速度环比例系数--16
  float SpdKi;   //!< 速度环积分系数--17
  float IKp;     //!< 电流环比例系数--18
  float IKi;   //!< 电流环积分系数----19
  float LocRef;
  float LocReff;
  float LocReff_1;
  float LocFdb;
  float LocUi;                   //!< 转速环的积分
  float LocUp;                   //!< 速度环的误差
  float SpdFdb;                  //!< 主轴电机速度环的转速反馈,Spd归一化的转速
  float SpdFdbf;
  float SpdFdbf_1;
  float SpdRef;                  //!< 转速环的指令
  Uint16 Calcnt;                 //!< 计数器
  float SpdUi;                   //!< 转速环的积分
  float SpdUp;                   //!< 速度环的误差
  float IqFdb;                   //!< q轴电流反馈
  float IqRef;                   //!< q轴电流的给定,又是速度环的输出
  float IqUi;                    //!< q轴电流积分
  float IqUp;                    //!< q轴电流误差
  float IdFdb;                   //!< d轴电流反馈
  float IdRef;                   //!< d轴电流的给定,又是速度环的输出
  float IdUi;                    //!< d轴电流积分
  float IdUp;                    //!< d轴电流误差
  float Uq;                      //!< q轴电压的给定,又是电流环的输出
  float Ud;                      //!< d轴电压的给定,又是电流环的输出
  float Sin;
  float Cos;
  float Alpha;
  float Beta;
  float Ualpha;
  float Ubeta;
  float tmp1;
  float tmp2;
  float tmp3;
  float Ta;
  float Tb;
  float Tc;
  Uint16 temp1;
  Uint16 temp1_1;
  Uint16 VecSector;
}Calc_REG;
extern Calc_REG Calc;

struct Status_Bits
{                               /// bits description
Uint16  Err_Idc          : 1;             ///过流  0
Uint16  Err_Drv          : 1;             ///驱动故障 1
Uint16  Err_OverV        : 1;             /// 过压 2
Uint16  Err_Locked       : 1;             ///堵转 3
Uint16  Err_Sta4         : 1;                 //回零故障  4
Uint16  Err_Feed         : 1;             //反馈故障  5
Uint16  Err_Com          : 1;             //通讯错误  6
Uint16  Com_Read         : 1;             //接收一帧标志   7
Uint16  Err_Ia          : 1;             /// 8 Ia过流
Uint16  Err_Ib          : 1;             /// 9 Ib过流
Uint16  Err_Ic          : 1;             /// 10 Ic过流
Uint16  rsvd1            : 5;             /// 15:11  reserved
};
union Status_REG
{
  Uint16 all;
  struct Status_Bits bit;
};
typedef struct
{
Uint16     En;
Uint16     RxFlag;      //接收标志，为1需修改，修改后复位0
Uint16     ZeroFlag;
Uint16     WriteFlag;   //写入标志，为1需写入FLASH的H区，完成后复位0
Uint16     RxType;        //串口接收的类型
union   Status_REG   Err;
Uint16     Read1;
Uint16     Read2;
int32      RxTmp;
Uint16     RxSum;        // 接受指令的累加
Uint16     RxCnt;        // 已经接受到的字节数
Uint16     TxType;       //发送类型，由接收的帧类型0的反馈指向决定
Uint16     TxData[2];    // 发送的两个数据字节
int16      TxTemp;       //待发送暂存
Uint16     TxTemp1;       //待发送暂存
Uint16     TxCnt;        // 已经发送的数据长度
Uint16     TxSum;        //已发送的数据的加和；
Uint16     Ver;
Uint16     Buffer[256];   //存储参数，待写入flash
}Uart_REG;
extern Uart_REG Uart;

typedef struct
{
  Uint16 Mode;   //运行模式
  Uint16 Mode_1;
  Uint16 Run;
  Uint16 Run_1;
  Uint16 Ecatstatus;
  Uint16 Ecatstatus_1;
  Uint16 ModeRead;
  Uint16 ModeRead_1;
  Uint16 Status; //电机状态
  Uint16 Hall;//读取三路霍尔信号，确定电机初始位置
  Uint16 Hall_pos1;
  Uint16 Hall_pos2;
  Uint16 Hall_pos3;
  float  Hall_pos4;
  float  HallAngle;//根据霍尔计算粗略角度
  float  Code_M;  //增量机械角度
  float  Code_M_1;
  Uint16 Dir;      //增量位置传动方向，增量解算位置反馈
  Uint16 Dir1;     //电机增量角度方向
  Uint16 Dir2;     //电机霍尔方向
  Uint16 Dir3;     //电流方向
  Uint16 Dir4;     //速度反馈方向
  Uint16 Dir5;     //绝对编码器方向
  Uint16 Tmp_pos1; //电机增量计数器
  Uint16 Tmp_pos2;
  Uint16 Tmp_pos3;
  Uint16 Tmp_pos4; //电机增量角度
  float  Tmp_pos5;
  float  Tmp_pos6; //增量电气角度
  Uint16  Angle_M;   //磁编码器读取机械角
  Uint16  Angle_Mf;   //磁编码器读取机械角
  Uint16  Angle_M2;   //磁编码器读取机械角
  Uint16 Sta3_flag;   //回零模式计算偏差标志
  Uint16 Sta4_flag; //状态4找初始角模式标志
  Uint32 Sta4_cout; //计数器
  float  Sta4_angle; //给定电气角度
  Uint16 Sta4_onecir; //旋转电气一周标志
  Uint16 Angle_flag; //电气角度选择标志
  float  Angle_I;    //电气角度，0--1
  float  Angle_M_Pre;//上周期的机械角度，计算转速用
  float  Angle_M_Diff;//角度差
  float  Angle_H_1; //计算速度时霍尔角度
  float  Angle_H_Cnt;//霍尔速度时计数器
  float  Spd_Tmp1;    //计算速度方法1结果
  float  Spd_Tmp2;    //计算速度方法2结果
  Uint32 Spd_Tmp3;
  float  Spd_Time;
  float  SpdFdbf;  //计算速度滤波值
  float  SpdFdbf_1;
  int32  Loc_Dt;    //第一次index时锁存计数器值
  int32  Loc_Tmp1;
  float  Loc_Tmp2;  //计算相对位置反馈机械角度归一化
  float  Loc_Tmp3;  //计算相对位置反馈输出端归一化
  int32  Loc_cycle;  //圈数
  float  Angle_df;  //解算角度和绝对位置的偏差记录
  int16  T1;
  int16  T2;
  int16  T3;
  int16  T4;
  int16  T5;
  Uint16 Cnt_Lock;
  float  IdFdb;
  float  IqFdb;
  float  IdFdb_1;
  float  IdFdbf;
  float  IqFdb_1;
  float  IqFdbf;
  float  Ia;      //<! 电机A相电流 A
  float  Ib;      //<! 电机B相电流 A
  float  Ic;      //<! 电机C相电流 A
  float  Ia_lock;
  float  Ib_lock;
  float  Ic_lock;
  float  Vdc;      //<! 母线电压V
  float  PeakI;   //峰值电流，归一化用--9
  float  LimitSpd;  //速度限幅------10
  float  LimitI;    //电流限幅------11
  float  LockedSpd;  //过载速度-----12
  float  LockedI;    //过载电流-----13
}Bldc_TYPE;
extern Bldc_TYPE Bldc;

typedef struct
{
  Uint16 Ratio;  //传动比  ---1
  Uint16 Poles;  //极对数 ---2
  Uint16 Coder;  //编码器线数---3
  Uint16 Dir;    //传动方向----4
  Uint16 InitAdc1;//零电流采样值--5
  Uint16 InitAdc2;   //--------6
  Uint16  InitAngle; //增量初始角//--7
  int32  Pos_offset;//磁编码器角度偏置，存入flash的B区--8
  int32  PeakI;   //峰值电流，归一化用--9
  int32  LimitSpd;  //速度限幅------10
  int32  LimitI;    //电流限幅------11
  int32  LockedSpd;  //过载速度-----12
  int32  LockedI;    //过载电流-----13
  int32 LocKp;   //!< 速度环比例系数--14
  int32 LocKi;   //!< 速度环积分系数--15
  int32 SpdKp;   //!< 速度环比例系数--16
  int32 SpdKi;   //!< 速度环积分系数--17
  int32 IKp;     //!< 电流环比例系数--18
  int32 IKi;   //!< 电流环积分系数----19
  Uint16  InitAngle1; //霍尔初始角//--20
  Uint16  Loc_type;  //位置反馈类型选择 ---21
}Flash_TYPE;
extern Flash_TYPE Flash;

struct Temp_Bits
{                             /// bits description
Uint16  data1;
Uint16  data2;
};
union Temp_REG
{
  float all;
  struct Temp_Bits data;
};
extern union Temp_REG  Temp;//

typedef struct
{
Uint16  Cnt_Idc;
Uint16  Cnt_Ia;
Uint16  Cnt_Ib;
Uint16  Cnt_Ic;
Uint16  Cnt_Status4;
Uint16  Cnt_Lock;
float   Vdc;
}Safe_REG;
extern Safe_REG Safe;

#endif  // end of F28X_PROJECT_H definition

//
// End of file
//
