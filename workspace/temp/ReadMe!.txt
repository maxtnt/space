EEEPC Tool v2 Alpha 1 Build 69 release:

*EXCLAIMER*
The Author nor the Host of this program will be held responsible if it breaks anything.
USE AT YOUR OWN RISK.

To disable functionality like cpu frequency control, fan and/or backlight control edit the
respective fields listed below in Tool.ini:
FreqCtrl=x; //x = 1 - Enable CPU frequency control. x = 0 - Disable
FanCtrl=x; //x = 1 - Enable fan control. x = 0 - Disable
BLCtrl=x; //x = 1 - Enable backlight control. x = 0 - Disable
*Note: If updating from an earlier version of the tool, delete the old Tool.ini before use.


To adjust the OSD settings you simply edit OSD.ini:
TextClr = OSD text color in "BGR" hexadecimal format, ie: FF0000 for Blue and 0000FF for Red.
BGClr = Same as TextClr, currently unused.
OSDPos = 1 - 6:
0 = Defined by OSDPosX and OSDPosY, see below.
1 = Top left.
2 = Top right.
3 = Bottom left.
4 = Bottom right.
5 = Middle left.
6 = Middle right.
Anything else will make it default to the same spot as #2.

OSDPosX = The horizontal (X) position on the screen in pixels;
OSDPosY = The vertical (Y) position on the screen in pixels;
FontName = Name of the font you want to use, keep it like "FontName=;"
if you want the program to use the default system font.

FontSize = Font size

All the other settings are boolean, aka '0' or '1':

FontBold = Make the text bold
FontItalic = Make text Italic
FontUnderline = Add an underline to the text
FontStrikeout = strike out the text

CpuLoad = Display CPU usage.
MemLoad = Display memory usage.
ScrRest = Display current main screen resolution.
ScrBrit = Display current LCD brightness level.
Speed = Display CPU frequency information.
Temp = Display CPU temperature.
Fan = Display fan RPM and duty cycle (in %).
Batt = Display battery information, currently doesn't actually show anything useful.


Instructions for presets:
-------------------------------------------

The presets must be located in a subdirectory named "Presets".
Each preset is going to be in it's own file with a "PRT" extension (like "MyFan.prt"),
each file's name (excluding the ".prt" part) is going to be the preset name in the menu.
The menu will be separated; on the left side will be the default presets and on the right side,
user defined presets will be listed. This of course applies to each section separately.

These are all just samples of how you can create your own presets
-------------------------------------------
Fan:
-------------------------------------------
[Fan Preset]
Type=fan;
PWM=50; Sets the fan speed (in percent), must be between 0 = 100

-------------------------------------------
Backlight:
-------------------------------------------
[code][Backlight Preset]
Type=backlight;
Brightness=204; //80%, very bright. ((% * 255) / 100)

-------------------------------------------
Speed:
-------------------------------------------
[Speed Preset]
Type=speed;
FSB=95;
PCIE=100;
Step=1;
Delay=500;
HighV=1;
-------------------------------------------