#include "ArduiEmulator.hpp"
#include "NamedPipes.h"
#include "Adafruit_GFX.h"

#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef _swap_int16_t
#define _swap_int16_t(a, b)                                                    \
  {                                                                            \
    int16_t t = a;                                                             \
    a = b;                                                                     \
    b = t;                                                                     \
  }
#endif

void hexToRGB(uint16_t hexValue, byte *pr, byte *pg, byte *pb)
{
  if (hexValue == 1)
  {
    *pr = 255;
    *pg = 255;
    *pb = 255;

    return;
  }

  int r = ((hexValue >> 11) & 0x1F);  // Extract the 5 R bits
  int g = ((hexValue >> 5) & 0x3F);   // Extract the 6 G bits
  int b = ((hexValue) & 0x1F);        // Extract the 5 B bits

  *pr = ((r * 255) / 31);
  *pg = ((g * 255) / 63);
  *pb = ((b * 255) / 31);
}

/**************************************************************************/
/*!
   @brief    Instatiate a GFX context for graphics! Can only be done by a
   superclass
   @param    w   Display width, in pixels
   @param    h   Display height, in pixels
*/
/**************************************************************************/
Adafruit_GFX::Adafruit_GFX(int16_t w, int16_t h) : WIDTH(w), HEIGHT(h) {
  _width = WIDTH;
  _height = HEIGHT;
  rotation = 0;
  cursor_y = cursor_x = 0;
  textsize_x = textsize_y = 1;
  textcolor = textbgcolor = 0xFFFF;
  wrap = true;
  _cp437 = false;

  this->memo = "";

  CString str;
  str.Format(_T("BG %d %d"), (int)w, (int)h);
  NamedPipesSend(MessagesTypes::GraphicMessage, str);
}

/**********************************************************************/
/*!
  @brief  Set text cursor location
  @param  x    X coordinate in pixels
  @param  y    Y coordinate in pixels
*/
/**********************************************************************/
void Adafruit_GFX::setCursor(int16_t x, int16_t y) 
{
  CString str;
  str.Format(_T("PR %d %d"), (int)x, (int)y);
  NamedPipesSend(MessagesTypes::GraphicMessage, str);
  this->cursor_x = x;
  this->cursor_y = y;
}

/**********************************************************************/
/*!
  @brief   Set text font color with transparant background
  @param   c   16-bit 5-6-5 Color to draw text with
  @note    For 'transparent' background, background and foreground
           are set to same color rather than using a separate flag.
*/
/**********************************************************************/
void Adafruit_GFX::setTextColor(uint16_t color)
{
  CString str;
  byte r, g, b;
  hexToRGB(color, &r, &g, &b);
  str.Format(_T("TC %d %d %d"), (int)r, (int)g, (int)b);
  NamedPipesSend(MessagesTypes::GraphicMessage, str);
}

/**************************************************************************/
/*!
   @brief    Fill a rectangle completely with one color. Update in subclasses if
   desired!
    @param    x   Top left corner x coordinate
    @param    y   Top left corner y coordinate
    @param    w   Width in pixels
    @param    h   Height in pixels
   @param    color 16-bit 5-6-5 Color to fill with
*/
/**************************************************************************/
void Adafruit_GFX::fillRect(int16_t x, int16_t y, int16_t w, int16_t h,
                            uint16_t color) {
  CString str;
  byte r, g, b;
  hexToRGB(color, &r, &g, &b);
  str.Format(_T("RC %d %d %d %d %d %d %d %d %d %d"), (int)x, (int)y, (int)w, (int)h, (int)r, (int)g, (int)b, (int)r, (int)g, (int)b);
  NamedPipesSend(MessagesTypes::GraphicMessage, str);
}

/**************************************************************************/
/*!
   @brief    Fill the screen completely with one color. Update in subclasses if
   desired!
    @param    color 16-bit 5-6-5 Color to fill with
*/
/**************************************************************************/
void Adafruit_GFX::fillScreen(uint16_t color) {
  fillRect(0, 0, _width, _height, color);
}

