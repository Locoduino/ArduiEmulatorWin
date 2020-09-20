/*
 FS.cpp - file system wrapper
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

#include "FS.h"
//#include "FSImpl.h"

using namespace fs;

File::File(LPCWSTR path, LPCWSTR mode)
{
  this->isDirectoryFlag = false;

  wchar_t buffer[80];

  wcscpy_s(buffer, 80, TEXT(FS_STARTDIR));
  wcscat_s(buffer, 80, path);

  DWORD dwAttrs = GetFileAttributes(CString(buffer));
  if (dwAttrs != INVALID_FILE_ATTRIBUTES) 
    this->isDirectoryFlag = (dwAttrs & FILE_ATTRIBUTE_DIRECTORY) > 0;

  if (isDirectoryFlag)
  {
    this->directory = String(*path);
    
    wcscpy_s(buffer, 80, TEXT(FS_STARTDIR));
    wcscat_s(buffer, 80, path);
    wcscat_s(buffer, 80, TEXT("/*.*"));

    hSearch = FindFirstFile(buffer, &FileData);
    if (hSearch == INVALID_HANDLE_VALUE)
    {
      printf("No files found.\n");
      hSearch = NULL;
      return;
    }

    bool fileFound = true;
    while (FileData.cFileName[0] == '.' && fileFound)
      fileFound = FindNextFile(hSearch, &FileData);
  }
  else
  {
    CT2A ascii(path);
    _wfopen_s(&(this->pFile), buffer, mode);

    if (this->pFile != NULL)
    {
      this->filename = ascii;
      this->memo.reserve(100);
      this->memo = "";
    }
  }
}

File::~File()
{
  close();
}

size_t File::write(uint8_t val) 
{ 
  if (!*this)
    return 0;

  return fputc(val, this->pFile);
}

size_t File::write(const uint8_t* buf, size_t size) 
{ 
  if (!*this)
    return 0;

  return fwrite(buf, 1, size, this->pFile);
}

int File::available() 
{ 
  if (!*this)
    return 0;

  fpos_t pos;
  fgetpos(this->pFile, &pos); 
  return (int)(size() - pos); 
}

int File::read() 
{ 
  if (! *this)
    return 0;

  uint8_t buf[3];
  return (int) fread(buf, 1, 1, this->pFile); 
}

int File::peek() 
{
  if (!*this)
    return -1;

  uint8_t buf[3];
  fpos_t pos;

  fgetpos(this->pFile, &pos);
  fread(buf, 1, 1, this->pFile);
  fsetpos(this->pFile, &pos);

  return buf[0];
}

void File::flush() 
{ 
  if (!*this)
    return;

  if (this->memo.length() > 0)
  {
    println("");
  }

  fflush(this->pFile); 
  this->memo = "";
}

size_t File::read(uint8_t* buf, size_t size) 
{ 
  if (!*this)
    return 0;

  return fread(buf, 1, size, this->pFile);
}

size_t File::readBytes(char* buffer, size_t length) 
{ 
  if (!*this)
    return 0;

  return fread(buffer, 1, length, this->pFile);
}

bool File::seek(uint32_t pos, SeekMode mode) 
{ 
  if (!*this)
    return false;

  return fseek(this->pFile, pos, 0);
}

bool File::seek(uint32_t pos) 
{ 
  if (!*this)
    return false;

  return seek(pos, SeekMode::SeekCur);
}

size_t File::position() const 
{ 
  if (! *this)
    return -1;

  fpos_t pos;
  fgetpos(this->pFile, &pos); 
  return pos; 
}

size_t File::size() 
{
  struct stat stat_buf;
  char buffer[80];

  strcpy_s(buffer, 80, FS_STARTDIR);
  strcat_s(buffer, 80, this->filename.c_str());

  int rc = stat(buffer, &stat_buf);
  return rc == 0 ? stat_buf.st_size : -1;
}

void File::close() 
{ 
  if (this->pFile != NULL)
  {
    flush();
    fclose(this->pFile);
    this->pFile = NULL;
  }

  hSearch = NULL;
  this->filename = "";
  this->directory = "";
  this->memo = "";
}

time_t File::getLastWrite()
{
  return (time_t)0;
}

const char* File::name() const
{
  return this->filename.c_str();
}

bool File::isDirectory(void)
{
  return this->isDirectoryFlag;
}

File File::openNextFile(const char* mode)
{
  bool fileFound = true;

  fileFound = FindNextFile(hSearch, &FileData);

  if (fileFound)
    _wfopen_s(&(this->pFile), FileData.cFileName, (const wchar_t*)mode);
  else
    hSearch = NULL; // end of scanning !

  return *this;
}

void File::rewindDirectory(void)
{
  wchar_t buffer[80];
  wcscpy_s(buffer, TEXT(FS_STARTDIR));
  wcscat_s(buffer, CString(this->directory.c_str()));
  wcscat_s(buffer, TEXT("/*.*"));

  hSearch = FindFirstFile(buffer, &FileData);
  if (hSearch == INVALID_HANDLE_VALUE)
  {
    printf("No files found.\n");
    hSearch = NULL;
    return;
  }

  bool fileFound = true;
  while (FileData.cFileName[0] == '.' && fileFound)
    fileFound = FindNextFile(hSearch, &FileData);
}

// Print part

size_t  File::print(const char line[])
{
  if (this->memo.length() == 0)
    this->memo = line;
  else
    this->memo += line;
  return strlen(line);
}

size_t  File::println(const char line[])
{
  if (!*this)
    return 0;

  this->memo += line;
  fputs(this->memo.c_str(), this->pFile);
  this->memo = "";
  return strlen(line);
}

size_t  File::print(const String& line)
{
  this->memo += line;
  return line.length();
}

size_t  File::println(const String& line)
{
  return println(line.c_str());
}

size_t  File::print(char value)
{
  size_t size = this->memo.length();
  this->memo += String(value);
  return this->memo.length() - size;
}

size_t  File::print(int value)
{
  return print(value, DEC);
}

size_t  File::print(int value, int i)
{
  String str;
  switch (i)
  {
  case DEC:
    str = String(value);
    print(str);
    break;
  case HEX:
    str = String(value, 16);
    print(str);
    break;
  case BIN:
    str = String(value, 2);
    print(str);
    break;
  }

  return str.length();
}

size_t  File::println(int value)
{
  size_t size = print(value, DEC);
  println("");
  return size;
}

size_t  File::println(int value, int i)
{
  size_t size = print(value, i);
  println("");
  return size;
}

size_t File::printf(const char* format, ...)
{
  va_list args;
  CString str;
  va_start(args, format);
  str.Format(CString(format), args);
  va_end(args);
  CT2A ascii(str);
  print(ascii);
  return str.GetLength();
}

// End of priont part


File FS::open(const char* path, const char* mode)
{
  return File(CString(path), (LPCWSTR) mode);
}

File FS::open(const String& path, const char* mode)
{
  return open(path.c_str(), mode);
}

bool FS::exists(const char* path)
{
  char buffer[80];
  strcpy_s(buffer, 80, FS_STARTDIR);
  strcat_s(buffer, 80, path);

  FILE* file;
  if (fopen_s(&file, buffer, "r")) 
  {
    fclose(file);
    return true;
  }

  return false;
}

bool FS::exists(const String& path)
{
  return exists(path.c_str());
}

bool FS::remove(const char* path)
{
  char buffer[80];
  strcpy_s(buffer, FS_STARTDIR);
  strcat_s(buffer, path);

  return ::remove(buffer) == 0;
}

bool FS::remove(const String& path)
{
  return remove(path.c_str());
}

bool FS::rename(const char* pathFrom, const char* pathTo)
{
  char bufferFrom[80];
  strcpy_s(bufferFrom, FS_STARTDIR);
  strcat_s(bufferFrom, pathFrom);
  char bufferTo[80];
  strcpy_s(bufferTo, FS_STARTDIR);
  strcat_s(bufferTo, pathTo);

  return ::rename(bufferFrom, bufferTo) == 0;
}

bool FS::rename(const String& pathFrom, const String& pathTo)
{
  return rename(pathFrom.c_str(), pathTo.c_str());
}

bool FS::mkdir(const char* path)
{
  wchar_t* wcstring = new wchar_t[80];
  size_t convertedChars = 0;
  mbstowcs_s(&convertedChars, wcstring, 80, FS_STARTDIR, _TRUNCATE);

  wchar_t* buffer = new wchar_t[80]; 
  mbstowcs_s(&convertedChars, buffer, 80, path, _TRUNCATE);
  StrCatW(wcstring, buffer);

  return ::_tmkdir(wcstring) == 0;
}

bool FS::mkdir(const String& path)
{
  return mkdir(path.c_str());
}

bool FS::rmdir(const char* path)
{
  wchar_t* wcstring = new wchar_t[80];
  size_t convertedChars = 0;
  mbstowcs_s(&convertedChars, wcstring, 80, FS_STARTDIR, _TRUNCATE);

  wchar_t* buffer = new wchar_t[80];
  mbstowcs_s(&convertedChars, buffer, 80, path, _TRUNCATE);
  StrCatW(wcstring, buffer);

  return ::_trmdir(wcstring) == 0;
}

bool FS::rmdir(const String& path)
{
  return rmdir(path.c_str());
}
