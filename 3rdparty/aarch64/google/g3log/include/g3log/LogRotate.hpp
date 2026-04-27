/** ==========================================================================
* 2011 by KjellKod.cc, modified by Vrecan in https://bitbucket.org/vrecan/g2log-dev
* 2015, adopted by KjellKod for g3log at:https://github.com/KjellKod/g3sinks
*
* This code is PUBLIC DOMAIN to use at your own risk and comes
* with no warranties. This code is yours to share, use and modify with no
* strings attached and no restrictions or obligations.
* ============================================================================*
* PUBLIC DOMAIN and Not copywrited. First published at KjellKod.cc
* ********************************************* */

#pragma once

#include <string>
#include <memory>
#include <vector>
#include "g3log/logmessage.hpp"



struct LogRotateHelper;

/**
* \param log_prefix is the 'name' of the binary, this give the log name 'LOG-'name'-...
* \param log_directory gives the directory to put the log files */
class LogRotate {
    using IgnoreLogLevelsFilter = std::vector<LEVELS>;

  public:
    LogRotate(const LogRotate&) = delete;
    LogRotate& operator=(const LogRotate&) = delete;


    LogRotate(const std::string& log_prefix, \
              const std::string& log_directory, \
              const std::string& logger_id, \
              const std::string &log_ext, \
              const std::string &syslink,  \
              int max_log_size,     \
              int max_log_nubmer,   \
              std::vector<LEVELS> filter);
    virtual ~LogRotate();


    void save(std::string logEnty);

    //use saveLogMessage() as default call for this sink instead of save()
    void saveLogMessage(g3::LogMessageMover message);
    
    std::string changeLogFile(const std::string& log_directory, const std::string& logid ="");
    
    std::string logFileName();

    // here max archive log count means the max number of all log files including current log
    void setMaxArchiveLogCount(int max_size);
    int getMaxArchiveLogCount();
    
    void setFlushPolicy(size_t flush_policy); // 0: never (system auto flush), 1 ... N: every n times
    void flush();


    // After max_file_size_in_bytes the next log entry will trigger log 
    // compression to a gz file and log entries will start fresh
    void setMaxLogSize(int max_file_size_in_bytes);
    int getMaxLogSize();

    //set customized log format. the format we're using now is 
    //[level|月/日 时:分:秒:微秒 线程号 文件名:行号]日志内容，例如：[INFO |05/13 19:55:58.800572 8821 launch.cpp:325]Entering task- browser console...（注意：release版本，不记录文件名和行号）
	void overrideLogDetails(g3::LogMessage::LogDetailsFunc func);

    //set log header
	void overrideLogHeader(const std::string& change);

    bool rotateLog();
    //bool CheckLevel(const     LEVELS &level,const std::string &file_path) const;
    //void OpenModuleLevel(const       LEVELS &level);
    //void CloseModuleLevel(const       LEVELS &level);

  private:
    std::unique_ptr<LogRotateHelper> pimpl_;

    IgnoreLogLevelsFilter _filter;
};


