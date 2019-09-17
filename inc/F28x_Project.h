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
  float Angle;                   //!< �ջ����Ƽ���ʹ�õĽǶ�
  float Spd;                     //!< ���ʵ��ת��
  float  Ia;                  //!< ������A�����
  float  Ib;                  //!< ������B�����
  float  Ic;                  //!< ������C�����
  float LocKp;   //!< �ٶȻ�����ϵ��--14
  float LocKi;   //!< �ٶȻ�����ϵ��--15
  float SpdKp;   //!< �ٶȻ�����ϵ��--16
  float SpdKi;   //!< �ٶȻ�����ϵ��--17
  float IKp;     //!< ����������ϵ��--18
  float IKi;   //!< ����������ϵ��----19
  float LocRef;
  float LocReff;
  float LocReff_1;
  float LocFdb;
  float LocUi;                   //!< ת�ٻ��Ļ���
  float LocUp;                   //!< �ٶȻ������
  float SpdFdb;                  //!< �������ٶȻ���ת�ٷ���,Spd��һ����ת��
  float SpdFdbf;
  float SpdFdbf_1;
  float SpdRef;                  //!< ת�ٻ���ָ��
  Uint16 Calcnt;                 //!< ������
  float SpdUi;                   //!< ת�ٻ��Ļ���
  float SpdUp;                   //!< �ٶȻ������
  float IqFdb;                   //!< q���������
  float IqRef;                   //!< q������ĸ���,�����ٶȻ������
  float IqUi;                    //!< q���������
  float IqUp;                    //!< q��������
  float IdFdb;                   //!< d���������
  float IdRef;                   //!< d������ĸ���,�����ٶȻ������
  float IdUi;                    //!< d���������
  float IdUp;                    //!< d��������
  float Uq;                      //!< q���ѹ�ĸ���,���ǵ����������
  float Ud;                      //!< d���ѹ�ĸ���,���ǵ����������
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
Uint16  Err_Idc          : 1;             ///����  0
Uint16  Err_Drv          : 1;             ///�������� 1
Uint16  Err_OverV        : 1;             /// ��ѹ 2
Uint16  Err_Locked       : 1;             ///��ת 3
Uint16  Err_Sta4         : 1;                 //�������  4
Uint16  Err_Feed         : 1;             //��������  5
Uint16  Err_Com          : 1;             //ͨѶ����  6
Uint16  Com_Read         : 1;             //����һ֡��־   7
Uint16  Err_Ia          : 1;             /// 8 Ia����
Uint16  Err_Ib          : 1;             /// 9 Ib����
Uint16  Err_Ic          : 1;             /// 10 Ic����
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
Uint16     RxFlag;      //���ձ�־��Ϊ1���޸ģ��޸ĺ�λ0
Uint16     ZeroFlag;
Uint16     WriteFlag;   //д���־��Ϊ1��д��FLASH��H������ɺ�λ0
Uint16     RxType;        //���ڽ��յ�����
union   Status_REG   Err;
Uint16     Read1;
Uint16     Read2;
int32      RxTmp;
Uint16     RxSum;        // ����ָ����ۼ�
Uint16     RxCnt;        // �Ѿ����ܵ����ֽ���
Uint16     TxType;       //�������ͣ��ɽ��յ�֡����0�ķ���ָ�����
Uint16     TxData[2];    // ���͵����������ֽ�
int16      TxTemp;       //�������ݴ�
Uint16     TxTemp1;       //�������ݴ�
Uint16     TxCnt;        // �Ѿ����͵����ݳ���
Uint16     TxSum;        //�ѷ��͵����ݵļӺͣ�
Uint16     Ver;
Uint16     Buffer[256];   //�洢��������д��flash
}Uart_REG;
extern Uart_REG Uart;

