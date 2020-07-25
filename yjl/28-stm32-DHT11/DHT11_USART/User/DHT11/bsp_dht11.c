#include "bsp_dht11.h"

static void DHT11_GPIO_Configuration(void);
static void DHT11_Mode_Out_PP(void);
static void DHT11_Mode_IPU(void);
static uint8_t DHT11_Read_Byte(void);

 /**
  * @brief  DHT11 ��ʼ������
  * @param  ��
  * @retval ��
  */
void DHT11_Init(void)
{
	DHT11_GPIO_Configuration();
	DHT11_Dout_1; 
}

/*
 * ��������DHT11_GPIO_Configuration
 * ����  ������DHT11�õ���I/O��
 * ����  ����
 * ���  ����
 */
static void DHT11_GPIO_Configuration(void)
{
	GPIO_InitTypeDef               GPIO_InitStructure;
	
	/* ���� GPIO ����ʱ�� */
	DHT11_Data_APBxClock_FUN(DHT11_Data_GPIO_CLK,ENABLE);
	
	/*ѡ��Ҫ���Ƶ�DHT11_Dout_GPIO_PORT����*/
	GPIO_InitStructure.GPIO_Pin = DHT11_Data_GPIO_PIN;
	
	/*��������ģʽΪͨ���������*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	
	/*������������Ϊ50MHz */ 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	/* ���ṹ������д�뵽�Ĵ��� */
	GPIO_Init(DHT11_Data_GPIO_PORT,&GPIO_InitStructure);
}

/*
 * ��������DHT11_Mode_IPU
 * ����  ��ʹDHT11-DATA���ű�Ϊ��������ģʽ
 * ����  ����
 * ���  ����
 */
static void DHT11_Mode_IPU(void)
{
		GPIO_InitTypeDef               GPIO_InitStructure;
	
	/*ѡ��Ҫ���Ƶ�DHT11_Dout_GPIO_PORT����*/
	GPIO_InitStructure.GPIO_Pin = DHT11_Data_GPIO_PIN;
	
	/*��������ģʽΪͨ���������*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	
	/* ���ṹ������д�뵽�Ĵ��� */
	GPIO_Init(DHT11_Data_GPIO_PORT,&GPIO_InitStructure);
}

/*
 * ��������DHT11_Mode_Out_PP
 * ����  ��ʹDHT11-DATA���ű�Ϊ�������ģʽ
 * ����  ����
 * ���  ����
 */
static void DHT11_Mode_Out_PP(void)
{
	GPIO_InitTypeDef               GPIO_InitStructure;
	
	/*ѡ��Ҫ���Ƶ�DHT11_Dout_GPIO_PORT����*/	
	GPIO_InitStructure.GPIO_Pin = DHT11_Data_GPIO_PIN;
	
	/*��������ģʽΪͨ���������*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	
	/*������������Ϊ50MHz */ 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	/* ���ṹ������д�뵽�Ĵ��� */
	GPIO_Init(DHT11_Data_GPIO_PORT,&GPIO_InitStructure);
}

/* 
 * ��DHT11��ȡһ���ֽڣ�MSB ��λ����
 * DHT11 ��26~28us�ĸߵ�ƽ��ʾ��0������70us�ߵ�ƽ��ʾ��1����
 * ͨ����� x us��ĵ�ƽ��������������״ ��x ���������ʱ 
 */
static uint8_t DHT11_Read_Byte(void)
{
	uint8_t i,temp = 0;
	
	for(i=0;i<8;i++)
	{
		/*ÿbit��50us�͵�ƽ���ÿ�ʼ����ѯֱ���ӻ����� ��50us �͵�ƽ ����*/  
		while(DHT11_Dout_IN() == Bit_RESET);
		
		Delay_us(40);                                   /* ��ʱx us �����ʱ��Ҫ��������0������ʱ�伴�� */
		
		
		if(DHT11_Dout_IN() == Bit_SET)                  /* x us����Ϊ�ߵ�ƽ��ʾ���ݡ�1�� */
		{
			while(DHT11_Dout_IN() == Bit_SET);            /* �ȴ��ߵ�ƽ����*/
			
			temp |= (uint8_t)((0x01)<<(7-i));             /* ��λ���У������� 1 ���� 7-i λ */
		}
		else
		{
			temp &= (uint8_t)~(0x01<<(7-i));                /* ��λ���У������� 0 ���� 7-i λ */
		}
	}
	return temp;	
}
		
/*
 * һ�����������ݴ���Ϊ40bit����λ�ȳ�
 * 8bit ʪ������ + 8bit ʪ��С�� + 8bit �¶����� + 8bit �¶�С�� + 8bit У��� 
 */
uint8_t DHT11_Read_temperature_humidity(DHT11_Data_TypeDef *DHT11_Data)
{
	DHT11_Mode_Out_PP();                                   /* ����Ϊ���ģʽ */
	
	DHT11_Dout_0;                                          /* ����������ƽ*/
	
	Delay_ms(18);                                          /* �������������ͱ������18���� */
	
	DHT11_Dout_1;                                          /* �������������� 20~40 us*/
	
	Delay_us(30);
	
	DHT11_Mode_IPU();                                      /* ����Ϊ����ģʽ,,�ж��ӻ���Ӧ�ź� */
	 
	/* �жϴӻ��Ƿ��е͵�ƽ��Ӧ�ź� �粻��Ӧ����������Ӧ����������*/   
	/* DHT11���յ������Ŀ�ʼ�źź�, �ȴ�������ʼ�źŽ���,Ȼ����80us�͵�ƽ��Ӧ�ź� */
	if(DHT11_Dout_IN() == Bit_RESET)
	{ 
		while(DHT11_Dout_IN() == Bit_RESET);                 /* �ȴ��͵�ƽ��Ӧ�źŽ��� */
		
	  /*��ѯֱ���ӻ������� 80us �ߵ�ƽ �����źŽ�����׼����ȡ����*/
		while(DHT11_Dout_IN()==Bit_SET);
		
		/* ������ʼ��ȡ���� */
		
		DHT11_Data->humidity_int = DHT11_Read_Byte();             /* ��ȡʪ������λ */
		
		DHT11_Data->humidity_deci = DHT11_Read_Byte();            /* ��ȡʪ��С��λ */
		
		DHT11_Data->temperature_int = DHT11_Read_Byte();          /* ��ȡ�¶�����λ */
		
		DHT11_Data->temperature_deci = DHT11_Read_Byte();         /* ��ȡ�¶�С��λ */
		
		DHT11_Data->check_sum = DHT11_Read_Byte();

    /* ��������Ϊ���ģʽ */		
		DHT11_Mode_Out_PP();
		/* �������� */
		DHT11_Dout_1;
		
		/*У�������Ƿ���ȷ */
		if(DHT11_Data->check_sum == DHT11_Data->humidity_int+DHT11_Data->humidity_deci+DHT11_Data->temperature_int+DHT11_Data->temperature_deci)
		{
			return SUCCESS;
		}
		else
		{
			return ERROR;
		}
	}
	return ERROR;
	
}










