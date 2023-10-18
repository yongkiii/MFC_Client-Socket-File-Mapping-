#pragma once
#define REG_PNAME	TEXT("\\\\.\\pipe\\Reg")
#define SEL_PNAME	TEXT("\\\\.\\pipe\\Sel")

//회원
#define MAX_ID_LEN		100	//아이디
#define MAX_PW_LEN		20	//비번
#define MAX_NAME_LEN	256	//이름
#define MAX_PHONE_LEN	256	//전화번호
#define MAX_BIRTH_LEN	256	//생년월일
#define MAX_ADDR_LEN	256	//주소
#define MAX_GEN_LEN		100	//성별

//상품
#define MAX_PRO_NAME_LEN	256 //상품 이름
#define MAX_PRO_ID_LEN		256	//상품 id(번호)
#define MAX_DATE_LEN		256	//구매 날짜
#define MAX_ICE_HOT 256
//message
#define MAX_MESSAGE_LEN		256

//
#define REG_RES_OK		0
#define REG_RES_NO		-1

#define LOGIN_RES_OK	0  /*성공*/
#define LOGIN_RES_ALR	-1 /*이미 로긴 중*/
#define LOGIN_RES_NOC	-2 /*비밀 번호 다름*/
#define LOGIN_RES_NOI	-3 /*아이디 없음*/
#define LOGIN_RES_FA	-4 /*암튼 실패*/

//회원가입
#define REG_REQ		0x0001
#define REG_RES		0x0002
#define UNREG_REQ	0x0003

//로그인
#define LOGIN_REQ	0x0101
#define LOGIN_RES	0x0102
#define LOGOUT_REQ	0x0103

//판매
#define SEL_REQ		0x1001
#define SEL_RES		0x1002
