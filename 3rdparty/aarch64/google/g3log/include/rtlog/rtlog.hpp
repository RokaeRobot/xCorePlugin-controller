#pragma once


#include <ctime>
#include <string>
#include <csignal>
#include <iostream>


#ifdef G3_RT_LOG


struct LEVELS;

namespace rt {




class MsgBuffer{
    
public:
    /**
    * @brief 当前buf的头结点
    */
    char *Front();
    
    /**
    * @brief 当前buf的尾结点
    */
    char *Back();
    
    /**
    * @brief 最后一帧可容纳数据大小
    */
    size_t Capacity();
    
    /**
    * @brief 设置当前最后一帧的有效size
    */
    bool SetSize(size_t sz);
    
    /**
    * @brief MsgBuffer的构造和析构,必须要调用
    */
    bool Init(size_t sz);
    void Deinit();
    
    /**
    * @brief 新建一个节点加入到该buffer里面，当前的front和back会同步变换。
    */
    bool NewBuf(size_t size);
    
    /**
    * @brief 读取数据到str里面，非实时线程调用
    */
    void GetString(std::string &str);
private:
    struct MsgNode{
        char *data;
        size_t size;
        MsgNode *next;
    };
    MsgNode m_head;
    MsgNode *m_cur;
    int m_last_size;
   
};



struct RTLogMsg {
    short level;
    int tid;
    int line;
    unsigned int lost;
    char *file_name;
    MsgBuffer msg_buf;
    struct timeval tv;

    /**
    * @brief 只能通过Create和Destroy创建msg对象
    */
    static RTLogMsg* Create(const char *file, const int line,const LEVELS &level);
    void Destroy();

    void GetMsg(std::string &str){return msg_buf.GetString(str);};
private:
    RTLogMsg(){};
    ~RTLogMsg(){};

};


class  LogStreambuf : public std::streambuf {
public:
    LogStreambuf() :m_buf(nullptr),m_oom(false){}
    void Init(MsgBuffer* buf){
        //第一块buf必须有效否则不写入数据
        if(buf == nullptr ||  buf->Front() == nullptr || buf->Front() > buf->Back()){
            m_oom = true;
            return;
        }
        m_buf = buf;
        m_oom = false;
        setp(m_buf->Front(), m_buf->Back() + 1);
    }
    int_type overflow(int_type ch);
      
    /**
    * @brief 返回的是buf最后一帧数据的有效字数
    */
    size_t pcount() const {return pbase()?static_cast<size_t>(pptr() - pbase()):0; }
    
    char* pbase() const { return m_buf?m_buf->Front():nullptr;}
private:
    MsgBuffer *m_buf;
    bool m_oom;
};

class LogStream : public std::ostream {
   public:
    LogStream(): std::ostream(nullptr){}
    void Init(MsgBuffer *buf){m_streambuf.Init(buf);rdbuf(&m_streambuf);}

    // Legacy std::streambuf methods.
    size_t pcount() const { return m_streambuf.pcount(); }
    char* pbase() const { return m_streambuf.pbase(); }
    char* str() const { return pbase(); }

    LogStream(const LogStream&) = delete;
    LogStream& operator=(const LogStream&) = delete;
private:
    LogStreambuf m_streambuf;
    
};






struct RTLogCapture {
    
    RTLogCapture(const char *file, const int line,const LEVELS &level);
    ~RTLogCapture() ;
    std::ostream& stream(){return log_stream;};
    
#ifdef _MSC_VER 
#	if _MSC_VER >= 1400
#		define G3LOG_FORMAT_STRING _Printf_format_string_
#	else
#		define G3LOG_FORMAT_STRING __format_string
#	endif
       
        void capturef(G3LOG_FORMAT_STRING const char *printf_like_message, ...);
#else
#	define G3LOG_FORMAT_STRING
    
       // Use "-Wall" to generate warnings in case of illegal printf format.
       //      Ref:  http://www.unixwiz.net/techtips/gnu-c-attributes.html
       [[gnu::format(printf, 2, 3)]] void capturef(G3LOG_FORMAT_STRING const char *printf_like_message, ...); // 2,3 ref:  http://www.codemaestro.com/reviews/18
#endif
    //void capturef(const char *printf_like_message, ...);
private:
    RTLogMsg *ptr;
    LogStream log_stream;
};




bool CallerIsRT();
void SetMaxMsgSize(size_t max_size) ;
void SetTaskQueueSize(size_t qsize);




} 




#define SELECT_LOG_STREAM(level,expression) \
(::rt::CallerIsRT()? ::rt::RTLogCapture(__FILE__,__LINE__,level).stream():LogCapture(__FILE__,__LINE__,__PRETTY_FUNCTION__,level,expression).stream())


#define SELECT_LOG_CAPTUREF(level,expression,printf_like_message, ...) \
(::rt::CallerIsRT()? ::rt::RTLogCapture(__FILE__,__LINE__,level).capturef(printf_like_message,##__VA_ARGS__):LogCapture(__FILE__,__LINE__,__PRETTY_FUNCTION__,level,expression).capturef(printf_like_message,##__VA_ARGS__))


#else


#define SELECT_LOG_STREAM(level,expression) \
    LogCapture(__FILE__,__LINE__,__PRETTY_FUNCTION__,level,expression).stream()


#define SELECT_LOG_CAPTUREF(level,expression,printf_like_message, ...) \
    LogCapture(__FILE__,__LINE__,__PRETTY_FUNCTION__,level,expression).capturef(printf_like_message,##__VA_ARGS__)

#endif











