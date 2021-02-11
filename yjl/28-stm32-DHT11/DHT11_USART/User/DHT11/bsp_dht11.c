#include "bsp_dht11.h"

static void DHT11_GPIO_Configuration(void);
static void DHT11_Mode_Out_PP(void);
static void DHT11_Mode_IPU(void);
static uint8_t DHT11_Read_Byte(void);

 /**
  * @brief  DHT11 初始化函数
  * @param  无
  * @retval 无
  */
void DHT11_Init(void)
{
	DHT11_GPIO_Configuration();
	DHT11_Dout_1; 
}

/*
 * 函数名：DHT11_GPIO_Configuration
 * 描述  ：配置DHT11用到的I/O口
 * 输入  ：无
 * 输出  ：无
 */
static void DHT11_GPIO_Configuration(void)
{
	GPIO_InitTypeDef               GPIO_InitStructure;
	
	/* 开启 GPIO 外设时钟 */
	DHT11_Data_APBxClock_FUN(DHT11_Data_GPIO_CLK,ENABLE);
	
	/*选择要控制的DHT11_Dout_GPIO_PORT引脚*/
	GPIO_InitStructure.GPIO_Pin = DHT11_Data_GPIO_PIN;
	
	/*设置引脚模式为通用推挽输出*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	
	/*设置引脚速率为50MHz */ 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	/* 将结构体配置写入到寄存器 */
	GPIO_Init(DHT11_Data_GPIO_PORT,&GPIO_InitStructure);
}

/*
 * 函数名：DHT11_Mode_IPU
 * 描述  ：使DHT11-DATA引脚变为上拉输入模式
 * 输入  ：无
 * 输出  ：无
 */
static void DHT11_Mode_IPU(void)
{
		GPIO_InitTypeDef               GPIO_InitStructure;
	
	/*选择要控制的DHT11_Dout_GPIO_PORT引脚*/
	GPIO_InitStructure.GPIO_Pin = DHT11_Data_GPIO_PIN;
	
	/*设置引脚模式为通用推挽输出*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	
	/* 将结构体配置写入到寄存器 */
	GPIO_Init(DHT11_Data_GPIO_PORT,&GPIO_InitStructure);
}

/*
 * 函数名：DHT11_Mode_Out_PP
 * 描述  ：使DHT11-DATA引脚变为推挽输出模式
 * 输入  ：无
 * 输出  ：无
 */
static void DHT11_Mode_Out_PP(void)
{
	GPIO_InitTypeDef               GPIO_InitStructure;
	
	/*选择要控制的DHT11_Dout_GPIO_PORT引脚*/	
	GPIO_InitStructure.GPIO_Pin = DHT11_Data_GPIO_PIN;
	
	/*设置引脚模式为通用推挽输出*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	
	/*设置引脚速率为50MHz */ 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	/* 将结构体配置写入到寄存器 */
	GPIO_Init(DHT11_Data_GPIO_PORT,&GPIO_InitStructure);
}

/* 
 * 从DHT11读取一个字节，MSB 高位先行
 * DHT11 以26~28us的高电平表示“0”，以70us高电平表示“1”，
 * 通过检测 x us后的电平即可区别这两个状 ，x 即下面的延时 
 */
static uint8_t DHT11_Read_Byte(void)
{
	uint8_t i,temp = 0;
	
	for(i=0;i<8;i++)
	{
		/*每bit以50us低电平标置开始，轮询直到从机发出 的50us 低电平 结束*/  
		while(DHT11_Dout_IN() == Bit_RESET);
		
		Delay_us(40);                                   /* 延时x us 这个延时需要大于数据0持续的时间即可 */
		
		
		if(DHT11_Dout_IN() == Bit_SET)                  /* x us后仍为高电平表示数据“1” */
		{
			while(DHT11_Dout_IN() == Bit_SET);            /* 等待高电平结束*/
			
			temp |= (uint8_t)((0x01)<<(7-i));             /* 高位先行，数据是 1 左移 7-i 位 */
		}
		else
		{
			temp &= (uint8_t)~(0x01<<(7-i));                /* 高位先行，数据是 0 左移 7-i 位 */
		}
	}
	return temp;	
}
		
/*
 * 一次完整的数据传输为40bit，高位先出
 * 8bit 湿度整数 + 8bit 湿度小数 + 8bit 温度整数 + 8bit 温度小数 + 8bit 校验和 
 */
uint8_t DHT11_Read_temperature_humidity(DHT11_Data_TypeDef *DHT11_Data)
{
	DHT11_Mode_Out_PP();                                   /* 主机为输出模式 */
	
	DHT11_Dout_0;                                          /* 拉低主机电平*/
	
	Delay_ms(18);                                          /* 主机把总线拉低必须大于18毫秒 */
	
	DHT11_Dout_1;                                          /* 主机把总线拉高 20~40 us*/
	
	Delay_us(30);
	
	DHT11_Mode_IPU();                                      /* 主机为输入模式,,判读从机响应信号 */
	 
	/* 判断从机是否有低电平响应信号 如不响应则跳出，响应则向下运行*/   
	/* DHT11接收到主机的开始信号后, 等待主机开始信号结束,然后发送80us低电平响应信号 */
	if(DHT11_Dout_IN() == Bit_RESET)
	{ 
		while(DHT11_Dout_IN() == Bit_RESET);                 /* 等待低电平响应信号结束 */
		
	  /*轮询直到从机发出的 80us 高电平 标置信号结束，准备读取数据*/
		while(DHT11_Dout_IN()==Bit_SET);
		
		/* 主机开始读取数据 */
		
		DHT11_Data->humidity_int = DHT11_Read_Byte();             /* 读取湿度整数位 */
		
		DHT11_Data->humidity_deci = DHT11_Read_Byte();            /* 读取湿度小数位 */
		
		DHT11_Data->temperature_int = DHT11_Read_Byte();          /* 读取温度整数位 */
		
		DHT11_Data->temperature_deci = DHT11_Read_Byte();         /* 读取温度小数位 */
		
		DHT11_Data->check_sum = DHT11_Read_Byte();

    /* 将主机设为输出模式 */		
		DHT11_Mode_Out_PP();
		/* 拉高总线 */
		DHT11_Dout_1;
		
		/*校验数据是否正确 */
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










