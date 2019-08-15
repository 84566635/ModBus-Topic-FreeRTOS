/*======================================================================================*
 * �ļ���   ��modbus.c
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

/*======================================== �ļ����� ===================================*/
#include "modbus.h"

/*======================================== ��ֲ��� ===================================*/

/*======================================== ˽�к궨��  ================================*/

/*======================================== ˽�����Ͷ���  ==============================*/

/*======================================== ˽�к������� ===============================*/


/*======================================== ˽�б������� ===============================*/


/*======================================== �ӿڱ������� ===============================*/

/*======================================== �������� ===================================*/
//����ΪModBusRTU CRCУ���㷨
/* CRC ��λ�ֽ�ֵ�� */
const uint8_t TblCRCHi[] = 
{
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
	0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
	0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
	0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
	0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
	0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
	0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
	0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
	0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
	0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
	0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
	0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
	0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
	0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
	0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
	0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
	0x80, 0x41, 0x00, 0xC1, 0x81, 0x40
};
/* CRC��λ�ֽ�ֵ��*/
const uint8_t TblCRCLo[] = 
{
	0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06,
	0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD,
	0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
	0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A,
	0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC, 0x14, 0xD4,
	0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
	0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3,
	0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4,
	0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
	0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29,
	0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED,
	0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
	0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60,
	0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67,
	0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
	0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68,
	0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE, 0x7E,
	0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
	0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71,
	0x70, 0xB0, 0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92,
	0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
	0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B,
	0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B,
	0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
	0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42,
	0x43, 0x83, 0x41, 0x81, 0x80, 0x40
};

//���ɵ�CRC��
static uint16_t CRC16( uint8_t *pMsg, uint8_t DataLen)
{
	uint16_t Index;        /* CRCѭ���е�����  */
	uint8_t	CRCHi = 0xFF; /* ��CRC�ֽڳ�ʼ��  */
	uint8_t CRCLo = 0xFF; /* ��CRC�ֽڳ�ʼ�� */

	while (DataLen--)  /* ������Ϣ������ */
	{
		Index = CRCHi ^ *pMsg++ ;   /* ����CRC */
		CRCHi = CRCLo ^ TblCRCHi[Index] ;
		CRCLo = TblCRCLo[Index] ;
	}
	return (((uint16_t)(CRCHi) << 8) | CRCLo);
}

/*************************************************
��������:__ModBus_U16BigToSmall

��������:�������ֽڵ��ֽ�����˸�ʽU16ת��ΪС��u16

���ú����嵥: 

������������Դ: 

�������˵��: pU16BigData����˸�ʽ���ֽ��׵�ַ�������ֽ�

�������˵��: 

����ֵ˵��: С�˸�ʽu16

��ע:
*************************************************/
uint16_t __ModBus_U16BigToSmall( uint8_t * pU16BigData )
{
	return ((( uint16_t )( *pU16BigData )) << 8u ) | (*(pU16BigData + 1));
}


/*************************************************
��������:__ModBus_U16SmallToBig

��������:��u16С�˸�ʽ��ֵ ת��Ϊ��˸�ʽ�洢�ֽ���

���ú����嵥: 

������������Դ: 

�������˵��: u16SmallData��С�˸�ʽ��ֵ

�������˵��: pU16BigData����˸�ʽ�ֽ����׵�ַ������Ϊ��

����ֵ˵��: С�˸�ʽu16

��ע:
*************************************************/
void __ModBus_U16SmallToBig( uint16_t u16SmallData, uint8_t * pU16BigData )
{
	if( pU16BigData == NULL )
		return;
	*pU16BigData = (uint8_t)(u16SmallData >> 8u);
	*( ++pU16BigData) = (uint8_t)(u16SmallData);
}

/*************************************************
��������:ModBus_RtuAddCrc

��������:�������ֽ����н�β������ModBusRTU��������CRC�ֽ�.

���ú����嵥: 

������������Դ: 

�������˵��: uint8_t *pData
								�����ֽ���ָ��
							uint16_t usefulDataLen
								�ֽ�������Ч�����ֽ������ֽ���ʵ�ʴ洢����Ӧ�ñȸ�ֵ��2���ֽ�

�������˵��: 

����ֵ˵��: 

��ע:
*************************************************/
void ModBus_RtuAddCrc( uint8_t *pData, uint16_t usefulDataLen  )
{
	__ModBus_U16SmallToBig( CRC16( pData, usefulDataLen ), pData + usefulDataLen );
}


/*************************************************
��������:ModBus_CreatErrorAckPack

��������:������Ϣ�ṹ������е�errorCode����Ϣ�����ɱ�׼�쳣��Ӧ��Ϣ�ֽ�������

���ú����嵥: 

������������Դ: 

�������˵��:	ModBus_Msg_TypeDef * hModBusMsg, 
								���������롢�쳣�����Ϣ
							ModBus_Type_enum msgType,
								��Ϣ��ʽ
�������˵��: uint16_t * packLen
								�����ֽ����ĳ���
����ֵ˵��: �������ɵ���Ϣ�ֽ���ָ�룬��Ҫ�ɽ����������ͷ�

��ע:
*************************************************/
uint8_t * ModBus_CreatErrorAckPack( ModBus_Msg_TypeDef * hModBusMsg, ModBus_Type_enum msgType, uint16_t * packLen)
{
	uint8_t *pData = NULL;
	switch( msgType )
	{
	case ModBus_TYPE_RTU:
		pData = pvPortMalloc( 5 );
		if( NULL == pData )
			break;
		pData[0] = hModBusMsg->parse.slaveId;
		pData[1] = hModBusMsg->parse.funCode | 0x80u;
		pData[2] = hModBusMsg->parse.errorCode;
		ModBus_RtuAddCrc( pData, 3 );
		*packLen = 5;
		break;
	case ModBus_TYPE_ASCII:
		break;
	case ModBus_TYPE_TCP:
		break;
	}
	return pData;
}


