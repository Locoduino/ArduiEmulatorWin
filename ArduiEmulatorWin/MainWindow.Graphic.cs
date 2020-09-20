using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.IO;
//using System.Drawing;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Windows;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace ArduiEmulatorWin
{

	// Create a host visual derived from the FrameworkElement class.
	// This class provides layout, event handling, and container support for
	// the child visual objects.
	public class MyVisualHost : FrameworkElement
	{
		public static MyVisualHost currentControl;

		// Create a collection of child visual objects.
		private VisualCollection children;

		public MyVisualHost()
		{
			children = new VisualCollection(this);
			currentControl = this;
		}

		// Create a DrawingVisual that contains a rectangle.
		public DrawingVisual DrawRectangle(Point location, Size size, Brush brush, Pen pen)
		{
			DrawingVisual drawingVisual = new DrawingVisual();

			// Retrieve the DrawingContext in order to create new drawing content.
			DrawingContext drawingContext = drawingVisual.RenderOpen();

			// Create a rectangle and draw it in the DrawingContext.
			Rect rect = new Rect(location, size);
			drawingContext.DrawRectangle(brush, pen, rect);

			// Persist the drawing content.
			drawingContext.Close();

			this.children.Add(drawingVisual);

			return drawingVisual;
		}

		// Create a DrawingVisual that contains a rectangle.
		public DrawingVisual DrawRoundedRectangle(Point location, Size size, UInt16 radius, Brush brush, Pen pen)
		{
			DrawingVisual drawingVisual = new DrawingVisual();

			// Retrieve the DrawingContext in order to create new drawing content.
			DrawingContext drawingContext = drawingVisual.RenderOpen();

			// Create a rectangle and draw it in the DrawingContext.
			Rect rect = new Rect(location, size);
			drawingContext.DrawRoundedRectangle(brush, pen, rect, radius, radius);

			// Persist the drawing content.
			drawingContext.Close();

			this.children.Add(drawingVisual);

			return drawingVisual;
		}

		// Create a DrawingVisual that contains a rectangle.
		public DrawingVisual DrawLine(Point start, Point end, Pen pen)
		{
			DrawingVisual drawingVisual = new DrawingVisual();

			// Retrieve the DrawingContext in order to create new drawing content.
			DrawingContext drawingContext = drawingVisual.RenderOpen();

			// Create a rectangle and draw it in the DrawingContext.
			drawingContext.DrawLine(pen, start, end);

			// Persist the drawing content.
			drawingContext.Close();

			this.children.Add(drawingVisual);

			return drawingVisual;
		}

		// Create a DrawingVisual that contains a circle.
		// if brush not null, draw a filled circle.
		public DrawingVisual DrawCircle(Point center, UInt16 radius, Brush brush, Pen pen)
		{
			DrawingVisual drawingVisual = new DrawingVisual();

			// Retrieve the DrawingContext in order to create new drawing content.
			DrawingContext drawingContext = drawingVisual.RenderOpen();

			// Create a rectangle and draw it in the DrawingContext.
			drawingContext.DrawEllipse(brush, pen, center, radius, radius);

			// Persist the drawing content.
			drawingContext.Close();

			this.children.Add(drawingVisual);

			return drawingVisual;
		}

		// Create a DrawingVisual that contains a rectangle.
		public DrawingVisual DrawText(Point location, string text, Brush brush, int size)
		{
			DrawingVisual drawingVisual = new DrawingVisual();

			DrawingContext drawingContext = drawingVisual.RenderOpen();

			FormattedText formattedText = new FormattedText(text,
				System.Globalization.CultureInfo.CurrentCulture,
				FlowDirection.LeftToRight,
				new Typeface("Segoe UI"),
				size,
				brush,
				null,
				TextFormattingMode.Display);
			drawingContext.DrawText(formattedText, location);

			// Persist the drawing content.
			drawingContext.Close();

			this.children.Add(drawingVisual);

			return drawingVisual;
		}

		// Create a DrawingVisual that contains a bitmap.
		public DrawingVisual DrawMonoBitmap(Point location, Size size, string filename, Pen pen)
		{
			DrawingVisual drawingVisual = new DrawingVisual();

			// Retrieve the DrawingContext in order to create new drawing content.
			DrawingContext drawingContext = drawingVisual.RenderOpen();

			int bitmapSize = (int)(size.Height * size.Width) / 8;

			char[] chardata = new char[bitmapSize * 2];

			int readCount = 0;
			// Create a stream reader object to read a text file.
			using (var reader = new System.IO.StreamReader(filename))
			{
				readCount = reader.ReadBlock(chardata, 0, bitmapSize * 2);
			}

			byte[] data = new byte[readCount];
			for (int i = 0; i < readCount; i++)
			{
				data[i] = (byte)chardata[i]; 
			}

			BitmapImage biImg = new BitmapImage();
			MemoryStream ms = new MemoryStream(data);
			biImg.BeginInit();
			biImg.StreamSource = ms;
			biImg.EndInit();

			ImageSource imgSrc = biImg as ImageSource;

			// Create a rectangle and draw it in the DrawingContext.
			Rect rect = new Rect(location, size);
			drawingContext.DrawImage(imgSrc, rect);

			// Persist the drawing content.
			drawingContext.Close();

			this.children.Add(drawingVisual);

			return drawingVisual;
		}

		public void Clear()
		{
			this.children.Clear();
		}

		// Provide a required override for the VisualChildrenCount property.
		protected override int VisualChildrenCount
		{
			get { return this.children.Count; }
		}

		// Provide a required override for the GetVisualChild method.
		protected override Visual GetVisualChild(int index)
		{
			if (index < 0 || index >= this.children.Count)
			{
				throw new ArgumentOutOfRangeException();
			}

			return this.children[index];
		}
	}

	public class Graphic
	{
		// Top left corner is 0,0 coordinate !

		public int sizex, sizey;
		public int posx, posy;
		public byte textColorR, textColorG, textColorB;
		public byte textSize;
		private bool Display;
		public double scaleFactor;

		public void init(int sizeX, int sizeY)
		{
			ArduinoWindow.MainForm.ShowGraphicArea();

			this.sizex = sizeX;
			this.sizey = sizeY;
			this.scaleFactor = ArduinoWindow.MainForm.ScreenGrid.ActualHeight / sizeY;

			this.posx = 0;
			this.posy = 0;

			this.textColorR = 0;
			this.textColorG = 0;
			this.textColorB = 0;

			this.textSize = 10;

			this.clear();
		}

		Point GetPoint(int x, int y)
		{
			return new Point(x * this.scaleFactor, y * this.scaleFactor);
		}

		Size GetSize(int sizex, int sizey)
		{
			return new Size(sizex * this.scaleFactor, sizey * this.scaleFactor);
		}

		public void clear()
		{
			if (this.sizex == 0)
				return;

			MyVisualHost.currentControl.Clear();

			// Create a rectangle and draw it in the DrawingContext.
			MyVisualHost.currentControl.DrawRectangle(this.GetPoint(0, 0), this.GetSize(this.sizex - 1, this.sizey - 1), Brushes.LightCoral, null);

			this.home();
		}

		public void home()
		{
			this.posx = 0;
			this.posy = 0;
		}

		int write(char ch)
		{
			var str = new StringBuilder();
			str.Append(ch);
			this.printText(this.posx, this.posy, str.ToString());
			return 1;
		}

		public void setCursor(int posX, int posY)
		{
			if (posY >= this.sizey)
			{
				ArduinoWindow.MainForm.debug("move out of the screen !");
				return;
			}

			if (posX >= this.sizex)
			{
				ArduinoWindow.MainForm.debug("move out of the screen !");
				return;
			}

			this.posx = posX;
			this.posy = posY;
		}

		public void printText(int posX, int posY, string inString, Brush brush = null)
		{
			if (posY >= this.sizey)
			{
				ArduinoWindow.MainForm.debug("move out of the screen !");
				return;
			}

			if (posX >= this.sizex)
			{
				ArduinoWindow.MainForm.debug("move out of the screen !");
				return;
			}

			if (brush == null)
			{
				brush = new SolidColorBrush(Color.FromRgb(this.textColorR, this.textColorG, this.textColorB));
			}

			MyVisualHost.currentControl.DrawText(this.GetPoint(posX, posY), inString, brush, (int)(this.textSize * screen.scaleFactor));

			this.posx = posX;
			this.posy = posY;
		}

		static Brush GetBrush(byte r, byte g, byte b)
		{
			var brush = new SolidColorBrush();
			brush.Color = Color.FromRgb(r, g, b);
			return brush;
		}

		static Pen GetPen(byte r, byte g, byte b)
		{
			var brush = new SolidColorBrush();
			brush.Color = Color.FromRgb(r, g, b);
			return new Pen(brush, 1);			
		}

		// A message is a text received from NamedPipes for Lcd print
		// The syntax is :
		// Begin : GRS BG sizex sizey
		//		where sizex is the X pixel size of the graphic part.
		//		where sizey is the Y pixel size of the graphic part.
		// clear : GRS CL
		// home : GRS HOME
		// write : GRS WR 'char'
		//		where char is the character to output at the current cursor position.
		// Print : GRS PR x y "mess"
		//		where row is a row number
		//		where col is a column number
		//		and mess the text to print, surrounded by double quotes. If no text, do a setCursor only.
		// Display : GRS DISP bool
		//		where bool means display if true, or hide (no display) if false;
		// Draw Line : LI x1 y1 x2 y2 penR penG penB
		// Draw Rect : RC x y sizex sizey penR penG penB
		//		draw a rectangle.
		// Draw Rect : RC x y sizex sizey penR penG penB brushR brushG brushB
		//		draw a filled rectangle : pen for outline, brush for content.
		// Draw Rounded Rect : RR x y sizex sizey rad penR penG penB
		//		draw a rounded rectangle.
		// Draw Rounded Rect : RR x y sizex sizey rad penR penG penB brushR brushG brushB
		//		draw a filled rounded rectangle : pen for outline, brush for content.
		// Draw Circle : CI xc yc rad penR penG penB
		//		draw a circle.
		// Draw Circle : CI xc yc rad penR penG penB brushR brushG brushB
		//		draw a filled circle : pen for outline, brush for content.
		// Draw Bitmap : BMP x y sizex sizey "filename" R G B
		//		draw the given monochrome bitmap with given color
		// Set Text Color: TC penR penG penB
		//		set the color for the next text drawing.
		// Print : PR x y "mess" penR penG penB
		//		mess is the text to print, surrounded by double quotes. If no text, do a setCursor only. Is no color, use the current text color.
		// 
		public static bool ParseMessage(string[] inItems)
		{
			Brush brush = null;
			Pen pen;

			// inItems[0] is always 'GRS' .
			switch (inItems[1].ToUpper())
			{
				case "BG":
					if (inItems.Length < 4)
						break;
					if (inItems.Length == 4)
					{
						screen.init(int.Parse(inItems[2]), int.Parse(inItems[3]));
						return true;
					}
					break;

				case "CL":
					screen.clear();
					return true;

				case "HOME":
					screen.home();
					return true;

				case "PR":
					if (inItems.Length < 4)
						break;
					if (inItems.Length == 4)
						screen.setCursor(int.Parse(inItems[2]), int.Parse(inItems[3]));
					else
					{
						if (inItems.Length == 5)
							screen.printText(int.Parse(inItems[2]), int.Parse(inItems[3]), inItems[4].Substring(1, inItems[4].Length - 2));
						else
						{
							if (inItems.Length < 8)
							{
								brush = GetBrush(byte.Parse(inItems[5]), byte.Parse(inItems[6]), byte.Parse(inItems[7]));
								screen.printText(int.Parse(inItems[2]), int.Parse(inItems[3]), inItems[4].Substring(1, inItems[4].Length - 2), brush);
							}
						}
					}
					return true;

				case "DISP":
					if (inItems.Length < 3)
						break;
					int val = int.Parse(inItems[2]);
					return true;

				case "WR":
					if (inItems.Length < 3)
						break;
					int valchar = int.Parse(inItems[2]);
					screen.write((char) valchar);
					return true;

				case "LN":  //line
					if (inItems.Length < 9)
						break;
					pen = GetPen(byte.Parse(inItems[6]), byte.Parse(inItems[7]), byte.Parse(inItems[8]));
					MyVisualHost.currentControl.DrawLine(
						screen.GetPoint(int.Parse(inItems[2]), int.Parse(inItems[3])), 
						screen.GetPoint(int.Parse(inItems[4]), int.Parse(inItems[5])), 
						pen);
					break;

				case "RC":  //Rectangle
					if (inItems.Length < 9)
						break;
					pen = GetPen(byte.Parse(inItems[6]), byte.Parse(inItems[7]), byte.Parse(inItems[8]));
					if (inItems.Length > 11)
						brush = GetBrush(byte.Parse(inItems[9]), byte.Parse(inItems[10]), byte.Parse(inItems[11]));
					MyVisualHost.currentControl.DrawRectangle(
						screen.GetPoint(int.Parse(inItems[2]), int.Parse(inItems[3])),
						screen.GetSize(int.Parse(inItems[4]), int.Parse(inItems[5])),
						brush,
						pen);
					break;

				case "RR":  //Rounded Rectangle
					if (inItems.Length < 10)
						break;
					pen = GetPen(byte.Parse(inItems[7]), byte.Parse(inItems[8]), byte.Parse(inItems[9]));
					if (inItems.Length > 12)
						brush = GetBrush(byte.Parse(inItems[10]), byte.Parse(inItems[11]), byte.Parse(inItems[12]));
					MyVisualHost.currentControl.DrawRoundedRectangle(
						screen.GetPoint(int.Parse(inItems[2]), int.Parse(inItems[3])),
						screen.GetSize(int.Parse(inItems[4]), int.Parse(inItems[5])), 
						(ushort) (ushort.Parse(inItems[6]) * screen.scaleFactor),
						brush,
						pen);
					break;

				case "CI":  //circle
					if (inItems.Length < 8)
						break;
					pen = GetPen(byte.Parse(inItems[5]), byte.Parse(inItems[6]), byte.Parse(inItems[7]));
					if (inItems.Length > 10)
						brush = GetBrush(byte.Parse(inItems[8]), byte.Parse(inItems[9]), byte.Parse(inItems[10]));
					MyVisualHost.currentControl.DrawCircle(
						screen.GetPoint(int.Parse(inItems[2]), int.Parse(inItems[3])),
						(ushort) (ushort.Parse(inItems[4]) * screen.scaleFactor),
						brush,
						pen);
					break;

				case "CU":  //set cursor
					if (inItems.Length < 4)
						break;

					screen.posx = int.Parse(inItems[2]);
					screen.posy = int.Parse(inItems[3]);
					break;

				case "TC":  //text color
					if (inItems.Length < 5)
						break;

					screen.textColorR = byte.Parse(inItems[2]);
					screen.textColorG = byte.Parse(inItems[3]);
					screen.textColorB = byte.Parse(inItems[4]);
					break;

				case "BMP":  //Draw monochrome bitmap
					if (inItems.Length < 10)
						break;
					pen = GetPen(byte.Parse(inItems[6]), byte.Parse(inItems[7]), byte.Parse(inItems[8]));
					MyVisualHost.currentControl.DrawMonoBitmap(
						screen.GetPoint(int.Parse(inItems[2]), int.Parse(inItems[3])),
						new Size(int.Parse(inItems[4]), int.Parse(inItems[5])),
						inItems[9].Substring(1, inItems[9].Length - 2), pen);
					break;

			}

			return false;
		}

		public static Graphic screen = new Graphic();
	}
}
