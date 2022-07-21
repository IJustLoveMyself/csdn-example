/**
  ******************************************************************************
  * @file    md_log.h
  * @author  gxf
  * @version V1.0.0
  * @date    2021.09.06
  * @brief   小远机器人日志打印接口文档
 ==============================================================================
 */
#include "bsp_uart.h"
#include "md_log.h"
#include "XiaoyuanConfig.h"
#include <stdio.h> 
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

static unsigned char is_tag_output(const char *tag);
static void gxf_log_simple(const char *format,...);

static unsigned char gxf_log_output_level = LOG_OUTPUT_LEVEL;    /* 输出等级设置 大于该等级的日志可以输出*/
static unsigned char gxf_log_output = LOG_OUTPUT;                /* 输出开关设置 1：开启日志输出 0：关闭日志输出 */
/* 日志输出内容 1：允许输出，0：禁止输出 */
static gxf_log_out_t log_out={
  .level = LOG_CONTENT_LEVEL, 
  .tag   = LOG_CONTENT_TAG,
  .file  = LOG_CONTENT_FILE,
  .func  = LOG_CONTENT_FUNC,
  .line  = LOG_CONTENT_LINE,
};
/* 日志输出等级 */
static const char *log_level_buf[] = {					
  [LOG_LEVEL_DEBUG]    ="[DEBUG]",
  [LOG_LEVEL_INFO]     ="[INFO]",
  [LOG_LEVEL_WARN]     ="[WARNING]",
  [LOG_LEVEL_ERROR]    ="[ERROR]",
  [LOG_LEVEL_ASSERT]   ="[ASSERT]",
};

/* 标签链表的头部节点 */
static _tag_t *headnode;

/**
 * [itoa description]
 * @author Gxf
 * @dateTime 2021-10-25
 * @brief    [description]将数字转换成字符串
 * @note     [description]最多转换5位的数字
 * @param    buf           [description]存储转换后的字符串的地址
 * @param    num           [description]要转化的十进制数
 */
static void itoa(char *buf,int num)
{
  if(num<10)
  {
    buf[0] = num+'0';
    return;
  }
  if(num<100&&num>9)
  {
    buf[0] = num/10+'0';
    buf[1] = num%10+'0';
    return;
  }
  if(num<1000&&num>99)
  {
    buf[0] = num/100+'0';
    buf[1] = num%100/10+'0';
    buf[2] = num%10+'0';
    return;
  }
  if(num<10000&&num>999)
  {
    buf[0] = num/1000+'0';
    buf[1] = num%1000/100+'0';
    buf[2] = num%100/10+'0';
    buf[3] = num%10+'0';
    return;
  }
  if(num<100000&&num>9999)
  {
    buf[0] = num/10000+'0';
    buf[1] = num%10000/1000+'0';
    buf[2] = num%1000/100+'0';
    buf[3] = num%100/10+'0';
    buf[4] = num%10+'0';
    return;
  }
}

/**
 * [gxf_log_usart_send_bytes description]
 * @author Gxf
 * @dateTime 2021-10-25
 * @brief    [description]串口输出函数
 * @note     [description]这里用的平台是GD32的串口，其他平台请重写此函数
 * @param    buf           [description]要串口输出的字符数组
 * @param    len           [description]要输出的长度
 */
static void gxf_log_usart_send_bytes(u8 *buf ,u8 len)
{
  u8 i;
  for(i=0;i<len;i++)
  {
  	usart_data_transmit(LOG_USART, (uint8_t)buf[i]);
    while(RESET == usart_flag_get(LOG_USART, USART_FLAG_TBE));
  }
}
/**
 * [gxf_log_simple description]
 * @brief    [description]Debug 简易日志输出函数.
 * @note     [description]只输出用户提供的字符数组，这种模式输出的日志没有过滤能力
 * @param    format     [description]格式化字符数组.
 * @param    ...		[description]可变函数列表
 * @retval None
 */

static void gxf_log_simple(const char *format,...)
{
  char buf[LOG_BUF_SIZE];
  va_list list;
  va_start(list, format);
  vsnprintf(buf,LOG_BUF_SIZE,format, list);
  va_end(list);
  #ifdef LOG_BY_USART
    printf("%s\n", buf);
  #endif
}

/**
 * @brief  Debug 详细日志输出函数.
 * @note   输出详细的日志信息，包括日志的等级、标签、文件、模块、行号、用户信息
 * @param  level    : 输出日志等级
 * @param  tag      : 输出日志标签
 * @param  file     : 输出日志所在的源文件
 * @param  func     : 输出日志所在的模块
 * @param  line     : 输出日志所在的行号
 * @param  format   : 格式化字符数组.用户信息
 * @param  ...      : 可变函数列表
 * @retval None
 */