/*************************************************
��������:ModBus_Parse

��������:�õ�һ��������ModBus����֡�����봦������������Ч�Խ����жϡ�
		��Ч��ʽ���ݽ���ֱ����������ʽ��ȷ�����ǹ��������������Ľ������
		�쳣��Ӧ��

���ú����嵥: 

������������Դ: 

�������˵��:	ModBus_Msg_TypeDef * hModBusMsg 
								���������packDataָ���������ݣ�packLen���ݳ��ȣ�type��������
							ModBus_Type_enum msgType
								������Ϣ����
							
�������˵��: hModBusMsg->parse�洢�����������

����ֵ˵��: ����0��ʾ�����ɹ��������쳣������ʧ�ܣ�����ʧ�ܹ����룬����hModBusMsg->parse.errorCode��

��ע:
*************************************************/
int ModBus_Parse( ModBus_Msg_TypeDef * hModBusMsg, ModBus_Type_enum msgType )
{
	int result = -1;
	uint16_t i;
	
	switch( msgType )
	{
	case ModBus_TYPE_RTU:
		//��С�����ж�
		if( hModBusMsg->packLen < MODBUS_RTU_PACKLEN_MIN )
			break;
		//CRCУ��
		if( 0 != CRC16( hModBusMsg->packData, hModBusMsg->packLen ))
			break;
		//��ʼ����
		hModBusMsg->parse.slaveId = (hModBusMsg->packData)[0];
		hModBusMsg->parse.funCode = (hModBusMsg->packData)[1];
		hModBusMsg->parse.dataType = MODBUS_DATA_TPYE_NULL;		//������������Ϊδ֪
		//ƥ�书����
		switch( hModBusMsg->parse.funCode )
		{
		case MODBUS_FUN_READ_DISOUT:
			hModBusMsg->parse.dataType = MODBUS_DATA_TPYE_DISOUT;
		case MODBUS_FUN_READ_DISIN:
			if( MODBUS_DATA_TPYE_NULL == hModBusMsg->parse.dataType )
				hModBusMsg->parse.dataType = MODBUS_DATA_TPYE_DISIN;
		case MODBUS_FUN_READ_HOLD:
			if( MODBUS_DATA_TPYE_NULL == hModBusMsg->parse.dataType )
				hModBusMsg->parse.dataType = MODBUS_DATA_TPYE_HOLD;
		case MODBUS_FUN_READ_INPUT:
			if( MODBUS_DATA_TPYE_NULL == hModBusMsg->parse.dataType )
				hModBusMsg->parse.dataType = MODBUS_DATA_TPYE_INPUT;
			//�����ж�
			if( MODBUS_RTU_PACKLEN_READ_SIZE != hModBusMsg->packLen )
				break;
			hModBusMsg->parse.regAddrStart = __ModBus_U16BigToSmall( (hModBusMsg->packData) + 2 );
			hModBusMsg->parse.regLen = __ModBus_U16BigToSmall( (hModBusMsg->packData) + 4 );
			//��ɢ��Ĵ������ݿ�Ȳ�ͬ
			if( ( MODBUS_FUN_READ_DISOUT == hModBusMsg->parse.funCode ) || ( MODBUS_FUN_READ_DISIN == hModBusMsg->parse.funCode) )
			{
				hModBusMsg->parse.byteLen = __ModBus_DisRegLenToByteSize( hModBusMsg->parse.regLen );
			}
			else
			{
				hModBusMsg->parse.byteLen = hModBusMsg->parse.regLen * 2u;
			}
			//�����洢�ռ�
			if( hModBusMsg->parse.pValue != NULL )
				vPortFree( hModBusMsg->parse.pValue );
			hModBusMsg->parse.pValue = pvPortMalloc( hModBusMsg->parse.byteLen );
			if( hModBusMsg->parse.pValue == NULL )
				break;		//������
			memset( hModBusMsg->parse.pValue, 0, hModBusMsg->parse.byteLen );
			
			result = 0;
			break;
			
		case MODBUS_FUN_WRITE_DISOUT:
			hModBusMsg->parse.dataType = MODBUS_DATA_TPYE_DISOUT;
		case MODBUS_FUN_WRITE_HOLD:
			if( MODBUS_DATA_TPYE_NULL == hModBusMsg->parse.dataType )
				hModBusMsg->parse.dataType = MODBUS_DATA_TPYE_HOLD;
			//�����ж�
			if( MODBUS_RTU_PACKLEN_READ_SIZE != hModBusMsg->packLen )
				break;
			//������ֵ�洢��������Ϊ2���ֽ�
			if( hModBusMsg->parse.pValue != NULL )
				vPortFree( hModBusMsg->parse.pValue );
			hModBusMsg->parse.pValue = pvPortMalloc( sizeof(uint16_t) );
			if( hModBusMsg->parse.pValue == NULL )
				break;		//������
			*(hModBusMsg->parse.pValue) = __ModBus_U16BigToSmall( (hModBusMsg->packData) + 4 );
			hModBusMsg->parse.regLen = 1;
			if( MODBUS_FUN_WRITE_DISOUT == hModBusMsg->parse.funCode )		//������ɢ����ͣ�д��ֵ���޶�
			{
				if( ( *(hModBusMsg->parse.pValue) != MODBUS_DIS_VALUE_ON ) && ( *(hModBusMsg->parse.pValue) != MODBUS_DIS_VALUE_OFF ))
				{
					hModBusMsg->parse.errorCode = MODBUS_REACK_ERROR_DATA;		//���ݷ�Χ�쳣��Ӧ
					break;
				}
			}
			
			result = 0;
			break;
			
		case MODBUS_FUN_WRITE_DISOUT_MORE:
			hModBusMsg->parse.dataType = MODBUS_DATA_TPYE_DISOUT;
			hModBusMsg->parse.regLen = __ModBus_U16BigToSmall( (hModBusMsg->packData) + 4 );
			hModBusMsg->parse.byteLen = (hModBusMsg->packData)[ 6 ];
			if(	( hModBusMsg->parse.byteLen != 0 ) ||\
					((((int16_t)( hModBusMsg->parse.byteLen )) * 8u) < hModBusMsg->parse.regLen) ||\
					((((int16_t)( hModBusMsg->parse.byteLen - 1 )) * 8u) >= hModBusMsg->parse.regLen ))
			{
				//����Byte��ֵ�����Ӧ���ݳ��Ȳ��ԡ���ʽ���󣬺���
				break;
			}
			//������ֵ�洢��������ΪbyteLen���ֽ�
			if( hModBusMsg->parse.pValue != NULL )
				vPortFree( hModBusMsg->parse.pValue );
			hModBusMsg->parse.pValue = pvPortMalloc( hModBusMsg->parse.byteLen );
			if( hModBusMsg->parse.pValue == NULL )
				break;		//������
			memcpy( hModBusMsg->parse.pValue, (hModBusMsg->packData) + 7, hModBusMsg->parse.byteLen );
			
			result = 0;
			break;
			
		case MODBUS_FUN_WRITE_HOLD_MORE:
			hModBusMsg->parse.dataType = MODBUS_DATA_TPYE_HOLD;
			hModBusMsg->parse.regLen = __ModBus_U16BigToSmall( (hModBusMsg->packData) + 4 );
			hModBusMsg->parse.byteLen = (hModBusMsg->packData)[ 6 ];
			if(	( hModBusMsg->parse.byteLen != 0 ) ||\
					( ( hModBusMsg->parse.byteLen ) & 0x01u ) ||\
					( ( ( (int16_t)( hModBusMsg->parse.byteLen )) >> 1u) != hModBusMsg->parse.regLen) )
			{
				//����Byte��ֵ�����Ӧ���ݳ��Ȳ��ԡ���ʽ���󣬺���
				break;
			}
			//������ֵ�洢��������ΪbyteLen���ֽ�
			if( hModBusMsg->parse.pValue != NULL )
				vPortFree( hModBusMsg->parse.pValue );
			hModBusMsg->parse.pValue = pvPortMalloc( sizeof(uint16_t) * (hModBusMsg->parse.byteLen >> 0x01u) );
			if( hModBusMsg->parse.pValue == NULL )
				break;		//������
			for( i = 0; i < hModBusMsg->parse.regLen; ++i )
			{
				((uint16_t *)(hModBusMsg->parse.pValue))[i] = __ModBus_U16BigToSmall( (hModBusMsg->packData) + 7 + 2 * i );
			}
			
			result = 0;
			break;
		
		default:
			hModBusMsg->parse.errorCode = MODBUS_REACK_ERROR_FUN;		//����֧�ֵĹ������б���
			break;
		}
		break;
		
	case ModBus_TYPE_ASCII:
		break;
	case ModBus_TYPE_TCP:
		break;
	}
	
	return result;
}




