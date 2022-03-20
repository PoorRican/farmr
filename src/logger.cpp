//
// Created by Josue Figueroa on 3/18/22.
//

#include "logger.h"

Logger::Logger(log_mode mode, log_level level)
    : mode(mode), level(level) {
  if (mode != log_mode::Serial) {
    event_f = SD.open(EVENT_fn, FILE_WRITE);
    data_f = SD.open(DATA_fn, FILE_WRITE);
  }
}

Logger::~Logger() {
  if (mode != log_mode::Serial) {
    event_f.close();
    data_f.close();
  }
}

void Logger::data(Sensor::SensName type, double data) {
  data_t datapoint = {now(), type, data};
  log(datapoint);
}

void Logger::warning(const char* s) {
  event_t entry = {now(), log_level::Warning, s};
  log(entry);
}

void Logger::error(const char* s) {
  event_t entry = {now(), log_level::Error, s};
  log(entry);
}

void Logger::debug(const char* s) {
  event_t entry = {now(), log_level::Debug, s};
  log(entry);
}

void Logger::verbose(const char* s) {
  event_t entry = {now(), log_level::Verbose, s};
  log(entry);
}

void Logger::log(event_t &entry) {
  if ((uint8_t)entry.type > (uint8_t)this->level) {
    return;
  }

  char* s = nullptr;
  sprintf(s, "%lu::%d::%s",
          (unsigned long)now(), (uint8_t)entry.type, entry.data);

  if (this->mode != log_mode::Serial) {
    event_f.seek(EOF);
    event_f.write(s);
  }
  if (this->mode != log_mode::File) {
    Serial.println(s);
  }
}

void Logger::log(data_t &entry) {
  if ((uint8_t)entry.type > (uint8_t)this->level) {
    return;
  }

  // write as binary
  if (this->mode != log_mode::Serial) {
    data_f.seek(EOF);
    data_f.write((const uint8_t *)&entry, sizeof(entry));
  }
  if (this->mode != log_mode::File) {
    char* s = nullptr;
    sprintf(s, "%lu::%d::%f",
            (unsigned long)now(), (uint8_t)entry.type, entry.data);
    Serial.println(s);
  }
}
