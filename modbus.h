/*======================================================================================*
 * �ļ���   ��modbus.h
 * ����     ��
 * ����     ��2019��6��27��16:36:10
 * ����     ��trzhongty@163.com

 * �޸ļ�¼ :
 *--------------------------------------------------------------------------------------
 * �汾		����										����								�޸�����
 * V0.01  2019��6��27��16:38:07   trzhongty@163.com   1) ���δ��� 
 * v0.02	2019��7��2��01:31:50		trzhongty@163.com		1) ��TxPort��RxPort�������޸ģ�����
																											��ʱ��������һ�������˴ӻ���ʱ����
 *=====================================================================================*/

#ifndef __MODBUS_H__
#define __MODBUS_H__
#if defined(__cplusplus)
extern "C" {
#endif

/*======================================== �ļ����� =====================================*/
#include <string.h>

/*======================================== ��ֲ��� =====================================*/
//#include "main.h"
#include "freertos.h"
#include "semphr.h"
#include "task.h"

#define MODBUS_SLAVETASK_STACK_SIZE			512u		//�ӻ���������ջ��С
#define MODBUS_SLAVETASK_PRIORITY_NUM		3u			//�������ȼ�
//#define MODBUS_SLAVETASK_BUFF_SIZE			512u

////��������ϣ���Ҫ�ظ���Ӧʱ�ӿ�
//void __wifi_funreply( uint8_t * pdata, uint8_t num );
//#define ModBus_HAL_ReplyData( _replyData_, _replyLen_)		__wifi_funreply( _replyData_, _replyLen_)
////�����ݰ��޷�����������ݸ�ʽ�����⣬��Ҫ����ʱ�ص�
//#define ModBus_HAL_PackDump()								do{__wifi_packclear(); hwififun.state |= WIFI_FUN_STATE_ENDING_DONE;}while(0)							
//#define ModBus_HAL_FunParseStart()							FunWork_ModBus_FunParseStart()

/*======================================== �궨��  ======================================*/
#define MODBUS_DIS_VALUE_ON			((uint16_t)(0xFF00u))
#define MODBUS_DIS_VALUE_OFF		((uint16_t)(0x0000u))

#define MODBUS_RTU_PACKLEN_MIN					8u	 	//RTU����8�ֽ�
#define MODBUS_RTU_REPLY_PACKLEN_MIN		6u		//RTU��Ӧ�ֽ�����6u
#define MODBUS_RTU_PACKLEN_READ_SIZE		8u		//RTU ��ȡָ�ȫ��Ϊ8�ֽ�
#define MODBUS_RTU_PACKLEN_WRITE_SIZE		8u		//RTU д����ָ�ȫ��Ϊ8�ֽ�
#define MODBUS_RTU_REPLY_PACKLEN_ERRORACK_SIZE		5u

#define MODBUS_PACK_VERSION_DEF		((uint16_t)(0x0000u))		//��2��3���ֽ�Э��汾��
#define MODBUS_PACK_VERSION_DEF_H	( (uint8_t)(MODBUS_PACK_VERSION_DEF >> 8u) )
#define MODBUS_PACK_VERSION_DEF_L	( (uint8_t)(MODBUS_PACK_VERSION_DEF) )


#define MODBUS_PACKLEN_MIN		8u		//7���ֽ��ף���1���ֽڹ�����Ϊ���Ҫ�󣬵�С��12�ֽ�
#define MODBUS_FUN_READ_REMAINDERLEN_DEF		6u	//��ȡ�࣬Ĭ��6���ֽ�ʣ�೤��
#define MODBUS_FUN_WRITE_REMAINDERLEN_DEF		6u	//����д���࣬Ĭ��6���ֽ�ʣ�೤��

#define MODBUS_PACK_NUM_PACKID_H			0u
#define MODBUS_PACK_NUM_PACKID_L			1u
#define MODBUS_PACK_NUM_VERSION_H		2u
#define MODBUS_PACK_NUM_VERSION_L		3u
#define MODBUS_PACK_NUM_REMAINDERLEN_H	4u
#define MODBUS_PACK_NUM_REMAINDERLEN_L	5u
#define MODBUS_PACK_NUM_SLAVEID			6u
#define MODBUS_PACK_NUM_FUNCODE			7u


#define MODBUS_DIS_DATA_ON_DEF			((uint16_t)0xFF00u)		//��Ҫת�����ܺʹ��˳��һ��
#define MODBUS_DIS_DATA_OFF_DEF			((uint16_t)0x0000u)

/*======================================== ���Ͷ���  ====================================*/

//֧�ֵĹ�����ö��
typedef enum
{
	MODBUS_FUN_READ_DISOUT 				= 0x01u,
	MODBUS_FUN_READ_DISIN 				= 0x02u,
	MODBUS_FUN_READ_HOLD 					= 0x03u,
	MODBUS_FUN_READ_INPUT 				= 0x04u,
	MODBUS_FUN_WRITE_DISOUT 			= 0x05u,
	MODBUS_FUN_WRITE_HOLD 				= 0x06u,
	MODBUS_FUN_WRITE_DISOUT_MORE 	= 0x0Fu,
	MODBUS_FUN_WRITE_HOLD_MORE		= 0X10u,
	
	MODBUS_EXFUN_REPORT_DISOUT_MORE		= 0x45u,	//�����ϱ���ɢ�������ɢ���롢���ּĴ���������Ĵ���
	MODBUS_EXFUN_REPORT_DISIN_MORE		= 0x42u,
	MODBUS_EXFUN_REPORT_HOLD_MORE			= 0x46u,
	MODBUS_EXFUN_REPORT_INPUT_MORE		= 0x44u
}ModBus_Fun_enum;

//��������Ӧ�����б�
typedef enum
{
	MODBUS_REACK_ERROR_NULL			= 0x00u,	//�޴���
	MODBUS_REACK_ERROR_FUN			= 0x01u,
	MODBUS_REACK_ERROR_REG			= 0x02u,
	MODBUS_REACK_ERROR_DATA			= 0x03u,
	MODBUS_REACK_ERROR_DAMAGE		= 0x04u,
	MODBUS_REACK_ERROR_ACK			= 0x05u,
	MODBUS_REACK_ERROR_BUSY			= 0x06u,
	MODBUS_REACK_ERROR_NO				= 0x07u,
	MODBUS_REACK_ERROR_PARITY		= 0x08u
}ModBus_ErrorAck_enum;

//״̬ö��
typedef enum
{
	ModBus_STATE_NULL	= 0,
	ModBus_STATE_READY	= 1,
	ModBus_STATE_BUSY	= 2,
}ModBus_state_enum;

//ͨѶ��ʽ����ö��
typedef enum
{
	ModBus_TYPE_RTU 	= 0,
	ModBus_TYPE_ASCII = 1,
	ModBus_TYPE_TCP 	= 2,
}ModBus_Type_enum;

//���ݵ�����
typedef enum
{
	MODBUS_DATA_TPYE_NULL		= 0,	//δ֪����
	MODBUS_DATA_TPYE_DISOUT = 1,
	MODBUS_DATA_TPYE_DISIN 	= 2,
	MODBUS_DATA_TPYE_HOLD 	= 3,
	MODBUS_DATA_TPYE_INPUT 	= 4,
}ModBus_DataType_enum;

//�洢����֮�������
typedef struct
{
	uint16_t	*pValue;			//���ڵ���д��������洢��ֵ��Ϣ
	uint16_t	tcpId;				//���ݰ���ǰ�����ֽ�,ͨѶ���
	uint16_t	remainderLen;	//���ݰ�ʣ���ֽ���
	uint16_t	regAddrStart;	//���������Ϊ�Ĵ�����д�࣬�򽫼Ĵ�����ʼ��ַ��Ÿô�
	uint16_t	regLen;				//���������Ϊ�Ĵ�����д�࣬�򽫶�д������Ÿô�
	uint8_t		byteLen;			//���ڶ�д��������洢����ֵռ���ֽ���
	uint8_t		slaveId;			//���ݰ��ӻ��豸��ʶ���ӻ���ַ
	uint8_t		funCode;			//������
	ModBus_DataType_enum	dataType;		//���ݵ�����
	ModBus_ErrorAck_enum	errorCode;	//�쳣����
}ModBus_Parse_TypeDef;

//����ͨѶModbus�ṹ�壬
typedef struct
{
	uint8_t	*	packData;				//ָ����Դ����֡
	TickType_t	getTimeTick;	//��ȡ����ʱ��
	uint16_t	packLen;				//��Ӧ���ܳ���
	ModBus_Parse_TypeDef 		parse;
}ModBus_Msg_TypeDef;

//���ݵ��дģʽ
typedef enum
{
	MODBUS_DATA_MODE_ALL 			= 0,	//���⣬ֻҪ�ж��ķ�Χ�ڼ���
	MODBUS_DATA_MODE_STRICT 	= 1,	//�ϸ�ģʽ�������Ƕ����޶�����ʼ�Ĵ������䳤��
	MODBUS_DATA_MODE_CONTAIN 	= 2,	//����Ҫָ��Ĵ�����Χ���ڶ��ķ�Χ
}ModBus_DataMode_enum;

//���ݵ㶩������
typedef struct ModBus_TopicLink_struct
{
	struct ModBus_TopicLink_struct *pPext;
	ModBus_ErrorAck_enum (*pWriteFun)(	const struct ModBus_TopicLink_struct *pTopicLink,
																			uint16_t	 *pValue,
																			uint16_t 		regAddrStart,
																			uint16_t 		regLen );
	ModBus_ErrorAck_enum (*pReadFun)(		const struct ModBus_TopicLink_struct *pTopicLink,
																			uint16_t	 *pValue,
																			uint16_t 		regAddrStart,
																			uint16_t 		regLen );
	uint16_t 		regAddrStart;
	uint16_t 		regLen;
	uint8_t			slaveId;
	ModBus_DataType_enum	dataType;
	ModBus_DataMode_enum	dataMode;
}ModBus_TopicLink_TypeDef;

//���ݵ�д�����ȡ����ָ�붨��
//pValue��Modbus���亯�������ռ䣬������ɢ�ͣ��䱾��Ϊuint8_t*������uint16_t���ͣ����亯�������Զ����д�С��ת��
//��ɢд��Ͷ�ȡ��pValueָ���ֵӦ��Ϊ 0xff00���� 0x0000��
typedef ModBus_ErrorAck_enum ( *ModBus_TopicWriteFun)( 	const struct ModBus_TopicLink_struct *pTopicLink,
																												uint16_t	*pValue,
																												uint16_t 		regAddrStart,
																												uint16_t 		regLen );
																			
typedef ModBus_ErrorAck_enum ( *ModBus_TopicReadFun)( const struct ModBus_TopicLink_struct *pTopicLink,
																											uint16_t	 *pValue,
																											uint16_t 		regAddrStart,
																											uint16_t 		regLen );

//Ӳ���ӿڲ㣬ʵ�ֻ�Ӧ����
typedef int(*ModBus_TxPort_TypeDef)(uint8_t *pData, uint16_t size, TickType_t xTicksToWait);
//Ӳ���ӿڲ㣬ʵ�ֽ�������
typedef uint8_t *(*ModBus_RxPort_TypeDef)(uint16_t *packLen, TickType_t xTicksToWait);

//����һ���ӻ�ģʽ���񣬴�������ṹ��
typedef struct
{
	ModBus_RxPort_TypeDef		fRxPort;		//��ȡ���ݰ��ӿڣ��ɸú��������ռ䣬�����س���
	ModBus_TxPort_TypeDef		fTxPort;		//Ӳ���ӿڲ㣬���ڻظ�
	TickType_t	timeOutTick;			//�޶�����ʱʱ��
	ModBus_Type_enum msgType;			//��Ϣ��ʽ
	
}ModBus_SlaveInit_TypeDef;	

//�ӻ�ģʽ�����ܿ������ṹ��														
typedef struct
{
	SemaphoreHandle_t topicLinkMutex;						//��������
	ModBus_TopicLink_TypeDef *pTopicLinkHand;		//����ͷָ��
	ModBus_SlaveInit_TypeDef init;
	ModBus_state_enum				state;
}ModBus_Slave_TypeDef;


/*======================================== �������� =====================================*/

//�����ӻ� ���񣬿��ƽ��ա��������ַ����ظ�
ModBus_Slave_TypeDef * ModBus_CreateSlave( ModBus_SlaveInit_TypeDef *hSlaveInit );
//��ָ���ӻ�������Ӷ���������Ϣ
int ModBus_AddTopic( ModBus_Slave_TypeDef *hSlave, ModBus_TopicLink_TypeDef *hTopicLink );


//�������ɢ�ͼĴ�������ת��������Ҫ�������ֽڳ���
#define __ModBus_DisRegLenToByteSize( _regLen_ )	(( (_regLen_) >> 3u ) + (((_regLen_) & 0x07u)?( 1u ):( 0u )))

//��С��ת������
void __ModBus_U16SmallToBig( uint16_t u16SmallData, uint8_t * pU16BigData );	
uint16_t __ModBus_U16BigToSmall( uint8_t * pU16BigData );

//������ʽ���·�ָ��
int ModBus_MainTxCom( ModBus_SlaveInit_TypeDef *hSlaveInit,ModBus_Msg_TypeDef *hModBusMsg);


/*======================================== �������� =====================================*/


#if defined(__cplusplus)
}
#endif
#endif	/* __ModBus_H__ */
