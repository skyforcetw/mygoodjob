object MeasureWindow: TMeasureWindow
  Left = 360
  Top = 190
  BorderStyle = bsNone
  Caption = 'MeasureWindow'
  ClientHeight = 606
  ClientWidth = 860
  Color = clBlack
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  KeyPreview = True
  OldCreateOrder = False
  WindowState = wsMaximized
  OnClose = FormClose
  OnKeyPress = FormKeyPress
  PixelsPerInch = 120
  TextHeight = 16
  object Button1: TButton
    Left = 9
    Top = 9
    Width = 73
    Height = 24
    Caption = 'Test'
    TabOrder = 0
    Visible = False
    OnClick = Button1Click
  end
end