/**************************************************************************/
/*!
   @brief    Draw a line
    @param    x0  Start point x coordinate
    @param    y0  Start point y coordinate
    @param    x1  End point x coordinate
    @param    y1  End point y coordinate
    @param    color 16-bit 5-6-5 Color to draw with
*/
/**************************************************************************/
void Adafruit_GFX::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
                            uint16_t color) 
{
  CString str;
  byte r, g, b;
  hexToRGB(color, &r, &g, &b);
  str.Format(_T("LI %d %d %d %d %d %d %d"), (int)x0, (int)y0, (int)x1, (int)y1, (int)r, (int)g, (int)b);
  NamedPipesSend(MessagesTypes::GraphicMessage, str);
}

/**************************************************************************/
/*!
   @brief    Draw a circle outline
    @param    x0   Center-point x coordinate
    @param    y0   Center-point y coordinate
    @param    r   Radius of circle
    @param    color 16-bit 5-6-5 Color to draw with
*/
/**************************************************************************/
void Adafruit_GFX::drawCircle(int16_t x0, int16_t y0, int16_t rad,
                              uint16_t color) {
  CString str;
  byte r, g, b;
  hexToRGB(color, &r, &g, &b);
  str.Format(_T("LI %d %d %d %d %d %d"), (int)x0, (int)y0, (int)rad, (int)r, (int)g, (int)b);
  NamedPipesSend(MessagesTypes::GraphicMessage, str);
}

/**************************************************************************/
/*!
   @brief   Draw a rectangle with no fill color
    @param    x   Top left corner x coordinate
    @param    y   Top left corner y coordinate
    @param    w   Width in pixels
    @param    h   Height in pixels
    @param    color 16-bit 5-6-5 Color to draw with
*/
/**************************************************************************/
void Adafruit_GFX::drawRect(int16_t x, int16_t y, int16_t w, int16_t h,
                            uint16_t color) 
{
  CString str;
  byte r, g, b;
  hexToRGB(color, &r, &g, &b);
  str.Format(_T("RC %d %d %d %d %d %d %d"), (int)x, (int)y, (int)w, (int)h, (int)r, (int)g, (int)b);
  NamedPipesSend(MessagesTypes::GraphicMessage, str);
}

/**************************************************************************/
/*!
   @brief   Draw a rounded rectangle with no fill color
    @param    x   Top left corner x coordinate
    @param    y   Top left corner y coordinate
    @param    w   Width in pixels
    @param    h   Height in pixels
    @param    r   Radius of corner rounding
    @param    color 16-bit 5-6-5 Color to draw with
*/
/**************************************************************************/
void Adafruit_GFX::drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h,
                                 int16_t rad, uint16_t color) {
  CString str;
  byte r, g, b;
  hexToRGB(color, &r, &g, &b);
  str.Format(_T("RR %d %d %d %d %d %d %d %d"), (int)x, (int)y, (int)w, (int)h, (int)rad, (int)r, (int)g, (int)b);
  NamedPipesSend(MessagesTypes::GraphicMessage, str);
}

/**************************************************************************/
/*!
   @brief   Draw a rounded rectangle with fill color
    @param    x   Top left corner x coordinate
    @param    y   Top left corner y coordinate
    @param    w   Width in pixels
    @param    h   Height in pixels
    @param    r   Radius of corner rounding
    @param    color 16-bit 5-6-5 Color to draw/fill with
*/
/**************************************************************************/
void Adafruit_GFX::fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h,
                                 int16_t rad, uint16_t color) 
{
  CString str;
  byte r, g, b;
  hexToRGB(color, &r, &g, &b);
  str.Format(_T("RR %d %d %d %d %d %d %d %d %d %d %d"), (int)x, (int)y, (int)w, (int)h, (int)rad, (int)r, (int)g, (int)b, (int)r, (int)g, (int)b);
  NamedPipesSend(MessagesTypes::GraphicMessage, str);
}

/**************************************************************************/
/*!
   @brief   Draw a triangle with no fill color
    @param    x0  Vertex #0 x coordinate
    @param    y0  Vertex #0 y coordinate
    @param    x1  Vertex #1 x coordinate
    @param    y1  Vertex #1 y coordinate
    @param    x2  Vertex #2 x coordinate
    @param    y2  Vertex #2 y coordinate
    @param    color 16-bit 5-6-5 Color to draw with
*/
/**************************************************************************/
void Adafruit_GFX::drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
                                int16_t x2, int16_t y2, uint16_t color) {
  drawLine(x0, y0, x1, y1, color);
  drawLine(x1, y1, x2, y2, color);
  drawLine(x2, y2, x0, y0, color);
}

