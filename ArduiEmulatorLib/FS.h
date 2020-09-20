/*
 FS.h - file system wrapper
 Copyright (c) 2015 Ivan Grokhotkov. All rights reserved.
 This file is part of the esp8266 core for Arduino environment.

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef FS_H
#define FS_H

#include <memory>
#include "Arduino.h"
#include "WString.h"

#define FS_STARTDIR   "./Debug/SPIFFSdir"

namespace fs
{

#define FILE_READ       "r"
#define FILE_WRITE      "w"
#define FILE_APPEND     "a"

class File;

/*class FileImpl;
typedef std::shared_ptr<FileImpl> FileImplPtr;
class FSImpl;
typedef std::shared_ptr<FSImpl> FSImplPtr;
 */
enum SeekMode {
    SeekSet = 0,
    SeekCur = 1,
    SeekEnd = 2
};

class File
{
public:
  File() { this->pFile = NULL; this->filename = ""; }
  File(LPCWSTR path, LPCWSTR mode);
  ~File();

  size_t write(uint8_t val);
  size_t write(const uint8_t* buf, size_t size);
  int available();
  int read();
  int peek();
  void flush();
  size_t read(uint8_t* buf, size_t size);
  size_t readBytes(char* buffer, size_t length);

  bool seek(uint32_t pos, SeekMode mode);
  bool seek(uint32_t pos);
  size_t position() const;
  size_t size();
  void close();
  operator bool() const
  {
    return this->pFile != NULL || hSearch != NULL;
  }
  time_t getLastWrite();
  const char* name() const;

  bool isDirectory(void);
  File openNextFile(const char* mode = FILE_READ);
  void rewindDirectory(void);

  size_t print(const char line[]);
  size_t println(const char line[]);
  size_t print(const String& line);
  size_t println(const String& line);
  size_t print(char value);
  size_t print(int value);
  size_t print(int value, int i);
  size_t println(int value);
  size_t println(int value, int i);
  size_t printf(const char* format, ...);

protected:
    //FileImplPtr _p;

private:
    FILE* pFile;
    bool isDirectoryFlag;

    String filename;
    String directory;
    String memo;

    WIN32_FIND_DATA FileData;
    HANDLE          hSearch;
};

class FS
{
public:
   // FS(FSImplPtr impl) : _impl(impl) { }

    File open(const char* path, const char* mode = FILE_READ);
    File open(const String& path, const char* mode = FILE_READ);

    bool exists(const char* path);
    bool exists(const String& path);

    bool remove(const char* path);
    bool remove(const String& path);

    bool rename(const char* pathFrom, const char* pathTo);
    bool rename(const String& pathFrom, const String& pathTo);

    bool mkdir(const char *path);
    bool mkdir(const String &path);

    bool rmdir(const char *path);
    bool rmdir(const String &path);


protected:
   // FSImplPtr _impl;
};

} // namespace fs

#ifndef FS_NO_GLOBALS
using fs::FS;
using fs::File;
using fs::SeekMode;
using fs::SeekSet;
using fs::SeekCur;
using fs::SeekEnd;
#endif //FS_NO_GLOBALS

#endif //FS_H