/*************************************************
��������:ModBus_CreateReplyPack

��������:��ModBusָ���������������֮��ͨ���ú���������ȷ�Ļظ����ݰ���������лظ�

���ú����嵥: 

������������Դ: 

�������˵��:	ModBus_Msg_TypeDef * hModBusMsg 
								���������parse�ѽ������ݣ�parse.pValue��ֵ��
							ModBus_Type_enum msgType
								�����Ϣ����
							
�������˵��: uint16_t * packLen
								�����ֽ����ĳ���

����ֵ˵��: �������ɵ���Ϣ�ֽ���ָ�룬��Ҫ�ɽ����������ͷ�

��ע:
*************************************************/
uint8_t *ModBus_CreateReplyPack( ModBus_Msg_TypeDef * hModBusMsg, ModBus_Type_enum msgType, uint16_t *packLen)
{
	uint8_t *pack = NULL;
	uint16_t i;
	*packLen = 0;
	
	switch( msgType )
	{
	case ModBus_TYPE_RTU:
		//ƥ�书����
		switch( hModBusMsg->parse.funCode )
		{
		case MODBUS_FUN_READ_DISOUT:
		case MODBUS_FUN_READ_DISIN:
		case MODBUS_FUN_READ_HOLD:
		case MODBUS_FUN_READ_INPUT:
			//��ȡ��ṹ����
			*packLen = 5 + hModBusMsg->parse.byteLen;
			pack = pvPortMalloc( *packLen );
			if( pack == NULL )
				break;
			pack[ 0 ] = hModBusMsg->parse.slaveId;
			pack[ 1 ] = hModBusMsg->parse.funCode;
			pack[ 2 ] = hModBusMsg->parse.byteLen;
			if( hModBusMsg->parse.funCode == MODBUS_FUN_READ_DISOUT || hModBusMsg->parse.funCode == MODBUS_FUN_READ_DISIN )
			{
				memcpy( pack + 3, hModBusMsg->parse.pValue, hModBusMsg->parse.byteLen );
			}
			else
			{
				//���ڼĴ������ݣ���Ҫ��С��ת��
				for( i = 0; i < hModBusMsg->parse.byteLen; i += 2)
				{
					__ModBus_U16SmallToBig( hModBusMsg->parse.pValue[ i >> 1u ], pack + 3 + i );
				}
			}
			ModBus_RtuAddCrc( pack, *packLen - 2 );
		
			break;
			
		case MODBUS_FUN_WRITE_DISOUT:
		case MODBUS_FUN_WRITE_HOLD:
			//д�����ṹ������
			*packLen = 8;
			pack = pvPortMalloc( *packLen );
			if( pack == NULL )
				break;
			pack[ 0 ] = hModBusMsg->parse.slaveId;
			pack[ 1 ] = hModBusMsg->parse.funCode;
			__ModBus_U16SmallToBig( hModBusMsg->parse.regAddrStart , pack + 2 );
			__ModBus_U16SmallToBig( *(hModBusMsg->parse.pValue), pack + 4 );
			ModBus_RtuAddCrc( pack, *packLen - 2 );
		
			break;
			
		case MODBUS_FUN_WRITE_DISOUT_MORE:
		case MODBUS_FUN_WRITE_HOLD_MORE:
			//д����ṹ����
			*packLen = 8;
			pack = pvPortMalloc( *packLen );
			if( pack == NULL )
				break;
			pack[ 0 ] = hModBusMsg->parse.slaveId;
			pack[ 1 ] = hModBusMsg->parse.funCode;
			__ModBus_U16SmallToBig( hModBusMsg->parse.regAddrStart , pack + 2 );
			__ModBus_U16SmallToBig( hModBusMsg->parse.regLen, pack + 4 );
			ModBus_RtuAddCrc( pack, *packLen - 2 );
			break;
		
		default:
			//����֧�ֵĹ������б���
			break;
		}
	
		break;
	case ModBus_TYPE_ASCII:
		break;
	case ModBus_TYPE_TCP:
		break;
	}
	return pack;
}