typedef struct
{
  Uint16 Mode;   //����ģʽ
  Uint16 Mode_1;
  Uint16 Run;
  Uint16 Run_1;
  Uint16 Ecatstatus;
  Uint16 Ecatstatus_1;
  Uint16 ModeRead;
  Uint16 ModeRead_1;
  Uint16 Status; //���״̬
  Uint16 Hall;//��ȡ��·�����źţ�ȷ�������ʼλ��
  Uint16 Hall_pos1;
  Uint16 Hall_pos2;
  Uint16 Hall_pos3;
  float  Hall_pos4;
  float  HallAngle;//���ݻ���������ԽǶ�
  float  Code_M;  //������е�Ƕ�
  float  Code_M_1;
  Uint16 Dir;      //����λ�ô���������������λ�÷���
  Uint16 Dir1;     //��������Ƕȷ���
  Uint16 Dir2;     //�����������
  Uint16 Dir3;     //��������
  Uint16 Dir4;     //�ٶȷ�������
  Uint16 Dir5;     //���Ա���������
  Uint16 Tmp_pos1; //�������������
  Uint16 Tmp_pos2;
  Uint16 Tmp_pos3;
  Uint16 Tmp_pos4; //��������Ƕ�
  float  Tmp_pos5;
  float  Tmp_pos6; //���������Ƕ�
  Uint16  Angle_M;   //�ű�������ȡ��е��
  Uint16  Angle_Mf;   //�ű�������ȡ��е��
  Uint16  Angle_M2;   //�ű�������ȡ��е��
  Uint16 Sta3_flag;   //����ģʽ����ƫ���־
  Uint16 Sta4_flag; //״̬4�ҳ�ʼ��ģʽ��־
  Uint32 Sta4_cout; //������
  float  Sta4_angle; //���������Ƕ�
  Uint16 Sta4_onecir; //��ת����һ�ܱ�־
  Uint16 Angle_flag; //�����Ƕ�ѡ���־
  float  Angle_I;    //�����Ƕȣ�0--1
  float  Angle_M_Pre;//�����ڵĻ�е�Ƕȣ�����ת����
  float  Angle_M_Diff;//�ǶȲ�
  float  Angle_H_1; //�����ٶ�ʱ�����Ƕ�
  float  Angle_H_Cnt;//�����ٶ�ʱ������
  float  Spd_Tmp1;    //�����ٶȷ���1���
  float  Spd_Tmp2;    //�����ٶȷ���2���
  Uint32 Spd_Tmp3;
  float  Spd_Time;
  float  SpdFdbf;  //�����ٶ��˲�ֵ
  float  SpdFdbf_1;
  int32  Loc_Dt;    //��һ��indexʱ���������ֵ
  int32  Loc_Tmp1;
  float  Loc_Tmp2;  //�������λ�÷�����е�Ƕȹ�һ��
  float  Loc_Tmp3;  //�������λ�÷�������˹�һ��
  int32  Loc_cycle;  //Ȧ��
  float  Angle_df;  //����ǶȺ;���λ�õ�ƫ���¼
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
  float  Ia;      //<! ���A����� A
  float  Ib;      //<! ���B����� A
  float  Ic;      //<! ���C����� A
  float  Ia_lock;
  float  Ib_lock;
  float  Ic_lock;
  float  Vdc;      //<! ĸ�ߵ�ѹV
  float  PeakI;   //��ֵ��������һ����--9
  float  LimitSpd;  //�ٶ��޷�------10
  float  LimitI;    //�����޷�------11
  float  LockedSpd;  //�����ٶ�-----12
  float  LockedI;    //���ص���-----13
}Bldc_TYPE;
extern Bldc_TYPE Bldc;

typedef struct
{
  Uint16 Ratio;  //������  ---1
  Uint16 Poles;  //������ ---2
  Uint16 Coder;  //����������---3
  Uint16 Dir;    //��������----4
  Uint16 InitAdc1;//���������ֵ--5
  Uint16 InitAdc2;   //--------6
  Uint16  InitAngle; //������ʼ��//--7
  int32  Pos_offset;//�ű������Ƕ�ƫ�ã�����flash��B��--8
  int32  PeakI;   //��ֵ��������һ����--9
  int32  LimitSpd;  //�ٶ��޷�------10
  int32  LimitI;    //�����޷�------11
  int32  LockedSpd;  //�����ٶ�-----12
  int32  LockedI;    //���ص���-----13
  int32 LocKp;   //!< �ٶȻ�����ϵ��--14
  int32 LocKi;   //!< �ٶȻ�����ϵ��--15
  int32 SpdKp;   //!< �ٶȻ�����ϵ��--16
  int32 SpdKi;   //!< �ٶȻ�����ϵ��--17
  int32 IKp;     //!< ����������ϵ��--18
  int32 IKi;   //!< ����������ϵ��----19
  Uint16  InitAngle1; //������ʼ��//--20
  Uint16  Loc_type;  //λ�÷�������ѡ�� ---21
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