void gxf_log_detailed(uint8_t level, const char *tag, const char *file, const char *func,
        const int line, const char *format, ...)
{
  u8 buf[LOG_BUF_SIZE];
  memset(buf,0,sizeof(buf));
  int i = 0,cnt = 0;
  int ret = 0;
  /* 日志输出未打开，退出 */
  if(gxf_log_output == 0)
  	return;
  /* 日志等级未达到允许输出等级 */
  if(level<gxf_log_output_level)
  	return;
  /* 该标签的日志不允许输出 */
  if(is_tag_output(tag) == 0)
  	return;
  /* level 拼接到buf */
  if(log_out.level){
    while(log_level_buf[level][i]!='\0'){
      buf[cnt] = log_level_buf[level][i];
      cnt++;
      i++;
    }
    /* 加入分隔符 */
    buf[cnt] = ':';cnt++; i=0;
	}
  /* tag 拼接到buf */
  if(log_out.tag){
    while(tag[i]!='\0'){
    buf[cnt] = tag[i];
      cnt++;
      i++;
    }
    /* 加入分隔符 */
    buf[cnt] = ' ';cnt++; i=0;
	}
  /* file 拼接到buf */
  if(log_out.file){
    while(file[i]!='\0'){
      buf[cnt] = file[i];
      cnt++;
      i++;	
    }
    /* 加入分隔符 */
    buf[cnt] = ' ';cnt++; i=0;
  }
  /* func 拼接到buf */
  if(log_out.func){
    while(func[i]!='\0'){
      buf[cnt] = func[i];
      cnt++;
      i++;	
    }
    /* 加入分隔符 */
    buf[cnt] = ' ';cnt++; i=0;
    buf[cnt] = 'L';cnt++;
  }
  /* line转换成字符串，然后拼接 */
  if(log_out.line){
    char num[5];
    memset(num,0,5);
    itoa(num,line);
    while(num[i]!='\0'){
    buf[cnt] = num[i];
    cnt++;
    i++;	
    }
    /* 加入分隔符 */
    buf[cnt] = ' ';cnt++; 
  }
  va_list list;
  va_start(list, format);
  ret = vsnprintf((char *)&buf[cnt],LOG_BUF_SIZE,format, list);
  va_end(list);
  #ifdef LOG_BY_USART 
  gxf_log_usart_send_bytes(buf,(cnt+ret+1));
  #endif
}

/**
 * [gxf_log_init description]
 * @author Gxf
 * @dateTime 2021-10-27
 * @brief    [description] 日志模块初始化，主要是初始化一个存储tag的单向链表
 * @note     [description]
 */
void gxf_log_init(void)
{
  headnode = (_tag_t *)malloc(sizeof(_tag_t));
  headnode->tagname = "NO_TAG";
  headnode->output  = 1;
  headnode->tagid   = 0;
  headnode->next    = NULL;
}

/**
 * [gxf_log_append_tag description]
 * @author Gxf
 * @dateTime 2021-10-26
 * @brief    [description] 添加标签;遍历链表，在链表尾部添加
 * @note     [description]
 * @param    s             [description] 字符串标签的地址
 */
void gxf_log_append_tag(char *s)
{
  _tag_t *node = headnode;

  _tag_t *tagnode  = (_tag_t *)malloc(sizeof(_tag_t));
  tagnode->tagname = s;
  tagnode->next    = NULL;
  while(node->next != NULL)
  {
    node = node->next;
  }
  node->next     = tagnode;
  tagnode->tagid = node->tagid+1;
  /* 默认标签的输出开启 */
  tagnode->output= 1; 
}

/**
 * [gxf_log_ouput_level_set description]
 * @author Gxf
 * @dateTime 2021-10-27
 * @brief    [description] 设置允许日志输出的等级
 * @note     [description]
 * @param    level         [description] 等级：0~4
 */
void gxf_log_ouput_level_set(unsigned int level)
{
  gxf_log_output_level = level;
}
/**
 * [gxf_log_output_set description]
 * @author Gxf
 * @dateTime 2021-10-27
 * @brief    [description] 日志是否输出
 * @note     [description]
 * @param    output        [description] 1：开启日志输出 0：关闭日志输出
 */
void gxf_log_output_set(unsigned int output)
{
  gxf_log_output = output;
}

/**
 * [gxf_log_tag_output_set description]
 * @author Gxf
 * @dateTime 2021-10-27
 * @brief    [description] 设置日志标签的输出
 * @note     [description]
 * @param    output        [description] output总共32bit,每一个bit对应一个标签，该bit位为1，则标签允许输出
 */
void gxf_log_tag_output_set(unsigned int flag)
{
  _tag_t *node = headnode;
  while(node != NULL)
  {
  	/* tagid 从0 开始一次递增，且唯一
  	例如 tagid = 5 ,则该tag对应flag的bit5,bit5为1，则该tag的output置1 */
  	node->output = (flag>>node->tagid)&0x01;
  	node = node->next;
  }
}

/**
 * [gxf_log_tag_get description]
 * @author Gxf
 * @dateTime 2021-10-27
 * @brief    [description] 获取回复上位机的标签拼接数组
 * @note     [description]
 * @param    data          [description] 存放标签拼接数组的结构体
 */
void gxf_log_tag_get(void)
{
	char buf[200];
	unsigned char cnt = 0;
	unsigned char i   =0;	
  _tag_t *node      = headnode;
  while(node != NULL)
  {
    while(node->tagname[i]!='\0')
    {
      buf[cnt] = node->tagname[i];
      cnt++;
      i++;
    }
    i = 0;
    buf[cnt] = '*';
    cnt++;
    buf[cnt] = node->tagid;
    cnt++;
    buf[cnt] = '#';
    cnt++;
  }
  #ifdef LOG_BY_USART 
  gxf_log_usart_send_bytes((u8 *)buf,cnt);
  #endif
}
/**
 * [is_tag_output description]
 * @author Gxf
 * @dateTime 2021-10-27
 * @brief    [description] 判断tag是否允许输出
 * @note     [description]
 * @param    tag           [description] 要判断的tag,由字母和下划线组成
 */
static unsigned char is_tag_output(const char *tag)
{
  _tag_t *node = headnode;
  while(node != NULL)
  {
    if(strcmp(tag,node->tagname) == 0)
    {
  	  break;
    }
    node = node->next;
  }
  return node->output;
}

void gxf_log_content_select(unsigned int data)
{
  log_out.level = data&0x01;
  log_out.tag   = (data>>1)&0x01;
  log_out.file  = (data>>2)&0x01;
  log_out.func  = (data>>3)&0x01;
  log_out.line  = (data>>4)&0x01;                                                                              
}
