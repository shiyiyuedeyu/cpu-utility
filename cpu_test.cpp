#include <chrono>
#include <string>
#include <thread>
#include <vector>

#include <sys/time.h>
#include <time.h>
#include <unistd.h>

// #include "glog/logging.h"

struct timeval tvBegin;
struct timeval tvNow;
struct timeval tvReport;

// sleep us
void func(int gap) {
  int busy_time = 1000 * gap;
  while (true) {
    gettimeofday(&tvBegin, NULL);
    while (true) {
      gettimeofday(&tvNow, NULL);
      if (tvNow.tv_usec - tvBegin.tv_usec >= busy_time ||
          tvNow.tv_usec - tvBegin.tv_usec <= (0 - busy_time)) {
        usleep(100000 - busy_time);
        break;
      }
    }
  }
}

int main(int argc, char** argv) {
  // // set log
  // google::InitGoogleLogging(argv[0]);
  // google::SetStderrLogging(google::GLOG_ERROR);  // log level

  //   //  是否将日志输出到 stderr 而非文件。
  //   FLAGS_logtostderr = false;
  //   //  是否将日志输出到文件和 stderr，
  //   //  如果：true，忽略 FLAGS_stderrthreshold 的限制，所有信息打印到终端。
  //   FLAGS_alsologtostderr = false;
  //   //  输出到 stderr 的限值，默认为 2（ERROR），默认 ERORR 以下的信息(INFO、WARNING)不打印到终端
  //   FLAGS_stderrthreshold = google::ERROR;

  //   //  日志的输出目录和前缀
  //   google::SetLogDestination(google::GLOG_INFO, argv[0]);
  //   google::SetLogDestination(google::GLOG_WARNING, argv[0]);
  //   google::SetLogDestination(google::GLOG_ERROR, argv[0]);
  //   google::SetLogDestination(google::GLOG_FATAL, argv[0]);

    std::string thread_num = argv[1];
    std::string gap_us = argv[2];
    if (thread_num == "") {
      thread_num = "1";
    }
    if (gap_us == "") {
      gap_us = "10";
    }
    std::vector<std::thread> thread_pool(std::stoi(thread_num));
    for (int i = 0; i < thread_pool.size(); ++i) {
      thread_pool[i] = std::thread(func, std::stoi(gap_us));
    }
    while (true) {
      sleep(1000);
    }
    for (int i = 0; i < thread_pool.size(); ++i) {
      thread_pool[i].join();
    }

    return 0;
}