/*************************************************
��������:ModBus_Distribution

��������:��modbus����ͨ������֮�󣬵��øú��������ж�д����ַ�������pSlave�е�topicLink
	����������зַ�����ͳһ��������лظ�

���ú����嵥: 

������������Դ: 

�������˵��:	ModBus_Slave_TypeDef * hSlave
								�������ṹ�壬��������������������Ϣ
							ModBus_Msg_TypeDef * hModBusMsg 
								��Ϣ�ṹ�壬���������Ϣ
�������˵��: hModBusMsg->parse.errorCode����¼ʧ��ʱ���쳣��

����ֵ˵��: ����0��ʾ�ɹ��������ʾ�쳣

��ע://�����ƣ�δ���Ƴ�ʱ����
*************************************************/
int ModBus_Distribution( ModBus_Slave_TypeDef * hSlave, ModBus_Msg_TypeDef * hModBusMsg )
{
	int result = -1;
	uint16_t i, j;
	ModBus_TopicLink_TypeDef *pTopicLink;
	uint16_t regAddr = hModBusMsg->parse.regAddrStart;
	uint16_t regLen = 1;
	uint16_t regAddrEnd = hModBusMsg->parse.regAddrStart + hModBusMsg->parse.regLen;
	uint16_t byteSize;
	uint8_t findTopic = 0;
	uint16_t *pValue = NULL;
	
	uint8_t isWrite = 0;	//�Ƿ�Ϊд��ָ��
	uint8_t isDis = 0;		//�Ƿ�Ϊ��ɢ�Ĵ���
	
	//���ж϶�д����
	switch( hModBusMsg->parse.funCode )
	{
	case MODBUS_FUN_WRITE_DISOUT:
	case MODBUS_FUN_WRITE_HOLD:
	case MODBUS_FUN_WRITE_DISOUT_MORE:
	case MODBUS_FUN_WRITE_HOLD_MORE:
		isWrite = 1;
	}
	//�ж϶������Ƿ�Ϊ��ɢ
	switch( hModBusMsg->parse.funCode )
	{
	case MODBUS_FUN_READ_DISOUT:
	case MODBUS_FUN_READ_DISIN:
	case MODBUS_FUN_WRITE_DISOUT:
	case MODBUS_FUN_WRITE_DISOUT_MORE:
		isDis = 1;
	}
	
	if( ( xTaskGetTickCount() < hSlave->init.timeOutTick + hModBusMsg->getTimeTick ) &&\
			( pdTRUE == xSemaphoreTake( hSlave->topicLinkMutex, hSlave->init.timeOutTick + hModBusMsg->getTimeTick - xTaskGetTickCount())))
	{
		while( regAddr < regAddrEnd )		//regAddr������ֱ����β
		{
			//Ѱ��ƥ������ݵ�
			for( pTopicLink = hSlave->pTopicLinkHand, i = 0, findTopic = 0; pTopicLink != NULL ; ++i, pTopicLink = pTopicLink->pPext)
			{
				if( ( pTopicLink->slaveId == hModBusMsg->parse.slaveId ) &&\
						( pTopicLink->dataType == hModBusMsg->parse.dataType ))
				{
					//�ӻ���ַ����������ƥ��֮�󣬽�һ��ƥ���ַ
					switch( pTopicLink->dataMode )
					{
					case MODBUS_DATA_MODE_ALL:
						if( ( pTopicLink->regAddrStart <= regAddr ) &&\
							  ( pTopicLink->regLen + pTopicLink->regAddrStart > regAddr ))
						{
							//����ģʽ�£�ֻҪ�н�������regAddr����ʼ�ͽ�β֮��
							findTopic = 1;
						}
						break;
					
					case MODBUS_DATA_MODE_STRICT:
						if(	( regAddr == hModBusMsg->parse.regAddrStart	) &&\
								( pTopicLink->regAddrStart == regAddr ) &&\
							  ( pTopicLink->regLen == hModBusMsg->parse.regLen ))
						{
							//�ϸ�ģʽ�£����뵥��ָ���ȫ��Ӧ
							findTopic = 1;
						}
						break;
					
					case MODBUS_DATA_MODE_CONTAIN:
						if( ( pTopicLink->regAddrStart == regAddr ) &&\
							  ( pTopicLink->regLen + pTopicLink->regAddrStart <= regAddrEnd ))
						{
							//����ģʽ�£���ǰ��ʼ��ַ������ȣ��ҽ�β��ַӦ��С�ڵ���ָ�Χ
							findTopic = 1;
						}
						break;
					}
				}
				if( findTopic )
					break;	//��ǰ����ѭ�������ҵ�ƥ�䶩��
			}
			if( findTopic )
			{
				//���ҵ���ǰ�Ĵ�����ַƥ�䶩�ģ����зַ�����ǰ׼��
				//����ʵ��Ҫ�õļĴ�������
				if( regAddrEnd >= pTopicLink->regLen + pTopicLink->regAddrStart )
					regLen = pTopicLink->regLen + pTopicLink->regAddrStart - regAddr;
				else
					regLen = regAddrEnd - regAddr;
				//׼�����ݻ������ݿռ�
				if( pValue != NULL )
				{
					vPortFree( pValue );
					pValue = NULL;
				}
				if( isDis )
				{
					//��ɢ������׼��
					byteSize = __ModBus_DisRegLenToByteSize( regLen );
					pValue = pvPortMalloc( byteSize );	
					if( pValue != NULL )
						break;		//������
					memset( pValue, 0, byteSize  );
					if( isWrite )
					{
						//����ɢֵ��msgתд��pValue
						for( i = 0, j = regAddr - hModBusMsg->parse.regAddrStart; i < regLen ; ++i)
						{
							if( (((uint8_t *)(hModBusMsg->parse.pValue))[ j / 8u ] >> ( j % 8u)) & 0x01u )
								((uint8_t *)(pValue))[ i / 8u ] |= 0x01u << i % 8u;
						}
					}
				}
				else
				{
					//U16��������׼��
					byteSize = regLen * 2u;
					pValue = pvPortMalloc( byteSize );
					if( pValue == NULL )
						break;		//������
					memset( pValue, 0, byteSize  );
					if( isWrite )
					{
						//��ֵ��msgתд��pValue
						for( i = 0, j = regAddr - hModBusMsg->parse.regAddrStart; i < regLen ; ++i)
						{
							pValue[ i ] = (hModBusMsg->parse.pValue)[j];
						}
					}
				}
				//���ݼ��ռ�Ȳ���׼�����������е���
				if( isWrite )
				{
					hModBusMsg->parse.errorCode = (pTopicLink->pWriteFun)( pTopicLink, pValue, regAddr, regLen);
				}
				else
				{
					hModBusMsg->parse.errorCode = (pTopicLink->pReadFun)( pTopicLink, pValue, regAddr, regLen);
				}
				if( hModBusMsg->parse.errorCode != MODBUS_REACK_ERROR_NULL )
					break;
				//������������
				//����Ƕ�ȡ�࣬Ӧ�������ݴ洢����Ӧ�ռ���
				if( !isWrite )
				{
					if( isDis )
					{
						//����ɢֵ��pValueתд��msg
						for( i = 0, j = regAddr - hModBusMsg->parse.regAddrStart; i < regLen ; ++i)
						{
							if( (((uint8_t *)(pValue))[ i / 8u ] >> ( j % 8u)) & 0x01u )
								((uint8_t *)(hModBusMsg->parse.pValue))[ j / 8u ] |= 0x01u << i % 8u;
						}
					}
					else
					{
						//��ֵ��pValueתд��msg
						for( i = 0, j = regAddr - hModBusMsg->parse.regAddrStart; i < regLen ; ++i)
						{
							(hModBusMsg->parse.pValue)[j] = pValue[ i ];
						}
					}
				}
				//regAddr����
				regAddr += regLen;
				//��ʼ�µĶ���ƥ����Ѱ
			}
			else
			{
				//������ж��������δ����ƥ�䡣
				hModBusMsg->parse.errorCode = MODBUS_REACK_ERROR_REG;		//�Ĵ�����ַ����
				break;	//�˳��ַ�
			}
			
		}
		if( regAddr >= regAddrEnd  )		//��ַ���Ѿ�����򳬹���������ʾ������ɷַ�
			result = 0;
		
		xSemaphoreGive( hSlave->topicLinkMutex);
	}
	
	if( pValue != NULL )
	{
		vPortFree( pValue );
		pValue = NULL;
	}
	return result;
}



