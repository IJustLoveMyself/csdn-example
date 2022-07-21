/**
  ******************************************************************************
  * @file    md_log.h
  * @author  gxf
  * @version V1.0.0
  * @date    2021.09.06
  * @brief   小远机器人日志打印接口文档
 ==============================================================================
 */
#ifndef _MD_LOG_H_
#define _MD_LOG_H_
#include "gd32f4xx.h" 

#define LOG_LEVEL_ASSERT                      4
#define LOG_LEVEL_ERROR                       3
#define LOG_LEVEL_WARN                        2
#define LOG_LEVEL_INFO                        1
#define LOG_LEVEL_DEBUG                       0

void gxf_log_detailed(uint8_t level, const char *tag, const char *file, const char *func,
        const int line, const char *format, ...);

/* 在其他文件里定义标签的话 需要在md_log.h 之前定义*/					
#ifndef LOG_TAG
  #define LOG_TAG  "NO_TAG"
#endif
#define gxf_log_debug(format,...)       gxf_log_detailed(LOG_LEVEL_DEBUG,LOG_TAG,__FILE__, __FUNCTION__,\
        __LINE__, format,##__VA_ARGS__)
#define gxf_log_info(format,...)        gxf_log_detailed(LOG_LEVEL_INFO,LOG_TAG,__FILE__, __FUNCTION__,\
        __LINE__, format,##__VA_ARGS__)
#define gxf_log_warn(format,...)        gxf_log_detailed(LOG_LEVEL_WARN,LOG_TAG,__FILE__, __FUNCTION__,\
        __LINE__, format,##__VA_ARGS__)
#define gxf_log_error(format,...)       gxf_log_detailed(LOG_LEVEL_ERROR,LOG_TAG,__FILE__, __FUNCTION__,\
        __LINE__, format,##__VA_ARGS__)
#define gxf_log_assert(format,...)      gxf_log_detailed(LOG_LEVEL_ASSERT,LOG_TAG,__FILE__, __FUNCTION__,\
        __LINE__, format,##__VA_ARGS__)
typedef struct{
  char level;    /* 1：输出level信息 0：不输出level信息 */
  char tag;      /* 1：输出tag信息   0：不输出tag信息   */
  char file;     /* 1：输出file信息  0：不输出file信息  */
  char func;     /* 1：输出func信息  0：不输出func信息  */
  char line;     /* 1：输出line信息  0：不输出line信息  */
} gxf_log_out_t; /* 1：输出level信息 0：不输出level信息 */

typedef struct tagnode{
  char output;          /* 包含该标签的日志是否输出 1：标签输出；0：不输出；*/
  char tagid;           /* 标签的ID */
  char *tagname;        /* 标签内容 只能由字母和下划线组成*/
  struct tagnode *next; /* 下一个节点的地址 */
} _tag_t;

typedef struct {
  char          buf[200];        /* 这个结构体是用来定义存放拼接后的标签，目前的标签不多，暂定200，后期不够可以修改 */
  unsigned char len;             /* 数组中占用的长度  */
}data_t;

void gxf_log_tag_output_set(unsigned int flag);
void gxf_log_output_set(unsigned int output);
void gxf_log_ouput_level_set(unsigned int level);
void gxf_log_content_select(unsigned int data);
void gxf_log_tag_get(void);
void gxf_log_append_tag(char *s);
void gxf_log_init(void);
#endif
