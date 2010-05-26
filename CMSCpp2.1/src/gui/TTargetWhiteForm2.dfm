object TargetWhiteForm2: TTargetWhiteForm2
  Left = 300
  Top = 300
  Width = 928
  Height = 554
  Caption = 'TargetWhiteForm'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  OnCreate = FormCreate
  OnKeyPress = FormKeyPress
  OnShow = FormShow
  PixelsPerInch = 120
  TextHeight = 16
  object Label3: TLabel
    Left = 560
    Top = 496
    Width = 349
    Height = 16
    Caption = 'Copyright (C) 2010, AU Optronics Corp., All Right Reserved.'
  end
  object PageControl1: TPageControl
    Left = 9
    Top = 9
    Width = 904
    Height = 488
    ActivePage = TabSheet1
    TabIndex = 0
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = 'Target White'
      object GroupBox2: TGroupBox
        Left = 9
        Top = 9
        Width = 240
        Height = 440
        Caption = 'Target Color'
        TabOrder = 0
        object RadioButton_Targetxy: TRadioButton
          Left = 9
          Top = 128
          Width = 167
          Height = 25
          Caption = 'Adjust to Target x,y'
          TabOrder = 1
        end
        object RadioButton_RGBRatio: TRadioButton
          Left = 9
          Top = 41
          Width = 160
          Height = 24
          Caption = 'Adjust by RGB ratio'
          TabOrder = 2
        end
        object Button2: TButton
          Left = 81
          Top = 409
          Width = 80
          Height = 22
          Caption = 'Run'
          TabOrder = 3
          OnClick = Button2Click
        end
        object GroupBox4: TGroupBox
          Left = 25
          Top = 153
          Width = 208
          Height = 152
          Caption = 'Target xy on D-Illuminant Locus'
          TabOrder = 0
          object Label10: TLabel
            Left = 9
            Top = 25
            Width = 6
            Height = 16
            Caption = 'x'
          end
          object Label11: TLabel
            Left = 113
            Top = 25
            Width = 7
            Height = 16
            Caption = 'y'
          end
          object Label2: TLabel
            Left = 105
            Top = 64
            Width = 8
            Height = 16
            Caption = 'K'
          end
          object Label1: TLabel
            Left = 9
            Top = 64
            Width = 18
            Height = 16
            Caption = 'CT'
          end
          object Label5: TLabel
            Left = 9
            Top = 97
            Width = 10
            Height = 16
            Caption = 'u'#39
          end
          object Label6: TLabel
            Left = 112
            Top = 97
            Width = 10
            Height = 16
            Caption = 'v'#39
          end
          object Edit_targetx: TEdit
            Left = 33
            Top = 25
            Width = 72
            Height = 24
            ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
            TabOrder = 0
            Text = '0.2788'
            OnChange = Edit_targetxChange
          end
          object Edit_targety: TEdit
            Left = 129
            Top = 25
            Width = 72
            Height = 24
            ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
            TabOrder = 1
            Text = '0.2920'
            OnChange = Edit_targetyChange
          end
          object Edit_CT: TEdit
            Left = 32
            Top = 57
            Width = 73
            Height = 24
            ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
            TabOrder = 2
            Text = '10000'
            OnChange = Edit_CTChange
          end
          object Edit_up: TEdit
            Left = 32
            Top = 89
            Width = 73
            Height = 24
            Enabled = False
            ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
            TabOrder = 3
            Text = '0.1876'
          end
          object Edit_vp: TEdit
            Left = 128
            Top = 89
            Width = 73
            Height = 24
            Enabled = False
            ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
            TabOrder = 4
            Text = '0.4419'
          end
          object CheckBox_MoreAccurate: TCheckBox
            Left = 9
            Top = 121
            Width = 120
            Height = 24
            Caption = 'More Accurate'
            TabOrder = 5
            Visible = False
          end
        end
        object RadioButton_MaxRGB: TRadioButton
          Left = 9
          Top = 16
          Width = 144
          Height = 25
          Caption = 'Adjust to Max RGB'
          Checked = True
          TabOrder = 4
          TabStop = True
          OnClick = RadioButton_MaxRGBClick
        end
        object GroupBox1: TGroupBox
          Left = 25
          Top = 64
          Width = 208
          Height = 57
          Caption = 'RGB ratio'
          TabOrder = 5
          object Edit_R: TEdit
            Left = 9
            Top = 25
            Width = 40
            Height = 24
            ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
            TabOrder = 0
            Text = '255'
            OnChange = Edit_RChange
          end
          object Edit_G: TEdit
            Left = 57
            Top = 25
            Width = 40
            Height = 24
            ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
            TabOrder = 1
            Text = '255'
            OnChange = Edit_GChange
          end
          object Edit_B: TEdit
            Left = 105
            Top = 25
            Width = 40
            Height = 24
            ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
            TabOrder = 2
            Text = '255'
            OnChange = Edit_BChange
          end
        end
        object GroupBox3: TGroupBox
          Left = 16
          Top = 320
          Width = 217
          Height = 73
          Caption = 'Reference Color'
          TabOrder = 6
          Visible = False
          object Label4: TLabel
            Left = 9
            Top = 25
            Width = 6
            Height = 16
            Caption = 'x'
          end
          object Label7: TLabel
            Left = 73
            Top = 25
            Width = 7
            Height = 16
            Caption = 'y'
          end
          object Label8: TLabel
            Left = 144
            Top = 25
            Width = 9
            Height = 16
            Caption = 'Y'
          end
          object Edit_refx: TEdit
            Left = 16
            Top = 25
            Width = 49
            Height = 24
            Enabled = False
            ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
            TabOrder = 0
            Text = '0.0000'
          end
          object Edit_refy: TEdit
            Left = 89
            Top = 25
            Width = 48
            Height = 24
            Enabled = False
            ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
            TabOrder = 1
            Text = '0.0000'
          end
          object Edit_refLuminance: TEdit
            Left = 160
            Top = 25
            Width = 49
            Height = 24
            Enabled = False
            ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
            TabOrder = 2
            Text = '0.0'
          end
        end
        object CheckBox_MaxRGB: TCheckBox
          Left = 73
          Top = 393
          Width = 96
          Height = 16
          Caption = 'MaxRGB'
          TabOrder = 7
          Visible = False
        end
      end
      object GroupBox5: TGroupBox
        Left = 256
        Top = 9
        Width = 633
        Height = 440
        Caption = 'RGB Pattern'
        TabOrder = 1
        object Label13: TLabel
          Left = 9
          Top = 377
          Width = 10
          Height = 16
          Caption = 'G'
        end
        object Label14: TLabel
          Left = 9
          Top = 409
          Width = 9
          Height = 16
          Caption = 'B'
        end
        object Label12: TLabel
          Left = 9
          Top = 345
          Width = 10
          Height = 16
          Caption = 'R'
        end
        object ScrollBar_R: TScrollBar
          Left = 80
          Top = 352
          Width = 545
          Height = 17
          LargeChange = 10
          Max = 255
          PageSize = 0
          Position = 255
          TabOrder = 0
          OnChange = ScrollBar_RChange
        end
        object ScrollBar_G: TScrollBar
          Left = 80
          Top = 384
          Width = 545
          Height = 17
          LargeChange = 10
          Max = 255
          PageSize = 0
          Position = 255
          TabOrder = 1
          OnChange = ScrollBar_GChange
        end
        object ScrollBar_B: TScrollBar
          Left = 80
          Top = 416
          Width = 545
          Height = 17
          LargeChange = 10
          Max = 255
          PageSize = 0
          Position = 255
          TabOrder = 2
          OnChange = ScrollBar_BChange
        end
        object Panel1: TPanel
          Left = 9
          Top = 16
          Width = 616
          Height = 321
          Color = clWhite
          TabOrder = 3
        end
        object Edit_ScrollR: TEdit
          Left = 25
          Top = 345
          Width = 40
          Height = 24
          Enabled = False
          ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
          TabOrder = 4
          Text = '255'
        end
        object Edit_ScrollG: TEdit
          Left = 25
          Top = 377
          Width = 40
          Height = 24
          Enabled = False
          ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
          TabOrder = 5
          Text = '255'
        end
        object Edit_ScrollB: TEdit
          Left = 25
          Top = 409
          Width = 40
          Height = 24
          Enabled = False
          ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
          TabOrder = 6
          Text = '255'
        end
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Max Matrix'
      ImageIndex = 1
      object GroupBox6: TGroupBox
        Left = 9
        Top = 9
        Width = 208
        Height = 200
        Caption = 'Target Color'
        TabOrder = 0
        object Label17: TLabel
          Left = 9
          Top = 137
          Width = 13
          Height = 16
          Caption = 'W'
        end
        object Label20: TLabel
          Left = 9
          Top = 105
          Width = 9
          Height = 16
          Caption = 'B'
        end
        object Label18: TLabel
          Left = 9
          Top = 73
          Width = 10
          Height = 16
          Caption = 'G'
        end
        object Label19: TLabel
          Left = 9
          Top = 41
          Width = 10
          Height = 16
          Caption = 'R'
        end
        object Label15: TLabel
          Left = 112
          Top = 17
          Width = 9
          Height = 16
          Caption = 'Y'
        end
        object Label9: TLabel
          Left = 57
          Top = 17
          Width = 8
          Height = 16
          Caption = 'X'
        end
        object Label16: TLabel
          Left = 160
          Top = 17
          Width = 8
          Height = 16
          Caption = 'Z'
        end
        object Edit_RZ: TEdit
          Left = 144
          Top = 41
          Width = 49
          Height = 24
          ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
          TabOrder = 0
          Text = '0'
        end
        object Edit_GZ: TEdit
          Left = 144
          Top = 73
          Width = 49
          Height = 24
          ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
          TabOrder = 1
          Text = '0'
        end
        object Edit_BZ: TEdit
          Left = 144
          Top = 105
          Width = 49
          Height = 24
          ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
          TabOrder = 2
          Text = '0'
          OnChange = Edit_BZChange
        end
        object Edit_WZ: TEdit
          Left = 144
          Top = 137
          Width = 49
          Height = 24
          ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
          TabOrder = 3
          Text = '0'
        end
        object Edit_WY: TEdit
          Left = 89
          Top = 137
          Width = 48
          Height = 24
          ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
          TabOrder = 4
          Text = '0'
        end
        object Edit_BY: TEdit
          Left = 89
          Top = 105
          Width = 48
          Height = 24
          ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
          TabOrder = 5
          Text = '0'
        end
        object Edit_GY: TEdit
          Left = 89
          Top = 73
          Width = 48
          Height = 24
          ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
          TabOrder = 6
          Text = '0'
        end
        object Edit_RY: TEdit
          Left = 89
          Top = 41
          Width = 48
          Height = 24
          ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
          TabOrder = 7
          Text = '0'
        end
        object Edit_RX: TEdit
          Left = 32
          Top = 41
          Width = 49
          Height = 24
          ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
          TabOrder = 8
          Text = '0'
        end
        object Edit_GX: TEdit
          Left = 32
          Top = 73
          Width = 49
          Height = 24
          ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
          TabOrder = 9
          Text = '0'
        end
        object Edit_BX: TEdit
          Left = 32
          Top = 105
          Width = 49
          Height = 24
          ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
          TabOrder = 10
          Text = '0'
        end
        object Edit_WX: TEdit
          Left = 32
          Top = 137
          Width = 49
          Height = 24
          ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
          TabOrder = 11
          Text = '0'
        end
        object Button1: TButton
          Left = 65
          Top = 170
          Width = 80
          Height = 23
          Caption = 'Set'
          Enabled = False
          TabOrder = 12
          OnClick = Button1Click
        end
      end
    end
  end
end