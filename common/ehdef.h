#pragma once
#define REG_PNAME	TEXT("\\\\.\\pipe\\Reg")
#define SEL_PNAME	TEXT("\\\\.\\pipe\\Sel")

//ȸ��
#define MAX_ID_LEN		100	//���̵�
#define MAX_PW_LEN		20	//���
#define MAX_NAME_LEN	256	//�̸�
#define MAX_PHONE_LEN	256	//��ȭ��ȣ
#define MAX_BIRTH_LEN	256	//�������
#define MAX_ADDR_LEN	256	//�ּ�
#define MAX_GEN_LEN		100	//����

//��ǰ
#define MAX_PRO_NAME_LEN	256 //��ǰ �̸�
#define MAX_PRO_ID_LEN		256	//��ǰ id(��ȣ)
#define MAX_DATE_LEN		256	//���� ��¥
#define MAX_ICE_HOT 256
//message
#define MAX_MESSAGE_LEN		256

//
#define REG_RES_OK		0
#define REG_RES_NO		-1

#define LOGIN_RES_OK	0  /*����*/
#define LOGIN_RES_ALR	-1 /*�̹� �α� ��*/
#define LOGIN_RES_NOC	-2 /*��� ��ȣ �ٸ�*/
#define LOGIN_RES_NOI	-3 /*���̵� ����*/
#define LOGIN_RES_FA	-4 /*��ư ����*/

//ȸ������
#define REG_REQ		0x0001
#define REG_RES		0x0002
#define UNREG_REQ	0x0003

//�α���
#define LOGIN_REQ	0x0101
#define LOGIN_RES	0x0102
#define LOGOUT_REQ	0x0103

//�Ǹ�
#define SEL_REQ		0x1001
#define SEL_RES		0x1002