/*************************************************
�������ƣ�ModBus_FreeTopicLink

��������������TopicLink�������������������ṹ�塣

���ú����嵥: 

������������Դ: 

�������˵��: ModBus_TopicLink_TypeDef *hTopicLink
								��Ҫ������������ָ��

�������˵��: 

����ֵ˵��: 

��ע://�����ƣ���û�ж�����ȫ����,�Ͻ�����ͬʱ������ӵ�д�����
*************************************************/
void ModBus_FreeTopicLink( ModBus_TopicLink_TypeDef *hTopicLink )
{
	if( hTopicLink == NULL )
		return;
	if( hTopicLink->pPext == NULL )
	{
		vPortFree( hTopicLink );
	}
	else
	{
		ModBus_FreeTopicLink( hTopicLink->pPext );		//�ݹ��������
	}
}


/*************************************************
�������ƣ�ModBus_FreeSlave

��������������Slave�ṹ�壬�����ڲ�ָ��ȡ�

���ú����嵥: 

������������Դ: 

�������˵��: ModBus_Slave_TypeDef *hSlave
								��Ҫ�����Ľṹ��ָ��

�������˵��: 

����ֵ˵��: 

��ע://�����ƣ���û�ж�����ȫ����,�Ͻ�����ͬʱ������ӵ�д�����
*************************************************/
void ModBus_FreeSlave( ModBus_Slave_TypeDef *hSlave )
{
	if( hSlave == NULL )
		return;
	if( hSlave->topicLinkMutex != NULL )
	{
		vPortFree( hSlave->topicLinkMutex );
		hSlave->topicLinkMutex = NULL;
	}
	if( hSlave->pTopicLinkHand != NULL )
	{
		ModBus_FreeTopicLink( hSlave->pTopicLinkHand );
		hSlave->pTopicLinkHand = NULL;
	}
	vPortFree( hSlave );
}

/*************************************************
�������ƣ�ModBus_SlaveTask

�����������ܿ�Modbus���ݽ��ա��������ַ������ظ���������������������

���ú����嵥: 

������������Դ: 

�������˵��: ModBus_SlaveInit_TypeDef *hSlaveInit
								��ʼ������

�������˵��: 

����ֵ˵��: 

��ע://�����ƣ�δ���Ƴ�ʱ����
*************************************************/
void ModBus_SlaveTask( ModBus_Slave_TypeDef *hSlave )
{
	ModBus_Msg_TypeDef hModBusMsg;
	memset( &hModBusMsg, 0, sizeof( hModBusMsg ) );
	
	uint8_t * pReplyData = NULL;
	uint16_t replyLen = 0;
	
	while(1)
	{
		//��ȡModBus���ݰ�
		hModBusMsg.packData = hSlave->init.fRxPort( &(hModBusMsg.packLen), portMAX_DELAY );
		if( hModBusMsg.packData == NULL )
			continue;
		hModBusMsg.getTimeTick = xTaskGetTickCount();
		hModBusMsg.parse.errorCode = MODBUS_REACK_ERROR_NULL;
		//���ý���
		if( 0 != ModBus_Parse( &hModBusMsg, hSlave->init.msgType ) )
		{
			if( MODBUS_REACK_ERROR_NULL != hModBusMsg.parse.errorCode )
			{
				pReplyData = ModBus_CreatErrorAckPack( &hModBusMsg, hSlave->init.msgType, &replyLen);
			}
		}
		else
		{
			//����ͨ�������зַ�
			if( 0 != ModBus_Distribution( hSlave, &hModBusMsg ))
			{
				//�ַ������г����쳣
				if( MODBUS_REACK_ERROR_NULL == hModBusMsg.parse.errorCode )
				{
					hModBusMsg.parse.errorCode = MODBUS_REACK_ERROR_DAMAGE;		//δ֪���豸����
				}
				pReplyData = ModBus_CreatErrorAckPack( &hModBusMsg, hSlave->init.msgType, &replyLen);
			}
			else
			{
				//�ַ��ɹ���ɣ�����������Ӧ��Ϣ���лظ�
				pReplyData = ModBus_CreateReplyPack( &hModBusMsg, hSlave->init.msgType, &replyLen);
			}
		}
		if( ( pReplyData != NULL ) &&\
				(	hSlave->init.timeOutTick + hModBusMsg.getTimeTick > xTaskGetTickCount() ))
		{
			//���лظ�
			hSlave->init.fTxPort( pReplyData, replyLen, xTaskGetTickCount() - hModBusMsg.getTimeTick - hSlave->init.timeOutTick);
			vPortFree( pReplyData );
			pReplyData = NULL;
		}
		if( hModBusMsg.parse.pValue != NULL )
		{
			vPortFree( hModBusMsg.parse.pValue );
			hModBusMsg.parse.pValue = NULL;
			hModBusMsg.parse.byteLen = 0;
		}
		if( hModBusMsg.packData != NULL )
		{
			vPortFree( hModBusMsg.packData );
			hModBusMsg.packData = NULL;
			hModBusMsg.packLen = 0;
		}
	}
}


