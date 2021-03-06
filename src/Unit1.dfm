object Form1: TForm1
  Left = 238
  Top = 27
  Width = 993
  Height = 760
  Caption = 'Mifare Desfire demo ver 4.3'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label2: TLabel
    Left = 24
    Top = 60
    Width = 78
    Height = 13
    Caption = 'AID 3 bytes hex '
  end
  object Label10: TLabel
    Left = 24
    Top = 84
    Width = 100
    Height = 13
    Caption = 'AID key number auth'
  end
  object Label11: TLabel
    Left = 24
    Top = 104
    Width = 30
    Height = 13
    Caption = 'File ID'
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 703
    Width = 977
    Height = 19
    Panels = <>
    SimplePanel = True
  end
  object GroupBox2: TGroupBox
    Left = 0
    Top = 553
    Width = 977
    Height = 150
    Align = alClient
    TabOrder = 1
    object Memo1: TMemo
      Left = 2
      Top = 15
      Width = 973
      Height = 133
      Align = alClient
      TabOrder = 0
    end
  end
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 977
    Height = 553
    Align = alTop
    TabOrder = 2
    object GrBxAuth: TGroupBox
      Left = 8
      Top = 8
      Width = 433
      Height = 145
      Caption = 'Card authentication'
      TabOrder = 0
      object Label1: TLabel
        Left = 16
        Top = 24
        Width = 44
        Height = 13
        Caption = 'AES key:'
      end
      object Label8: TLabel
        Left = 16
        Top = 52
        Width = 78
        Height = 13
        Caption = 'AID 3 bytes hex '
      end
      object Label3: TLabel
        Left = 16
        Top = 76
        Width = 100
        Height = 13
        Caption = 'AID key number auth'
      end
      object LblFileNr: TLabel
        Left = 16
        Top = 100
        Width = 30
        Height = 13
        Caption = 'File ID'
      end
      object LblInterKeyNr: TLabel
        Left = 296
        Top = 52
        Width = 93
        Height = 13
        Caption = 'Internal key number'
      end
      object EdtKey: TEdit
        Left = 72
        Top = 20
        Width = 217
        Height = 21
        MaxLength = 32
        TabOrder = 0
        Text = '000102030405060708090A0B0C0D0E0F'
      end
      object EdtAID: TEdit
        Left = 128
        Top = 48
        Width = 65
        Height = 21
        MaxLength = 6
        TabOrder = 1
        Text = '000000'
      end
      object CmBxFileNr: TComboBox
        Left = 128
        Top = 96
        Width = 65
        Height = 21
        ItemHeight = 13
        ItemIndex = 0
        TabOrder = 2
        Text = '0'
        Items.Strings = (
          '0'
          '1'
          '2'
          '3'
          '4'
          '5'
          '6'
          '7'
          '8'
          '9'
          '10'
          '11'
          '12'
          '13'
          '14'
          '15'
          '16'
          '17'
          '18'
          '19'
          '20'
          '21'
          '22'
          '23'
          '24'
          '25'
          '26'
          '27'
          '28'
          '29'
          '30'
          '31')
      end
      object CmBxKeyNo: TComboBox
        Left = 128
        Top = 72
        Width = 65
        Height = 21
        ItemHeight = 13
        TabOrder = 3
        Text = '0'
        Items.Strings = (
          '0'
          '1'
          '2'
          '3'
          '4'
          '5'
          '6'
          '7'
          '8'
          '9'
          '10'
          '11'
          '12'
          '13')
      end
      object ChBxAuth: TCheckBox
        Left = 16
        Top = 120
        Width = 193
        Height = 17
        Caption = 'Master key authentication requires'
        TabOrder = 4
      end
      object ChBxInterKey: TCheckBox
        Left = 296
        Top = 24
        Width = 113
        Height = 17
        Caption = 'Internal key using'
        TabOrder = 5
      end
      object CmBxInterKeyNr: TComboBox
        Left = 296
        Top = 68
        Width = 65
        Height = 21
        ItemHeight = 13
        TabOrder = 6
        Text = '0'
        Items.Strings = (
          '0'
          '1'
          '2'
          '3'
          '4'
          '5'
          '6'
          '7'
          '8'
          '9'
          '10'
          '11'
          '12'
          '13'
          '14'
          '15')
      end
    end
    object GrBxIntKey: TGroupBox
      Left = 456
      Top = 8
      Width = 369
      Height = 145
      Caption = 'Internal keys operations'
      TabOrder = 1
      object Label12: TLabel
        Left = 24
        Top = 28
        Width = 44
        Height = 13
        Caption = 'AES key:'
      end
      object Label13: TLabel
        Left = 20
        Top = 52
        Width = 93
        Height = 13
        Caption = 'Internal key number'
      end
      object LblKeyPass: TLabel
        Left = 19
        Top = 84
        Width = 126
        Height = 13
        Caption = 'Internal key lock password'
      end
      object EdtIntKey: TEdit
        Left = 80
        Top = 24
        Width = 217
        Height = 21
        MaxLength = 32
        TabOrder = 0
        Text = '000102030405060708090A0B0C0D0E0F'
      end
      object CmBxEnterInterKey: TComboBox
        Left = 120
        Top = 48
        Width = 65
        Height = 21
        ItemHeight = 13
        TabOrder = 1
        Text = '0'
        Items.Strings = (
          '0'
          '1'
          '2'
          '3'
          '4'
          '5'
          '6'
          '7'
          '8'
          '9'
          '10'
          '11'
          '12'
          '13'
          '14'
          '15')
      end
      object BtnKey: TButton
        Left = 192
        Top = 48
        Width = 129
        Height = 25
        Caption = 'Store AES key into reader'
        Enabled = False
        TabOrder = 2
        OnClick = BtnKeyClick
      end
      object EdtKeyPass: TEdit
        Left = 152
        Top = 80
        Width = 65
        Height = 21
        MaxLength = 8
        TabOrder = 3
        Text = '11111111'
      end
      object BtnKeyLock: TButton
        Left = 16
        Top = 112
        Width = 113
        Height = 25
        Caption = 'Internal Keys Lock'
        TabOrder = 4
        OnClick = BtnKeyLockClick
      end
      object BtnKeyUnlock: TButton
        Left = 160
        Top = 112
        Width = 113
        Height = 25
        Caption = 'Internal Key Unlock'
        TabOrder = 5
        OnClick = BtnKeyUnlockClick
      end
    end
    object GrBxKeys: TGroupBox
      Left = 8
      Top = 160
      Width = 433
      Height = 201
      Caption = 'Keys operations'
      TabOrder = 2
      object LblNewKey: TLabel
        Left = 21
        Top = 52
        Width = 42
        Height = 13
        Caption = 'New key'
      end
      object LblOldKey: TLabel
        Left = 21
        Top = 28
        Width = 36
        Height = 13
        Caption = 'Old key'
      end
      object LblAidKeyNr: TLabel
        Left = 21
        Top = 76
        Width = 76
        Height = 13
        Caption = 'AID key number'
      end
      object EdtNewKey: TEdit
        Left = 72
        Top = 48
        Width = 217
        Height = 21
        MaxLength = 32
        TabOrder = 0
        Text = '000102030405060708090A0B0C0D0E0F'
      end
      object EdtOldKey: TEdit
        Left = 72
        Top = 24
        Width = 217
        Height = 21
        MaxLength = 32
        TabOrder = 1
        Text = '000102030405060708090A0B0C0D0E0F'
      end
      object BtnCardKey: TButton
        Left = 312
        Top = 24
        Width = 105
        Height = 25
        Caption = 'Change AES key'
        TabOrder = 2
        OnClick = BtnCardKeyClick
      end
      object CmBxAidKeyNr: TComboBox
        Left = 120
        Top = 72
        Width = 65
        Height = 21
        ItemHeight = 13
        TabOrder = 3
        Text = '0'
        Items.Strings = (
          '0'
          '1'
          '2'
          '3'
          '4'
          '5'
          '6'
          '7'
          '8'
          '9'
          '10'
          '11'
          '12'
          '13')
      end
      object BtnChangeKeySetting: TButton
        Left = 144
        Top = 104
        Width = 121
        Height = 25
        Caption = 'Change Key Settings'
        TabOrder = 4
        OnClick = BtnChangeKeySettingClick
      end
      object BtnGetKeySetings: TButton
        Left = 16
        Top = 104
        Width = 113
        Height = 25
        Caption = 'Get Key Settings'
        TabOrder = 5
        OnClick = BtnGetKeySetingsClick
      end
      object ChBxSett_1: TCheckBox
        Left = 16
        Top = 144
        Width = 297
        Height = 17
        Caption = 'Settings not changable anymore'
        TabOrder = 6
      end
      object ChBxCreate_1: TCheckBox
        Left = 16
        Top = 160
        Width = 321
        Height = 17
        Caption = 'Create or delete application with master key authentication'
        TabOrder = 7
      end
      object ChBxMaster_1: TCheckBox
        Left = 16
        Top = 176
        Width = 313
        Height = 17
        Caption = 'Master key not changable anymore'
        TabOrder = 8
      end
    end
    object GrBxApp: TGroupBox
      Left = 456
      Top = 160
      Width = 369
      Height = 145
      Caption = 'Application '
      TabOrder = 3
      object Label14: TLabel
        Left = 16
        Top = 20
        Width = 78
        Height = 13
        Caption = 'AID 3 bytes hex '
      end
      object LblMaxKeyNo: TLabel
        Left = 16
        Top = 44
        Width = 96
        Height = 13
        Caption = 'Maximal key number'
      end
      object Label16: TLabel
        Left = 16
        Top = 72
        Width = 123
        Height = 13
        Caption = 'Application'#39's keys settings'
      end
      object EdtAID_2: TEdit
        Left = 128
        Top = 16
        Width = 65
        Height = 21
        MaxLength = 6
        TabOrder = 0
        Text = '000000'
      end
      object CmBxAppMaxKeyNo: TComboBox
        Left = 128
        Top = 40
        Width = 65
        Height = 21
        ItemHeight = 13
        TabOrder = 1
        Text = '0'
        Items.Strings = (
          '0'
          '1'
          '2'
          '3'
          '4'
          '5'
          '6'
          '7'
          '8'
          '9'
          '10'
          '11'
          '12'
          '13')
      end
      object BtnApp: TButton
        Left = 248
        Top = 16
        Width = 97
        Height = 25
        Caption = 'Make Application'
        TabOrder = 2
        OnClick = BtnAppClick
      end
      object Button1: TButton
        Left = 248
        Top = 48
        Width = 97
        Height = 25
        Caption = 'Delete Application'
        TabOrder = 3
        OnClick = BtnDelAppClick
      end
      object ChBxSett_2: TCheckBox
        Left = 16
        Top = 88
        Width = 297
        Height = 17
        Caption = 'Settings not changable anymore'
        TabOrder = 4
      end
      object ChBxCreate_2: TCheckBox
        Left = 16
        Top = 104
        Width = 321
        Height = 17
        Caption = 'Create or delete file with master key authentication'
        TabOrder = 5
      end
      object ChBxMaster_2: TCheckBox
        Left = 16
        Top = 120
        Width = 313
        Height = 17
        Caption = 'Application master key not changable anymore'
        TabOrder = 6
      end
    end
    object GrBxFile: TGroupBox
      Left = 8
      Top = 368
      Width = 433
      Height = 169
      Caption = 'File'
      TabOrder = 4
      object Label15: TLabel
        Left = 8
        Top = 16
        Width = 30
        Height = 13
        Caption = 'File ID'
      end
      object Label9: TLabel
        Left = 8
        Top = 44
        Width = 58
        Height = 13
        Caption = 'Comm mode'
      end
      object LblFileSize: TLabel
        Left = 8
        Top = 72
        Width = 48
        Height = 13
        Caption = 'Size of file'
      end
      object Label4: TLabel
        Left = 25
        Top = 124
        Width = 46
        Height = 13
        Caption = 'Read key'
      end
      object Label5: TLabel
        Left = 98
        Top = 124
        Width = 45
        Height = 13
        Caption = 'Write key'
      end
      object Label6: TLabel
        Left = 164
        Top = 124
        Width = 57
        Height = 13
        Caption = 'Read & Write'
      end
      object Label7: TLabel
        Left = 232
        Top = 124
        Width = 57
        Height = 13
        Caption = 'Change key'
      end
      object Label20: TLabel
        Left = 16
        Top = 88
        Width = 49
        Height = 13
        Caption = 'Lower limit'
      end
      object Label21: TLabel
        Left = 88
        Top = 88
        Width = 49
        Height = 13
        Caption = 'Upper limit'
      end
      object Label22: TLabel
        Left = 160
        Top = 88
        Width = 27
        Height = 13
        Caption = 'Value'
      end
      object CmBxFileId_2: TComboBox
        Left = 72
        Top = 12
        Width = 65
        Height = 21
        ItemHeight = 13
        ItemIndex = 0
        TabOrder = 0
        Text = '0'
        Items.Strings = (
          '0'
          '1'
          '2'
          '3'
          '4'
          '5'
          '6'
          '7'
          '8'
          '9'
          '10'
          '11'
          '12'
          '13'
          '14'
          '15'
          '16'
          '17'
          '18'
          '19'
          '20'
          '21'
          '22'
          '23'
          '24'
          '25'
          '26'
          '27'
          '28'
          '29'
          '30'
          '31')
      end
      object CmBxEncrType: TComboBox
        Left = 72
        Top = 40
        Width = 97
        Height = 21
        ItemHeight = 13
        ItemIndex = 0
        TabOrder = 1
        Text = 'PLAIN'
        Items.Strings = (
          'PLAIN'
          'MACKED'
          'ENCHIPERED')
      end
      object EdtFileSize: TEdit
        Left = 72
        Top = 68
        Width = 49
        Height = 21
        TabOrder = 2
        Text = '20'
      end
      object CmBxChangeKey: TComboBox
        Left = 228
        Top = 140
        Width = 65
        Height = 21
        ItemHeight = 13
        TabOrder = 3
        Text = '0'
        Items.Strings = (
          '0'
          '1'
          '2'
          '3'
          '4'
          '5'
          '6'
          '7'
          '8'
          '9'
          '10'
          '11'
          '12'
          '13'
          '14'
          '15')
      end
      object CmBxRWKey: TComboBox
        Left = 160
        Top = 140
        Width = 65
        Height = 21
        ItemHeight = 13
        TabOrder = 4
        Text = '0'
        Items.Strings = (
          '0'
          '1'
          '2'
          '3'
          '4'
          '5'
          '6'
          '7'
          '8'
          '9'
          '10'
          '11'
          '12'
          '13'
          '14'
          '15')
      end
      object CmBxWriteKey: TComboBox
        Left = 88
        Top = 140
        Width = 65
        Height = 21
        ItemHeight = 13
        TabOrder = 5
        Text = '0'
        Items.Strings = (
          '0'
          '1'
          '2'
          '3'
          '4'
          '5'
          '6'
          '7'
          '8'
          '9'
          '10'
          '11'
          '12'
          '13'
          '14'
          '15')
      end
      object CmBxReadKey: TComboBox
        Left = 16
        Top = 140
        Width = 65
        Height = 21
        ItemHeight = 13
        TabOrder = 6
        Text = '0'
        Items.Strings = (
          '0'
          '1'
          '2'
          '3'
          '4'
          '5'
          '6'
          '7'
          '8'
          '9'
          '10'
          '11'
          '12'
          '13'
          '14'
          '15')
      end
      object BtnFile: TButton
        Left = 312
        Top = 24
        Width = 105
        Height = 25
        Caption = 'Make File'
        TabOrder = 7
        OnClick = BtnFileClick
      end
      object BtnDelFile: TButton
        Left = 312
        Top = 56
        Width = 105
        Height = 25
        Caption = 'Delete File'
        TabOrder = 8
        OnClick = BtnDelFileClick
      end
      object BtnPort: TButton
        Left = 320
        Top = 138
        Width = 88
        Height = 23
        Caption = 'Port Open'
        TabOrder = 9
        Visible = False
        OnClick = BtnPortClick
      end
      object RGFileType: TRadioGroup
        Left = 176
        Top = 8
        Width = 121
        Height = 57
        Caption = 'RGFileType'
        ItemIndex = 0
        Items.Strings = (
          'Standard data file'
          'Value file')
        TabOrder = 10
        OnClick = RGFileTypeClick
      end
      object EdtLowLim: TEdit
        Left = 16
        Top = 104
        Width = 65
        Height = 21
        Enabled = False
        TabOrder = 11
        Text = '0'
      end
      object EdtUpLim: TEdit
        Left = 88
        Top = 104
        Width = 65
        Height = 21
        Enabled = False
        TabOrder = 12
        Text = '0'
      end
      object EdtValue: TEdit
        Left = 160
        Top = 104
        Width = 65
        Height = 21
        Enabled = False
        TabOrder = 13
        Text = '0'
      end
      object BxLimCred: TCheckBox
        Left = 240
        Top = 104
        Width = 89
        Height = 17
        Caption = 'Limited credit'
        Enabled = False
        TabOrder = 14
      end
      object BxFreeGet: TCheckBox
        Left = 328
        Top = 104
        Width = 97
        Height = 17
        Caption = 'Free get value'
        Enabled = False
        TabOrder = 15
      end
    end
    object GrBxReadWrite: TGroupBox
      Left = 456
      Top = 304
      Width = 369
      Height = 81
      Caption = 'Standard Data File Read and Write'
      TabOrder = 5
      object Label17: TLabel
        Left = 8
        Top = 24
        Width = 101
        Height = 13
        Caption = 'Communication mode'
      end
      object Label18: TLabel
        Left = 8
        Top = 52
        Width = 48
        Height = 13
        Caption = 'Size of file'
      end
      object CmBxEncrType_2: TComboBox
        Left = 120
        Top = 20
        Width = 97
        Height = 21
        ItemHeight = 13
        ItemIndex = 0
        TabOrder = 0
        Text = 'PLAIN'
        Items.Strings = (
          'PLAIN'
          'MACKED'
          'ENCHIPERED')
      end
      object EdtFileSize_2: TEdit
        Left = 120
        Top = 48
        Width = 65
        Height = 21
        TabOrder = 1
        Text = '20'
      end
      object BtnFileWrite: TButton
        Left = 248
        Top = 16
        Width = 97
        Height = 25
        Caption = 'File Writing'
        TabOrder = 2
        OnClick = BtnFileWriteClick
      end
      object BtnFileRead: TButton
        Left = 248
        Top = 48
        Width = 97
        Height = 25
        Caption = 'File Reading'
        TabOrder = 3
        OnClick = BtnFileReadClick
      end
    end
    object GrBxCard: TGroupBox
      Left = 456
      Top = 464
      Width = 369
      Height = 81
      Caption = 'Card operations'
      TabOrder = 6
      object BtnUid: TButton
        Left = 8
        Top = 18
        Width = 105
        Height = 23
        Caption = 'Get Card UID'
        Enabled = False
        TabOrder = 0
        OnClick = BtnUidClick
      end
      object BtnFreeMem: TButton
        Left = 8
        Top = 48
        Width = 105
        Height = 25
        Caption = 'Get free memory'
        TabOrder = 1
        OnClick = BtnFreeMemClick
      end
      object Button2: TButton
        Left = 128
        Top = 16
        Width = 105
        Height = 25
        Caption = 'Format card'
        TabOrder = 2
        OnClick = BtnFormatClick
      end
      object BtnRndUid: TButton
        Left = 128
        Top = 48
        Width = 105
        Height = 25
        Caption = 'Set Random ID'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clRed
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 3
        OnClick = BtnRndUidClick
      end
      object BtnNewCard: TButton
        Left = 248
        Top = 16
        Width = 97
        Height = 25
        Caption = 'DES to AES'
        TabOrder = 4
        OnClick = BtnNewCardClick
      end
    end
    object GroupBox3: TGroupBox
      Left = 832
      Top = 8
      Width = 137
      Height = 529
      Caption = 'Baud rate'
      TabOrder = 7
      object Label19: TLabel
        Left = 8
        Top = 480
        Width = 121
        Height = 39
        Caption = 'Required baud rates are stored permanently in the reader.'
        WordWrap = True
      end
      object lbTxSpeed: TLabel
        Left = 8
        Top = 24
        Width = 91
        Height = 13
        Caption = 'Transmit baud rate:'
      end
      object lbRxSpeed: TLabel
        Left = 8
        Top = 72
        Width = 91
        Height = 13
        Caption = 'Receive baud rate:'
      end
      object btnGetSpeed: TButton
        Left = 8
        Top = 160
        Width = 121
        Height = 25
        Caption = 'Get baud rate'
        TabOrder = 0
        OnClick = btnGetSpeedClick
      end
      object btnSetSpeed: TButton
        Left = 8
        Top = 130
        Width = 121
        Height = 23
        Caption = 'Set baud rate'
        TabOrder = 1
        OnClick = btnSetSpeedClick
      end
      object cbTxSpeed: TComboBox
        Left = 8
        Top = 40
        Width = 121
        Height = 21
        Style = csDropDownList
        DropDownCount = 4
        ItemHeight = 13
        ItemIndex = 0
        TabOrder = 2
        Text = '106 kbps'
        Items.Strings = (
          '106 kbps'
          '212 kbps'
          '424 kbps'
          '848 kbps')
      end
      object cbRxSpeed: TComboBox
        Left = 8
        Top = 88
        Width = 121
        Height = 21
        Style = csDropDownList
        DropDownCount = 4
        ItemHeight = 13
        ItemIndex = 0
        TabOrder = 3
        Text = '106 kbps'
        Items.Strings = (
          '106 kbps'
          '212 kbps'
          '424 kbps'
          '848 kbps')
      end
    end
    object GrBxValueFile: TGroupBox
      Left = 456
      Top = 384
      Width = 369
      Height = 81
      Caption = 'Value File Operation'
      TabOrder = 8
      object Label23: TLabel
        Left = 8
        Top = 24
        Width = 104
        Height = 13
        Caption = 'Communication  mode'
      end
      object Label24: TLabel
        Left = 296
        Top = 32
        Width = 27
        Height = 13
        Caption = 'Value'
      end
      object CmBxEncrType_3: TComboBox
        Left = 120
        Top = 16
        Width = 97
        Height = 21
        ItemHeight = 13
        ItemIndex = 0
        TabOrder = 0
        Text = 'PLAIN'
        Items.Strings = (
          'PLAIN'
          'MACKED'
          'ENCHIPERED')
      end
      object BtnReadValue: TButton
        Left = 8
        Top = 48
        Width = 81
        Height = 25
        Caption = 'Read Value'
        TabOrder = 1
        OnClick = BtnReadValueClick
      end
      object BtnIncrease: TButton
        Left = 96
        Top = 48
        Width = 81
        Height = 25
        Caption = 'Increase value'
        TabOrder = 2
        OnClick = BtnIncreaseClick
      end
      object BtnDecrease: TButton
        Left = 184
        Top = 48
        Width = 81
        Height = 25
        Caption = 'Decrease Value'
        TabOrder = 3
        OnClick = BtnDecreaseClick
      end
      object EdtFileValue: TEdit
        Left = 272
        Top = 48
        Width = 89
        Height = 21
        TabOrder = 4
        Text = '0'
      end
    end
  end
  object Timer1: TTimer
    OnTimer = Timer1Timer
    Left = 264
    Top = 432
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = 'bin'
    Left = 200
    Top = 432
  end
  object OpenDialog1: TOpenDialog
    Left = 232
    Top = 432
  end
end
