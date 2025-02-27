#include "log.h"
#include "testing.h"

test (log) {
  LOG_TRACE("\nhello\n");
  LOG_DEBUG("hello\n");
  LOG_INFO("hello\n");
  LOG_WARN("hello\n");
  LOG_ERROR("hello\n");
  LOG_CRITICAL("hello\n");
}