/*************************************************
�������ƣ�ModBus_CreateSlave

��������������SlaveTask���񣬷���������������ṹָ��

���ú����嵥: ModBus_SlaveTask

������������Դ: 

�������˵��: ModBus_SlaveInit_TypeDef *hSlaveInit
								��ʼ������

�������˵��: 

����ֵ˵��: ModBus_Slave_TypeDef *hSlave

��ע:
*************************************************/
ModBus_Slave_TypeDef * ModBus_CreateSlave( ModBus_SlaveInit_TypeDef *hSlaveInit )
{
	ModBus_Slave_TypeDef *hSlave = NULL;
	int8_t result = -1;
	
	hSlave = pvPortMalloc( sizeof(ModBus_Slave_TypeDef) );
	if( hSlave == NULL )
		return hSlave;
	
	do
	{
		memset( hSlave, 0, sizeof(ModBus_Slave_TypeDef) );
		//��ʼ������
		hSlave->topicLinkMutex = xSemaphoreCreateMutex();
		if( hSlave->topicLinkMutex == NULL )
			break;
		hSlave->pTopicLinkHand = NULL;
		hSlave->state = ModBus_STATE_READY;
		hSlave->init.msgType = hSlaveInit->msgType;
		hSlave->init.fRxPort = hSlaveInit->fRxPort;
		hSlave->init.fTxPort = hSlaveInit->fTxPort;
		hSlave->init.timeOutTick = hSlaveInit->timeOutTick;
		
		if( pdPASS != xTaskCreate(	(void (*)(void *))&ModBus_SlaveTask, 
																"ModBusSlave", 
																MODBUS_SLAVETASK_STACK_SIZE, 
																hSlave, 
																MODBUS_SLAVETASK_PRIORITY_NUM, 
																NULL ))
		{
			break;	
		}
		
		result = 0;
	}while(0);
	
	if( result != 0 )
	{
		if( hSlave != NULL )
		{
			ModBus_FreeSlave( hSlave );
			hSlave = NULL;
		}
	}
	return hSlave;
}

/*************************************************
�������ƣ�ModBus_AddTopic

������������ָ��SlaveTask�����У��������ݵ㶩������

���ú����嵥: 

������������Դ: 

�������˵��: ModBus_Slave_TypeDef *hSlave
								ָ����SlaveTask��������������ͷ��������������
							ModBus_TopicLink_TypeDef *hTopicLink
								����Ҫ���ĵ����ݵ���Ϣ��������pNext
								
�������˵��: 

����ֵ˵��:0�ɹ�������ʧ��

��ע://�����ƣ���Ҫȥ��ȷ�����⡣
*************************************************/
int ModBus_AddTopic( ModBus_Slave_TypeDef *hSlave, ModBus_TopicLink_TypeDef *hTopicLink )
{
	int result = -1;
	ModBus_TopicLink_TypeDef *pTopicLinkTmp = NULL;
	
	do
	{
		if( hSlave == NULL || hTopicLink == NULL || hSlave->topicLinkMutex == NULL)
			break;
		if( pdTRUE == xSemaphoreTake( hSlave->topicLinkMutex, portMAX_DELAY ) )
		{
			do
			{
				pTopicLinkTmp = hSlave->pTopicLinkHand;
				if( pTopicLinkTmp != NULL )
				{
					for( ; pTopicLinkTmp->pPext != NULL ; pTopicLinkTmp = pTopicLinkTmp->pPext)
					{
					} 
					pTopicLinkTmp->pPext = pvPortMalloc( sizeof( ModBus_TopicLink_TypeDef ) );
					if( pTopicLinkTmp->pPext == NULL )
						break;
					pTopicLinkTmp = pTopicLinkTmp->pPext;
				}
				else
				{
					pTopicLinkTmp = hSlave->pTopicLinkHand = pvPortMalloc( sizeof( ModBus_TopicLink_TypeDef ) );
					if( pTopicLinkTmp == NULL )
						break;
				}
				pTopicLinkTmp->pWriteFun = hTopicLink->pWriteFun;
				pTopicLinkTmp->pReadFun = hTopicLink->pReadFun;
				pTopicLinkTmp->regAddrStart = hTopicLink->regAddrStart;
				pTopicLinkTmp->regLen = hTopicLink->regLen;
				pTopicLinkTmp->slaveId = hTopicLink->slaveId;
				pTopicLinkTmp->dataType = hTopicLink->dataType;
				pTopicLinkTmp->dataMode = hTopicLink->dataMode;
				pTopicLinkTmp->pPext = NULL;
				
				result = 0;
			}while(0);
			xSemaphoreGive( hSlave->topicLinkMutex );
		}		
	}while(0);
		
	return result;
}