// BITMAP / XBITMAP / GRAYSCALE / RGB BITMAP FUNCTIONS ---------------------

BOOL WriteDIB(LPTSTR szFile, HANDLE hDIB)
{
  /*HANDLE hDIB=GlobalAlloc(GPTR, sizeof(hDIBtochange));//this doesn't work, the result is four. Also the HANDLE parameter's name would be changed to hDIBtochange, so that the rest of the function uses the old 'hDIB' throughout
  cout<<endl<<sizeof(hDIBtochange);*/
  BITMAPFILEHEADER  hdr;
  LPBITMAPINFOHEADER    lpbi;
  if (!hDIB)
    return FALSE;
  CFile file;
  if (!file.Open(szFile, CFile::modeWrite | CFile::modeCreate))
    return FALSE;
  lpbi = (LPBITMAPINFOHEADER)hDIB;
  int nColors = 1 << lpbi->biBitCount;
  // Fill in the fields of the file header 
  hdr.bfType = ((WORD)('M' << 8) | 'B');    // is always "BM"
  hdr.bfSize = (DWORD) (GlobalSize(hDIB) + sizeof(hdr));
  hdr.bfReserved1 = 0;
  hdr.bfReserved2 = 0;
  hdr.bfOffBits = (DWORD)(sizeof(hdr) + lpbi->biSize + nColors * sizeof(RGBQUAD));
  // Write the file header 
  file.Write(&hdr, sizeof(hdr));
  // Write the DIB header and the bits 
  file.Write(lpbi, (UINT) GlobalSize(hDIB));
  return TRUE;
}

