object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 411
  ClientWidth = 852
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 456
    Top = 40
    Width = 31
    Height = 13
    Caption = 'Label1'
  end
  object InfoLabel: TLabel
    Left = 144
    Top = 280
    Width = 25
    Height = 13
    Caption = 'Info?'
  end
  object InfoLabel2: TLabel
    Left = 144
    Top = 299
    Width = 25
    Height = 13
    Caption = 'Info?'
  end
  object UserStringTree: TVirtualStringTree
    Left = 0
    Top = 0
    Width = 401
    Height = 257
    Header.AutoSizeIndex = 0
    Header.Options = [hoColumnResize, hoDrag, hoShowSortGlyphs, hoVisible]
    TabOrder = 0
    OnAddToSelection = UserStringTreeAddToSelection
    OnGetText = UserStringTreeGetText
    OnRemoveFromSelection = UserStringTreeRemoveFromSelection
    Columns = <
      item
        Position = 0
        Text = 'Name'
      end
      item
        Position = 1
        Text = 'Surname'
      end>
  end
  object ShowButton: TButton
    Left = 24
    Top = 275
    Width = 75
    Height = 25
    Caption = 'Show data'
    TabOrder = 1
    OnClick = ShowButtonClick
  end
  object PopulateButton: TButton
    Left = 472
    Top = 304
    Width = 129
    Height = 25
    Caption = 'Populate with data'
    TabOrder = 2
    OnClick = PopulateButtonClick
  end
  object ConnectionButton: TButton
    Left = 496
    Top = 256
    Width = 75
    Height = 25
    Caption = 'Connect'
    TabOrder = 3
    OnClick = ConnectionButtonClick
  end
  object ClearButton: TButton
    Left = 482
    Top = 352
    Width = 103
    Height = 25
    Caption = 'Clear the table'
    TabOrder = 4
    OnClick = ClearButtonClick
  end
  object RemoveButton: TButton
    Left = 248
    Top = 275
    Width = 75
    Height = 25
    Caption = 'Remove Row'
    TabOrder = 5
    OnClick = RemoveButtonClick
  end
  object SQLConnection1: TSQLConnection
    DriverName = 'Sqlite'
    Params.Strings = (
      'DriverUnit=Data.DbxSqlite'
      
        'DriverPackageLoader=TDBXSqliteDriverLoader,DBXSqliteDriver250.bp' +
        'l'
      
        'MetaDataPackageLoader=TDBXSqliteMetaDataCommandFactory,DbxSqlite' +
        'Driver250.bpl'
      'FailIfMissing=True'
      'Database=')
    Left = 480
    Top = 192
  end
  object SQLQuery1: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 560
    Top = 192
  end
end
