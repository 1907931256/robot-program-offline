/*
 * scaralib.h
 *
 *  Created on: 2016��11��21��
 *      Author: yin
 */

#ifndef SCARALIB_H_
#define SCARALIB_H_
#include "Eigen/Dense"
using namespace Eigen;
using namespace std;
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <QDebug>
#define ZERO_THRESH 	(0.000001)
#define PI 				M_PI



//==========================================�ؽڽṹ��
typedef struct
{
    float j1; float j2; float j3;
    float j4; float j5; float j6;

	bool ISOK;

	//��ӡ�ؽڽǶȣ���λ�ȣ�3��������λΪmm
    void printJointDegrees(void)
    {
		printf("Joint[%5.2f,%5.2f,%5.2f,%5.2f,%5.2f,%5.2f]\n",
                j1*180.0/PI, j2*180.0/PI, j3,
                j4*180.0/PI, j5*180.0/PI, j6*180.0/PI);
	}

	//��ӡ�ؽڽǶȣ���λ���ȣ�3��������λΪmm
    void printJointRadians(void) const
    {
        qDebug() << j1 << "  " <<  j2 << "  " << j3 << "  " << j4 << "  " << j5 << "  " <<j6;

	}

}Joint;

//==========================================��λ�����ṹ��
typedef struct
{
	float c1; float c2;

	//��ӡ��λ������ת�Ƕȣ���λ��
	void printCointDegrees(void){
        printf("Coint[%5.2f,%5.2f]\n",c1*180.0/PI, c2*180.0/PI);
	}

	//��ӡ��λ������ת�Ƕȣ���λ��
    void printCointRadians(void) const{
		printf("Coint[%5.2f,%5.2f]\n",c1, c2);
	}

}Coint;


typedef struct
{
	Vector3d Pc;		//Բ��
	double R;		//�뾶

	//pu,pvΪԲ����ƽ�����໥��ֱ����������λ����
	Vector3d pu;
	Vector3d pv;

	double alfa;		//��AB��Ӧ��Բ�Ľ�
	double theta;	//��AC��Ӧ��Բ�Ľ�

}Circle;


typedef struct
{
	Matrix4d m;
	Joint j;
	Coint c;
}MJCoint;


extern Coint targetC, currentC;


//���嶨��μ���SCARA������DHģ�͡�
//==========================�ؽڻ�е�ֳߴ綨��
extern float a2, a3, d3, dh;
//==========================��λ�����ߴ綨��
extern float ch_x0, ch_y0, ch_z0, ch_d1, ch_d2;
////��λ�����ϲ��Ե�)
extern float ch_a3, ch_d3;

//==========================�ؽڻ�е�����ƽǶ�
extern float JA_min[6], JA_max[6];

//==========================��λ�������ƽǶ�
extern float CA_min[2], CA_max[2];

//==========================��ǹ�任����
extern Matrix4d TCF;

//==========================ÿ1mm��ɢ�������Ĭ��10�����켣����Ϊ0.1mm
extern float RESOLUTION;
//==========================��̬1����ɢ�������Ĭ��10������̬����Ϊ0.1��
extern float RESOLUTION_ATT;


////==========================�ؽڻ�е�ֳߴ綨��
////���嶨��μ���SCARA������DHģ�͡�
//float a2 = 700.000;
//float a3 = 600.000;
//float d3 = 703.200;
////float dh = 233.924;
//float dh = 160.000;
//
////==========================��λ�����ߴ綨��
////���嶨��μ�����λ����DHģ�͡�
//float ch_x0 =  700.00;		//��λ�����ڷ�
//float ch_y0 = -600.00;		//��λ�����ڷ�
//float ch_z0 =    0.00;
//float ch_d1 =  150.00;
//float ch_d2 =  100.00;		//С��λ����
////��λ�����ϲ��Ե�
//float ch_a3 =  100.00;
//float ch_d3 =   40.00;
//
////==========================�ؽڻ�е�����ƽǶ�
//float JA_min[6] = {-170.0/180*pi, -170.0/180*pi, -500, -170.0/180*pi, -90.0/180*pi, -170.0/180*pi};
//float JA_max[6] = { 170.0/180*pi,  170.0/180*pi,   10,  170.0/180*pi,  90.0/180*pi,  170.0/180*pi};
//
////==========================��λ�������ƽǶ�
//float CA_min[2] = {-60.0/180*pi, -170.0/180*pi};
//float CA_max[2] = { 60.0/180*pi,  170.0/180*pi};