bool WriteBmp1bpp(LPWSTR szFile, int width, int height, const uint8_t bitmap[])
{
  FILE* f;
  unsigned char* img = NULL;
  int filesize = 54 + 3 * width * height;  //w is your image width, h is image height, both int

  img = (unsigned char*)malloc(3 * width * height);
  memset(img, 0, 3 * width * height);

  for (int i = 0; i < width; i++)
  {
    for (int j = 0; j < height; j++)
    {
      byte x = i; 
      byte y = (height - 1) - j;

      int posBit = (j * width) + i;
      int posByte = (posBit / 8);
      int bit = posBit - (posByte * 8);

      byte color = (posByte & (1 << bit)) > 0 ? 1 : 0;

      byte r = color * 255;
      if (r > 255) r = 255;
      img[(x + y * width) * 3 + 2] = (unsigned char)(r);
      img[(x + y * width) * 3 + 1] = (unsigned char)(r);
      img[(x + y * width) * 3 + 0] = (unsigned char)(r);
    }
  }

  unsigned char bmpfileheader[14] = { 'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0 };
  unsigned char bmpinfoheader[40] = { 40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0 };
  unsigned char bmppad[3] = { 0,0,0 };

  bmpfileheader[2] = (unsigned char)(filesize);
  bmpfileheader[3] = (unsigned char)(filesize >> 8);
  bmpfileheader[4] = (unsigned char)(filesize >> 16);
  bmpfileheader[5] = (unsigned char)(filesize >> 24);

  bmpinfoheader[4] = (unsigned char)(width);
  bmpinfoheader[5] = (unsigned char)(width >> 8);
  bmpinfoheader[6] = (unsigned char)(width >> 16);
  bmpinfoheader[7] = (unsigned char)(width >> 24);
  bmpinfoheader[8] = (unsigned char)(height);
  bmpinfoheader[9] = (unsigned char)(height >> 8);
  bmpinfoheader[10] = (unsigned char)(height >> 16);
  bmpinfoheader[11] = (unsigned char)(height >> 24);

  _wfopen_s(&f, szFile, _T("wb"));
  fwrite(bmpfileheader, 1, 14, f);
  fwrite(bmpinfoheader, 1, 40, f);
  for (int i = 0; i < height; i++)
  {
    fwrite(img + (width * (height - i - 1) * 3), 3, width, f);
    fwrite(bmppad, 1, (4 - (width * 3) % 4) % 4, f);
  }

  free(img);
  fclose(f);

  return true;
}

/**************************************************************************/
/*!
   @brief      Draw a PROGMEM-resident 1-bit image at the specified (x,y)
   position, using the specified foreground color (unset bits are transparent).
    @param    x   Top left corner x coordinate
    @param    y   Top left corner y coordinate
    @param    bitmap  byte array with monochrome bitmap
    @param    w   Width of bitmap in pixels
    @param    h   Height of bitmap in pixels
    @param    color 16-bit 5-6-5 Color to draw with
*/
/**************************************************************************/
void Adafruit_GFX::drawBitmap(int16_t x, int16_t y, const uint8_t bitmap[],
  int16_t w, int16_t h, uint16_t color) 
{
  //HBITMAP bitmap1bpp = CreateBitmap(w, h, 1, 1, bitmap);

  CString mess;
  wchar_t temppath[MAX_PATH + 1];
  GetTempPath(MAX_PATH + 1, temppath);
  GetLongPathName(temppath, temppath, MAX_PATH + 1);

  wchar_t tempfile[MAX_PATH + 1];
  GetTempFileName(temppath, _T("ardbitmap"), 0, tempfile);

  if (WriteBmp1bpp(tempfile, w, h, bitmap) == false)
  {
    printf("file couldn't be opened\n");
    exit(1);
  }

/*
  FILE* fp;
  _wfopen_s(&fp, tempfile, _T("wb"));

  if (fp == NULL) {
    printf("file couldn't be opened\n");
    exit(1);
  }

  fwrite(bitmap, 1, (w*h) / 8, fp);
  fclose(fp);
 */

  byte r, g, b;
  hexToRGB(color, &r, &g, &b);
  mess.AppendFormat(_T("BMP %d %d %d %d %d %d %d \"%s\""), x, y, w, h, r, g ,b, tempfile);
  NamedPipesSend(MessagesTypes::GraphicMessage, mess);
}

size_t Adafruit_GFX::printMemo()
{
  CString mess;
  mess.AppendFormat(_T("PR %d %d \"%s\""), this->cursor_x, this->cursor_y, this->memo);
  NamedPipesSend(MessagesTypes::GraphicMessage, mess);

  this->memo = "";
  return mess.GetLength();
}

size_t  Adafruit_GFX::print(const char line[])
{
  this->memo.Append(CString(line));
  return strlen(line);
}

size_t  Adafruit_GFX::println(const char line[])
{
  this->memo.Append(CString(line));
  printMemo();
  return strlen(line);
}

size_t  Adafruit_GFX::print(const CString& line)
{
  this->memo.Append(CString(line));
  return line.GetLength();
}

size_t  Adafruit_GFX::println(const CString& line)
{
  this->memo.Append(CString(line));
  printMemo();
  return line.GetLength();
}

size_t  Adafruit_GFX::print(const String& line)
{
  this->memo.Append(CString(line.c_str()));
  return line.length();
}

size_t  Adafruit_GFX::println(const String& line)
{
  this->memo.Append(CString(line.c_str()));
  printMemo();
  return line.length();
}

size_t  Adafruit_GFX::print(char value)
{
  size_t size = this->memo.GetLength();
  this->memo.Append(CString(value));
  return this->memo.GetLength() - size;
}

size_t  Adafruit_GFX::print(int value)
{
  return print(value, DEC);
}

size_t  Adafruit_GFX::print(int value, int i)
{
  CString str;
  switch (i)
  {
  case DEC:
    str.Format(_T("%d"), value);
    print(str);
    break;
  case HEX:
    str.Format(_T("%x"), value);
    print(str);
    break;
  case BIN:
    str.Format(_T("%d"), value);
    print(str);
    break;
  }

  return str.GetLength();
}

size_t  Adafruit_GFX::println(int value)
{
  size_t size = print(value, DEC);
  println("");
  return size;
}

size_t  Adafruit_GFX::println(int value, int i)
{
  size_t size = print(value, i);
  println("");
  return size;
}

size_t  Adafruit_GFX::print(IPAddress inIp)
{
  CString str;
  str.Format(_T("%d.%d.%d.%d"), inIp[0], inIp[1], inIp[2], inIp[3]);
  print(str);
  return  str.GetLength();
}

size_t  Adafruit_GFX::println(IPAddress inIp)
{
  size_t size = print(inIp);
  println("");
  return size;
}

size_t Adafruit_GFX::printf(const char* format, ...)
{
  va_list argsList;
  char buffer[255];

  va_start(argsList, format);
  vsprintf_s(buffer, 255, format, argsList);
  va_end(argsList);
  print(buffer);
  return strlen(buffer);
}


#if 0
/***************************************************************************/

/**************************************************************************/
/*!
   @brief    Create a simple drawn button UI element
*/
/**************************************************************************/
Adafruit_GFX_Button::Adafruit_GFX_Button(void) { _gfx = 0; }

/**************************************************************************/
/*!
   @brief    Initialize button with our desired color/size/settings
   @param    gfx     Pointer to our display so we can draw to it!
   @param    x       The X coordinate of the center of the button
   @param    y       The Y coordinate of the center of the button
   @param    w       Width of the buttton
   @param    h       Height of the buttton
   @param    outline  Color of the outline (16-bit 5-6-5 standard)
   @param    fill  Color of the button fill (16-bit 5-6-5 standard)
   @param    textcolor  Color of the button label (16-bit 5-6-5 standard)
   @param    label  Ascii string of the text inside the button
   @param    textsize The font magnification of the label text
*/
/**************************************************************************/
// Classic initButton() function: pass center & size
void Adafruit_GFX_Button::initButton(Adafruit_GFX *gfx, int16_t x, int16_t y,
                                     uint16_t w, uint16_t h, uint16_t outline,
                                     uint16_t fill, uint16_t textcolor,
                                     char *label, uint8_t textsize) {
  // Tweak arguments and pass to the newer initButtonUL() function...
  initButtonUL(gfx, x - (w / 2), y - (h / 2), w, h, outline, fill, textcolor,
               label, textsize);
}

/**************************************************************************/
/*!
   @brief    Initialize button with our desired color/size/settings
   @param    gfx     Pointer to our display so we can draw to it!
   @param    x       The X coordinate of the center of the button
   @param    y       The Y coordinate of the center of the button
   @param    w       Width of the buttton
   @param    h       Height of the buttton
   @param    outline  Color of the outline (16-bit 5-6-5 standard)
   @param    fill  Color of the button fill (16-bit 5-6-5 standard)
   @param    textcolor  Color of the button label (16-bit 5-6-5 standard)
   @param    label  Ascii string of the text inside the button
   @param    textsize_x The font magnification in X-axis of the label text
   @param    textsize_y The font magnification in Y-axis of the label text
*/
/**************************************************************************/
// Classic initButton() function: pass center & size
void Adafruit_GFX_Button::initButton(Adafruit_GFX *gfx, int16_t x, int16_t y,
                                     uint16_t w, uint16_t h, uint16_t outline,
                                     uint16_t fill, uint16_t textcolor,
                                     char *label, uint8_t textsize_x,
                                     uint8_t textsize_y) {
  // Tweak arguments and pass to the newer initButtonUL() function...
  initButtonUL(gfx, x - (w / 2), y - (h / 2), w, h, outline, fill, textcolor,
               label, textsize_x, textsize_y);
}

/**************************************************************************/
/*!
   @brief    Initialize button with our desired color/size/settings, with
   upper-left coordinates
   @param    gfx     Pointer to our display so we can draw to it!
   @param    x1       The X coordinate of the Upper-Left corner of the button
   @param    y1       The Y coordinate of the Upper-Left corner of the button
   @param    w       Width of the buttton
   @param    h       Height of the buttton
   @param    outline  Color of the outline (16-bit 5-6-5 standard)
   @param    fill  Color of the button fill (16-bit 5-6-5 standard)
   @param    textcolor  Color of the button label (16-bit 5-6-5 standard)
   @param    label  Ascii string of the text inside the button
   @param    textsize The font magnification of the label text
*/
/**************************************************************************/
void Adafruit_GFX_Button::initButtonUL(Adafruit_GFX *gfx, int16_t x1,
                                       int16_t y1, uint16_t w, uint16_t h,
                                       uint16_t outline, uint16_t fill,
                                       uint16_t textcolor, char *label,
                                       uint8_t textsize) {
  initButtonUL(gfx, x1, y1, w, h, outline, fill, textcolor, label, textsize,
               textsize);
}

/**************************************************************************/
/*!
   @brief    Initialize button with our desired color/size/settings, with
   upper-left coordinates
   @param    gfx     Pointer to our display so we can draw to it!
   @param    x1       The X coordinate of the Upper-Left corner of the button
   @param    y1       The Y coordinate of the Upper-Left corner of the button
   @param    w       Width of the buttton
   @param    h       Height of the buttton
   @param    outline  Color of the outline (16-bit 5-6-5 standard)
   @param    fill  Color of the button fill (16-bit 5-6-5 standard)
   @param    textcolor  Color of the button label (16-bit 5-6-5 standard)
   @param    label  Ascii string of the text inside the button
   @param    textsize_x The font magnification in X-axis of the label text
   @param    textsize_y The font magnification in Y-axis of the label text
*/
/**************************************************************************/
void Adafruit_GFX_Button::initButtonUL(Adafruit_GFX *gfx, int16_t x1,
                                       int16_t y1, uint16_t w, uint16_t h,
                                       uint16_t outline, uint16_t fill,
                                       uint16_t textcolor, char *label,
                                       uint8_t textsize_x, uint8_t textsize_y) {
  _x1 = x1;
  _y1 = y1;
  _w = w;
  _h = h;
  _outlinecolor = outline;
  _fillcolor = fill;
  _textcolor = textcolor;
  _textsize_x = textsize_x;
  _textsize_y = textsize_y;
  _gfx = gfx;
  strncpy(_label, label, 9);
}

/**************************************************************************/
/*!
   @brief    Draw the button on the screen
   @param    inverted Whether to draw with fill/text swapped to indicate
   'pressed'
*/
/**************************************************************************/
void Adafruit_GFX_Button::drawButton(boolean inverted) {
  uint16_t fill, outline, text;

  if (!inverted) {
    fill = _fillcolor;
    outline = _outlinecolor;
    text = _textcolor;
  } else {
    fill = _textcolor;
    outline = _outlinecolor;
    text = _fillcolor;
  }

  uint8_t r = min(_w, _h) / 4; // Corner radius
  _gfx->fillRoundRect(_x1, _y1, _w, _h, r, fill);
  _gfx->drawRoundRect(_x1, _y1, _w, _h, r, outline);

  _gfx->setCursor(_x1 + (_w / 2) - (strlen(_label) * 3 * _textsize_x),
                  _y1 + (_h / 2) - (4 * _textsize_y));
  _gfx->setTextColor(text);
  _gfx->setTextSize(_textsize_x, _textsize_y);
  _gfx->print(_label);
}

/**************************************************************************/
/*!
    @brief    Helper to let us know if a coordinate is within the bounds of the
   button
    @param    x       The X coordinate to check
    @param    y       The Y coordinate to check
    @returns  True if within button graphics outline
*/
/**************************************************************************/
boolean Adafruit_GFX_Button::contains(int16_t x, int16_t y) {
  return ((x >= _x1) && (x < (int16_t)(_x1 + _w)) && (y >= _y1) &&
          (y < (int16_t)(_y1 + _h)));
}

/**************************************************************************/
/*!
   @brief    Query whether the button was pressed since we last checked state
   @returns  True if was not-pressed before, now is.
*/
/**************************************************************************/
boolean Adafruit_GFX_Button::justPressed() { return (currstate && !laststate); }

/**************************************************************************/
/*!
   @brief    Query whether the button was released since we last checked state
   @returns  True if was pressed before, now is not.
*/
/**************************************************************************/
boolean Adafruit_GFX_Button::justReleased() {
  return (!currstate && laststate);
}

// -------------------------------------------------------------------------

// GFXcanvas1, GFXcanvas8 and GFXcanvas16 (currently a WIP, don't get too
// comfy with the implementation) provide 1-, 8- and 16-bit offscreen
// canvases, the address of which can be passed to drawBitmap() or
// pushColors() (the latter appears only in a couple of GFX-subclassed TFT
// libraries at this time).  This is here mostly to help with the recently-
// added proportionally-spaced fonts; adds a way to refresh a section of the
// screen without a massive flickering clear-and-redraw...but maybe you'll
// find other uses too.  VERY RAM-intensive, since the buffer is in MCU
// memory and not the display driver...GXFcanvas1 might be minimally useful
// on an Uno-class board, but this and the others are much more likely to
// require at least a Mega or various recent ARM-type boards (recommended,
// as the text+bitmap draw can be pokey).  GFXcanvas1 requires 1 bit per
// pixel (rounded up to nearest byte per scanline), GFXcanvas8 is 1 byte
// per pixel (no scanline pad), and GFXcanvas16 uses 2 bytes per pixel (no
// scanline pad).
// NOT EXTENSIVELY TESTED YET.  MAY CONTAIN WORST BUGS KNOWN TO HUMANKIND.

/**************************************************************************/
/*!
   @brief    Instatiate a GFX 1-bit canvas context for graphics
   @param    w   Display width, in pixels
   @param    h   Display height, in pixels
*/
/**************************************************************************/
GFXcanvas1::GFXcanvas1(uint16_t w, uint16_t h) : Adafruit_GFX(w, h) {
  uint16_t bytes = ((w + 7) / 8) * h;
  if ((buffer = (uint8_t *)malloc(bytes))) {
    memset(buffer, 0, bytes);
  }
}

/**************************************************************************/
/*!
   @brief    Delete the canvas, free memory
*/
/**************************************************************************/
GFXcanvas1::~GFXcanvas1(void) {
  if (buffer)
    free(buffer);
}

/**************************************************************************/
/*!
    @brief  Draw a pixel to the canvas framebuffer
    @param  x     x coordinate
    @param  y     y coordinate
    @param  color 16-bit 5-6-5 Color to fill with
*/
/**************************************************************************/
void GFXcanvas1::drawPixel(int16_t x, int16_t y, uint16_t color) {
#ifdef __AVR__
  // Bitmask tables of 0x80>>X and ~(0x80>>X), because X>>Y is slow on AVR
  static const uint8_t PROGMEM GFXsetBit[] = {0x80, 0x40, 0x20, 0x10,
                                              0x08, 0x04, 0x02, 0x01},
                               GFXclrBit[] = {0x7F, 0xBF, 0xDF, 0xEF,
                                              0xF7, 0xFB, 0xFD, 0xFE};
#endif

  if (buffer) {
    if ((x < 0) || (y < 0) || (x >= _width) || (y >= _height))
      return;

    int16_t t;
    switch (rotation) {
    case 1:
      t = x;
      x = WIDTH - 1 - y;
      y = t;
      break;
    case 2:
      x = WIDTH - 1 - x;
      y = HEIGHT - 1 - y;
      break;
    case 3:
      t = x;
      x = y;
      y = HEIGHT - 1 - t;
      break;
    }

    uint8_t *ptr = &buffer[(x / 8) + y * ((WIDTH + 7) / 8)];
#ifdef __AVR__
    if (color)
      *ptr |= pgm_read_byte(&GFXsetBit[x & 7]);
    else
      *ptr &= pgm_read_byte(&GFXclrBit[x & 7]);
#else
    if (color)
      *ptr |= 0x80 >> (x & 7);
    else
      *ptr &= ~(0x80 >> (x & 7));
#endif
  }
}

/**************************************************************************/
/*!
    @brief  Fill the framebuffer completely with one color
    @param  color 16-bit 5-6-5 Color to fill with
*/
/**************************************************************************/
void GFXcanvas1::fillScreen(uint16_t color) {
  if (buffer) {
    uint16_t bytes = ((WIDTH + 7) / 8) * HEIGHT;
    memset(buffer, color ? 0xFF : 0x00, bytes);
  }
}

/**************************************************************************/
/*!
   @brief    Instatiate a GFX 8-bit canvas context for graphics
   @param    w   Display width, in pixels
   @param    h   Display height, in pixels
*/
/**************************************************************************/
GFXcanvas8::GFXcanvas8(uint16_t w, uint16_t h) : Adafruit_GFX(w, h) {
  uint32_t bytes = w * h;
  if ((buffer = (uint8_t *)malloc(bytes))) {
    memset(buffer, 0, bytes);
  }
}

/**************************************************************************/
/*!
   @brief    Delete the canvas, free memory
*/
/**************************************************************************/
GFXcanvas8::~GFXcanvas8(void) {
  if (buffer)
    free(buffer);
}

/**************************************************************************/
/*!
    @brief  Draw a pixel to the canvas framebuffer
    @param  x   x coordinate
    @param  y   y coordinate
    @param  color 16-bit 5-6-5 Color to fill with
*/
/**************************************************************************/
void GFXcanvas8::drawPixel(int16_t x, int16_t y, uint16_t color) {
  if (buffer) {
    if ((x < 0) || (y < 0) || (x >= _width) || (y >= _height))
      return;

    int16_t t;
    switch (rotation) {
    case 1:
      t = x;
      x = WIDTH - 1 - y;
      y = t;
      break;
    case 2:
      x = WIDTH - 1 - x;
      y = HEIGHT - 1 - y;
      break;
    case 3:
      t = x;
      x = y;
      y = HEIGHT - 1 - t;
      break;
    }

    buffer[x + y * WIDTH] = color;
  }
}

/**************************************************************************/
/*!
    @brief  Fill the framebuffer completely with one color
    @param  color 16-bit 5-6-5 Color to fill with
*/
/**************************************************************************/
void GFXcanvas8::fillScreen(uint16_t color) {
  if (buffer) {
    memset(buffer, color, WIDTH * HEIGHT);
  }
}

void GFXcanvas8::writeFastHLine(int16_t x, int16_t y, int16_t w,
                                uint16_t color) {

  if ((x >= _width) || (y < 0) || (y >= _height))
    return;
  int16_t x2 = x + w - 1;
  if (x2 < 0)
    return;

  // Clip left/right
  if (x < 0) {
    x = 0;
    w = x2 + 1;
  }
  if (x2 >= _width)
    w = _width - x;

  int16_t t;
  switch (rotation) {
  case 1:
    t = x;
    x = WIDTH - 1 - y;
    y = t;
    break;
  case 2:
    x = WIDTH - 1 - x;
    y = HEIGHT - 1 - y;
    break;
  case 3:
    t = x;
    x = y;
    y = HEIGHT - 1 - t;
    break;
  }

  memset(buffer + y * WIDTH + x, color, w);
}

/**************************************************************************/
/*!
   @brief    Instatiate a GFX 16-bit canvas context for graphics
   @param    w   Display width, in pixels
   @param    h   Display height, in pixels
*/
/**************************************************************************/
GFXcanvas16::GFXcanvas16(uint16_t w, uint16_t h) : Adafruit_GFX(w, h) {
  uint32_t bytes = w * h * 2;
  if ((buffer = (uint16_t *)malloc(bytes))) {
    memset(buffer, 0, bytes);
  }
}

/**************************************************************************/
/*!
   @brief    Delete the canvas, free memory
*/
/**************************************************************************/
GFXcanvas16::~GFXcanvas16(void) {
  if (buffer)
    free(buffer);
}

/**************************************************************************/
/*!
    @brief  Draw a pixel to the canvas framebuffer
    @param  x   x coordinate
    @param  y   y coordinate
    @param  color 16-bit 5-6-5 Color to fill with
*/
/**************************************************************************/
void GFXcanvas16::drawPixel(int16_t x, int16_t y, uint16_t color) {
  if (buffer) {
    if ((x < 0) || (y < 0) || (x >= _width) || (y >= _height))
      return;

    int16_t t;
    switch (rotation) {
    case 1:
      t = x;
      x = WIDTH - 1 - y;
      y = t;
      break;
    case 2:
      x = WIDTH - 1 - x;
      y = HEIGHT - 1 - y;
      break;
    case 3:
      t = x;
      x = y;
      y = HEIGHT - 1 - t;
      break;
    }

    buffer[x + y * WIDTH] = color;
  }
}

/**************************************************************************/
/*!
    @brief  Fill the framebuffer completely with one color
    @param  color 16-bit 5-6-5 Color to fill with
*/
/**************************************************************************/
void GFXcanvas16::fillScreen(uint16_t color) {
  if (buffer) {
    uint8_t hi = color >> 8, lo = color & 0xFF;
    if (hi == lo) {
      memset(buffer, lo, WIDTH * HEIGHT * 2);
    } else {
      uint32_t i, pixels = WIDTH * HEIGHT;
      for (i = 0; i < pixels; i++)
        buffer[i] = color;
    }
  }
}

/**************************************************************************/
/*!
    @brief  Reverses the "endian-ness" of each 16-bit pixel within the
            canvas; little-endian to big-endian, or big-endian to little.
            Most microcontrollers (such as SAMD) are little-endian, while
            most displays tend toward big-endianness. All the drawing
            functions (including RGB bitmap drawing) take care of this
            automatically, but some specialized code (usually involving
            DMA) can benefit from having pixel data already in the
            display-native order. Note that this does NOT convert to a
            SPECIFIC endian-ness, it just flips the bytes within each word.
*/
/**************************************************************************/
void GFXcanvas16::byteSwap(void) {
  if (buffer) {
    uint32_t i, pixels = WIDTH * HEIGHT;
    for (i = 0; i < pixels; i++)
      buffer[i] = __builtin_bswap16(buffer[i]);
  }
}
#endif