/*************************************************
��������:ModBus_CreateMainPack

��������:����msg.parse�е���Ϣ������ModBusЭ������ָ�����ݰ����ɲ����ظ�ָ�롣ͬʱ������ָ������Ҫ��pValue�ռ�

���ú����嵥: 

������������Դ: 

�������˵��:	ModBus_Msg_TypeDef * hModBusMsg 
								�����·����������:�ӻ���ַ�������롢�Ĵ�����ʼ��ַ���Ĵ�������(��ѡ)��ֵ(��ѡ)
							ModBus_Type_enum msgType
								��Ϣ����
							
�������˵��: uint16_t * packLen
								�����ֽ����ĳ���

����ֵ˵��: �������ɵ���Ϣ�ֽ���ָ�룬��Ҫ�ɽ����������ͷţ����ΪNULL������Ϊ�޷������ռ������������

��ע:
*************************************************/
uint8_t *ModBus_CreateMainPack( ModBus_Msg_TypeDef * hModBusMsg, ModBus_Type_enum msgType, uint16_t *packLen)
{
	uint8_t *pack = NULL;
	uint16_t i;
	uint8_t isOtherCase = 0;
	
	hModBusMsg->parse.errorCode = MODBUS_REACK_ERROR_DATA;
	
	switch( msgType )
	{
	case ModBus_TYPE_RTU:
		hModBusMsg->parse.errorCode = MODBUS_REACK_ERROR_NULL;
	
		//ƥ�书����
		switch( hModBusMsg->parse.funCode )
		{
		case MODBUS_FUN_READ_DISOUT:
		case MODBUS_FUN_READ_DISIN:
			hModBusMsg->parse.byteLen = __ModBus_DisRegLenToByteSize( hModBusMsg->parse.regLen );
			isOtherCase = 1;
		case MODBUS_FUN_READ_HOLD:
		case MODBUS_FUN_READ_INPUT:
			//��ɢ��Ĵ������ݿ�Ȳ�ͬ
			if( !isOtherCase )
			{
				hModBusMsg->parse.byteLen = hModBusMsg->parse.regLen * 2u;
			}
			//�����洢�ռ�
			if( hModBusMsg->parse.pValue != NULL )
				vPortFree( hModBusMsg->parse.pValue );
			hModBusMsg->parse.pValue = pvPortMalloc( hModBusMsg->parse.byteLen );
			if( hModBusMsg->parse.pValue == NULL )
				break;
			memset( hModBusMsg->parse.pValue, 0 , hModBusMsg->parse.byteLen );
			//��ȡ��ṹ����
			*packLen = 8;
			pack = pvPortMalloc( *packLen );
			if( pack == NULL )
				break;
			pack[ 0 ] = hModBusMsg->parse.slaveId;
			pack[ 1 ] = hModBusMsg->parse.funCode;
			__ModBus_U16SmallToBig( hModBusMsg->parse.regAddrStart, pack + 2 );
			__ModBus_U16SmallToBig( hModBusMsg->parse.regLen, pack + 4 );
			ModBus_RtuAddCrc( pack, *packLen - 2 );
			
			break;
			
		case MODBUS_FUN_WRITE_DISOUT:
			if( hModBusMsg->parse.pValue == NULL || \
				  (	*(hModBusMsg->parse.pValue) != MODBUS_DIS_VALUE_ON && \
						*(hModBusMsg->parse.pValue) != MODBUS_DIS_VALUE_OFF ))
				break;
			isOtherCase = 1;
		case MODBUS_FUN_WRITE_HOLD:
			if( !isOtherCase )
				if( hModBusMsg->parse.pValue == NULL )
					break;
			*packLen = 8;
			pack = pvPortMalloc( *packLen );
			if( pack == NULL )
				break;
			pack[ 0 ] = hModBusMsg->parse.slaveId;
			pack[ 1 ] = hModBusMsg->parse.funCode;
			__ModBus_U16SmallToBig( hModBusMsg->parse.regAddrStart , pack + 2 );
			__ModBus_U16SmallToBig( *(hModBusMsg->parse.pValue), pack + 4 );
			ModBus_RtuAddCrc( pack, *packLen - 2 );
		
			break;
			
		case MODBUS_FUN_WRITE_DISOUT_MORE:
		case MODBUS_EXFUN_REPORT_DISOUT_MORE:
		case MODBUS_EXFUN_REPORT_DISIN_MORE:
			if( hModBusMsg->parse.pValue == NULL || \
				  hModBusMsg->parse.byteLen == 0 || \
					hModBusMsg->parse.byteLen != __ModBus_DisRegLenToByteSize( hModBusMsg->parse.regLen ))
				break;
			isOtherCase = 1;
			
		case MODBUS_FUN_WRITE_HOLD_MORE:
		case MODBUS_EXFUN_REPORT_HOLD_MORE:
		case MODBUS_EXFUN_REPORT_INPUT_MORE:
			//д����ṹ����
			if( !isOtherCase )
			{
				if( hModBusMsg->parse.pValue == NULL || \
				  hModBusMsg->parse.byteLen == 0 ||\
					hModBusMsg->parse.byteLen != 2u * hModBusMsg->parse.regLen)
					break;
			}
			//д�����ṹ������
			*packLen = 9 + hModBusMsg->parse.byteLen;
			pack = pvPortMalloc( *packLen );
			if( pack == NULL )
				break;
			pack[ 0 ] = hModBusMsg->parse.slaveId;
			pack[ 1 ] = hModBusMsg->parse.funCode;
			__ModBus_U16SmallToBig( hModBusMsg->parse.regAddrStart , pack + 2 );
			__ModBus_U16SmallToBig( hModBusMsg->parse.regLen, pack + 4 );
			pack[ 6 ] = hModBusMsg->parse.byteLen;
			
			if( isOtherCase )
			{
				memcpy( pack + 7, hModBusMsg->parse.pValue, hModBusMsg->parse.byteLen );
			}
			else
			{
				//���ڼĴ������ݣ���Ҫ��С��ת��
				for( i = 0; i < hModBusMsg->parse.byteLen; i += 2)
				{
					__ModBus_U16SmallToBig( hModBusMsg->parse.pValue[ i >> 1u ], pack + 7 + i );
				}
			}
			ModBus_RtuAddCrc( pack, *packLen - 2 );
			hModBusMsg->parse.errorCode = MODBUS_REACK_ERROR_NULL;
		
			break;
		
		default:
			//����֧�ֵĹ������б���
			hModBusMsg->parse.errorCode = MODBUS_REACK_ERROR_REG;
			break;
		}
	
		break;
	case ModBus_TYPE_ASCII:
		break;
	case ModBus_TYPE_TCP:
		break;
	}
	return pack;
}