//===========================����ʽ����������㷨
Matrix4d coo_fk(Joint j);
Joint coo_ik(Matrix4d matrix);

//===========================�ؽ�ʽ����������㷨
Matrix4d fk(Joint j);
Joint ik(Matrix4d matrix, bool choose_j2);
Joint NewPositionJoints(Matrix4d matrix);

Matrix4d ch_Ofk(Coint c);
Matrix4d ch_iik(Matrix4d matrix, Coint c);


//λ�˾���ת��Ϊ==>xyz�����ŷ����
ArrayXd pose_2_xyzrpw(Matrix4d H);
//xyz�����ŷ����ת��Ϊ==>λ�˾���
Matrix4d xyzrpw_2_pose(ArrayXd xyzrpw);


//ͨ���궨6���ȡTCF
Matrix4d getTCFMatrix(Matrix4d Moe1, Matrix4d Moe2, Matrix4d Moe3, Matrix4d Moe4, Matrix4d Moe5, Matrix4d Moe6);
//ͨ���궨6���ȡ��λ����
Matrix4d getCHPosAttitude(Matrix4d Moe1, Matrix4d Moe2, Matrix4d Moe3, Matrix4d Moe4, Matrix4d Moe5, Matrix4d Moe6);


Vector3d PositionLinearInterpolation(Vector3d p1, Vector3d p2, double t);
Quaterniond Lerp(Quaterniond qa, Quaterniond qb, double t);
Circle getCircleInfo(Vector3d p1, Vector3d p2, Vector3d p3);
Vector3d Position3DInterpolation(Vector3d p1, Vector3d p2, Vector3d p3, double t);
Quaterniond Slerp(Quaterniond qa, Quaterniond qb, double t);
Quaterniond pose_2_quaternion(Matrix4d m);
Matrix4d quaternion_2_pose(Quaterniond qin);

//��λ��������ϻ�е�ֱ�Բ��ʾ���У����ݻ�AB����AC��ӦԲ�ĽǱ��������л�C1��C2��C3
list<Coint> InterpolationOf3C(Coint C1, Coint C2, Coint C3, double a, double b, int step);
//����A,B����λ�ˣ��õ�AB�����ֱ�ߵ�λ������
list<MJCoint> PositionAttitudeLinearInterpolation(Matrix4d A, Matrix4d B);
//����A,B,C����λ�ˣ��õ�����ABC����Բ����λ������
list<MJCoint> PositionAttitude3DInterpolation(Matrix4d A, Matrix4d B, Matrix4d C);
//����A,B����λ���Լ���A,B���㴦��λ�����Ƕȣ��õ�AB�����ֱ�ߵ�λ�����кͱ�λ������Ӧ�ĽǶ�����
list<MJCoint> RobotAndCHPositionAttitudeLinearInterpolation(Coint C1, Coint C2, Matrix4d A, Matrix4d B);
//����A,B,C����λ���Լ���A,B,C���㴦��λ�����Ƕȣ��õ�����ABC����Բ����λ�����кͱ�λ������Ӧ�ĽǶ�����
list<MJCoint> RobotAndCHPositionAttitude3DInterpolation(Coint C1, Coint C2, Coint C3, Matrix4d A, Matrix4d B, Matrix4d C);
//����A,B,C����λ�ˣ��õ���ABC����ȷ���ı���������λ������
list<MJCoint> PositionAttitudeBezierInterpolation(Matrix4d A, Matrix4d B, Matrix4d C);



#endif /* SCARALIB_H_ */