/*************************************************
��������:ModBus_ParseReplyPack()

��������:��������ģʽ�·������ݰ�

���ú����嵥: 

������������Դ: 

�������˵��:	ModBus_Msg_TypeDef * hModBusMsg 
								����:�ӻ���ַ�������롢�Ĵ�����ʼ��ַ���Ĵ�������(��ѡ)��ֵ(��ѡ)
								������packDataָ���Ӧ�������ݣ�packLen���ݳ���
							ModBus_Type_enum msgType
								��Ϣ����
							
�������˵��: uint16_t * packLen
								�����ֽ����ĳ���

����ֵ˵��: �������ɵ���Ϣ�ֽ���ָ�룬��Ҫ�ɽ����������ͷţ����ΪNULL������Ϊ�޷������ռ������������

��ע:
*************************************************/
ModBus_ErrorAck_enum ModBus_ParseReplyPack( ModBus_Msg_TypeDef * hModBusMsg, ModBus_Type_enum msgType)
{
	int result = -1;
	uint16_t i;
	
	switch( msgType )
	{
	case ModBus_TYPE_RTU:
		//��С�����ж�
		if( hModBusMsg->packLen < MODBUS_RTU_REPLY_PACKLEN_MIN )
			break;
		//CRCУ��
		if( 0 != CRC16( hModBusMsg->packData, hModBusMsg->packLen ))
			break;
		//��ʼ����
		
		if( ( hModBusMsg->parse.slaveId != (hModBusMsg->packData)[0] ) ||\
				( ( hModBusMsg->parse.funCode != ( (hModBusMsg->packData)[1] & 0x7Fu ) ) && \
					!( 	( hModBusMsg->parse.funCode == MODBUS_EXFUN_REPORT_INPUT_MORE) && \
							( ( hModBusMsg->packData)[1] & 0x7Fu ) == MODBUS_EXFUN_REPORT_HOLD_MORE ) ) )	//������������չ��BUG
		{
			break;
		}
		if( (hModBusMsg->packData)[1] & 0x80u )
		{
			//�����뷵��
			if( hModBusMsg->packLen != MODBUS_RTU_REPLY_PACKLEN_ERRORACK_SIZE )
				break;
			hModBusMsg->parse.errorCode = (hModBusMsg->packData)[2];
			result = 0;		//��Ȼ�Ǵ����룬����Ҳ������������������
			break;
		}
		hModBusMsg->parse.errorCode = MODBUS_REACK_ERROR_NULL;
		//ƥ�书����
		switch( hModBusMsg->parse.funCode )
		{
		case MODBUS_FUN_READ_DISOUT:
		case MODBUS_FUN_READ_DISIN:
		case MODBUS_FUN_READ_HOLD:
		case MODBUS_FUN_READ_INPUT:
			//�����ж� �ӻ�+������+�ֽ���+����+CRC
			if( (hModBusMsg->packData)[2] != hModBusMsg->parse.byteLen )
				break;
			if( hModBusMsg->parse.pValue == NULL )
			{
				hModBusMsg->parse.pValue = pvPortMalloc( (hModBusMsg->packData)[2] );
				if( hModBusMsg->parse.pValue == NULL )
					break;
			}
			
			if( hModBusMsg->parse.funCode == MODBUS_FUN_READ_DISOUT || hModBusMsg->parse.funCode == MODBUS_FUN_READ_DISIN )
			{
				memcpy( hModBusMsg->parse.pValue, hModBusMsg->packData + 3, hModBusMsg->parse.byteLen );
			}
			else
			{
				//���ڼĴ������ݣ���Ҫ��С��ת��
				for( i = 0; i < hModBusMsg->parse.byteLen; i += 2)
				{
					(hModBusMsg->parse.pValue)[ i >> 1u] = __ModBus_U16BigToSmall( hModBusMsg->packData + 3 + i );
				}
			}
			
			result = 0;
			break;
			
		case MODBUS_FUN_WRITE_DISOUT:
		case MODBUS_FUN_WRITE_HOLD:
			//д������дָ����ظ�ָ��һģһ��
			if( ( MODBUS_RTU_PACKLEN_WRITE_SIZE != hModBusMsg->packLen ) ||\
					( __ModBus_U16BigToSmall( hModBusMsg->packData + 2 ) != hModBusMsg->parse.regAddrStart ) ||\
					( __ModBus_U16BigToSmall( hModBusMsg->packData + 4 ) != *(hModBusMsg->parse.pValue) ))
				break;
			
			result = 0;
			break;
			
		case MODBUS_FUN_WRITE_DISOUT_MORE:
		case MODBUS_FUN_WRITE_HOLD_MORE:
		case MODBUS_EXFUN_REPORT_DISOUT_MORE:
		case MODBUS_EXFUN_REPORT_DISIN_MORE:
		case MODBUS_EXFUN_REPORT_HOLD_MORE:
		case MODBUS_EXFUN_REPORT_INPUT_MORE:
			if( ( 8 != hModBusMsg->packLen ) ||\
					( __ModBus_U16BigToSmall( hModBusMsg->packData + 2 ) != hModBusMsg->parse.regAddrStart ) ||\
					( __ModBus_U16BigToSmall( hModBusMsg->packData + 4 ) != hModBusMsg->parse.regLen ))
				break;
			
			result = 0;
			break;
		
		default:
			hModBusMsg->parse.errorCode = MODBUS_REACK_ERROR_FUN;		//����֧�ֵĹ������б���
			break;
		}
		break;
		
	case ModBus_TYPE_ASCII:
		break;
	case ModBus_TYPE_TCP:
		break;
	}
	
	return result;
}


/*************************************************
�������ƣ�ModBus_MainTxCom

����������������ʽ���·�ָ��

���ú����嵥: 

������������Դ: 

�������˵��: ModBus_SlaveInit_TypeDef *hSlaveInit
								����RX TX �����ӿڣ�ͨѶʱ���޶�����Ϣ��ʽ����
							ModBus_Msg_TypeDef *hModBusMsg
								�����·����������:�ӻ���ַ�������롢�Ĵ�����ʼ��ַ���Ĵ�������(��ѡ)��ֵ(��ѡ)
								
�������˵��: ModBus_Msg_TypeDef *hModBusMsg
								���������ָ���pValueֵ��

����ֵ˵��: 0�ɹ�ͨѶ������쳣hModBusMsg->parse.errorCode�����쳣�룬��0�շ�ʧ�ܡ�

��ע:
*************************************************/
int ModBus_MainTxCom( ModBus_SlaveInit_TypeDef *hSlaveInit, ModBus_Msg_TypeDef *hModBusMsg)
{
	int result = -1;
	uint8_t *pack = NULL;
	uint16_t packLen = 0;
	TickType_t beginTick = xTaskGetTickCount();
	
	do
	{
		if( hModBusMsg->packData != NULL )
		{
			vPortFree( hModBusMsg->packData );
			hModBusMsg->packData = NULL;
		}
		hModBusMsg->packLen = 0;
		
		pack = ModBus_CreateMainPack( hModBusMsg, hSlaveInit->msgType, &packLen );
		if( pack == NULL )
			break;
		if( 0 != hSlaveInit->fTxPort( pack, packLen, hSlaveInit->timeOutTick + beginTick - xTaskGetTickCount() ))
			break;
		
		if( hSlaveInit->fRxPort != NULL )
		{
			while( hSlaveInit->timeOutTick + beginTick > xTaskGetTickCount() )
			{
				hModBusMsg->packData = hSlaveInit->fRxPort( &(hModBusMsg->packLen), hSlaveInit->timeOutTick + beginTick - xTaskGetTickCount());
				if( hModBusMsg->packData != NULL )
				{
					if( 0 != ModBus_ParseReplyPack( hModBusMsg, hSlaveInit->msgType ) && \
							hModBusMsg->parse.errorCode == MODBUS_REACK_ERROR_NULL)
						continue;		//û�гɹ������������ݰ����п��ܸð����Ƿ�����ͨѶ����ģ������ð�����������
					result = 0;
					break;
				}
			}
		}
		else
		{
			//���rxPort���պ���ָ��Ϊ�գ���Ϊ����Ҫ���շ��أ�ֱ�ӷ��ط��ͳɹ�
			result = 0;
		}
	}
	while(0);
	
	if( hModBusMsg->packData != NULL )
	{
		vPortFree( hModBusMsg->packData );
		hModBusMsg->packData = NULL;
	}
	if( pack != NULL )
		vPortFree( pack );
	
	return result;
}


/*===================================== End of File ===================================*/
