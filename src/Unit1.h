//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
    TStatusBar *StatusBar1;
    TGroupBox *GroupBox2;
    TMemo *Memo1;
    TTimer *Timer1;
    TSaveDialog *SaveDialog1;
    TOpenDialog *OpenDialog1;
        TGroupBox *GroupBox1;
        TGroupBox *GrBxAuth;
        TEdit *EdtKey;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label8;
        TEdit *EdtAID;
        TComboBox *CmBxFileNr;
        TLabel *Label3;
        TComboBox *CmBxKeyNo;
        TLabel *LblFileNr;
        TCheckBox *ChBxAuth;
        TLabel *Label10;
        TLabel *Label11;
        TCheckBox *ChBxInterKey;
        TComboBox *CmBxInterKeyNr;
        TLabel *LblInterKeyNr;
        TGroupBox *GrBxIntKey;
        TLabel *Label12;
        TEdit *EdtIntKey;
        TComboBox *CmBxEnterInterKey;
        TLabel *Label13;
        TButton *BtnKey;
        TLabel *LblKeyPass;
        TEdit *EdtKeyPass;
        TButton *BtnKeyLock;
        TButton *BtnKeyUnlock;
        TGroupBox *GrBxKeys;
        TLabel *LblNewKey;
        TEdit *EdtNewKey;
        TEdit *EdtOldKey;
        TLabel *LblOldKey;
        TButton *BtnCardKey;
        TLabel *LblAidKeyNr;
        TComboBox *CmBxAidKeyNr;
        TButton *BtnChangeKeySetting;
        TButton *BtnGetKeySetings;
        TCheckBox *ChBxSett_1;
        TCheckBox *ChBxCreate_1;
        TCheckBox *ChBxMaster_1;
        TGroupBox *GrBxApp;
        TLabel *Label14;
        TEdit *EdtAID_2;
        TLabel *LblMaxKeyNo;
        TComboBox *CmBxAppMaxKeyNo;
        TButton *BtnApp;
        TGroupBox *GrBxFile;
        TLabel *Label15;
     TComboBox *CmBxFileId_2;
        TLabel *Label9;
        TComboBox *CmBxEncrType;
        TLabel *LblFileSize;
        TEdit *EdtFileSize;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label7;
        TComboBox *CmBxChangeKey;
        TComboBox *CmBxRWKey;
        TComboBox *CmBxWriteKey;
        TComboBox *CmBxReadKey;
        TButton *BtnFile;
        TButton *BtnDelFile;
        TButton *Button1;
        TCheckBox *ChBxSett_2;
        TCheckBox *ChBxCreate_2;
        TCheckBox *ChBxMaster_2;
        TLabel *Label16;
        TGroupBox *GrBxReadWrite;
        TLabel *Label17;
        TComboBox *CmBxEncrType_2;
        TEdit *EdtFileSize_2;
        TLabel *Label18;
        TButton *BtnFileWrite;
        TButton *BtnFileRead;
        TGroupBox *GrBxCard;
        TButton *BtnUid;
        TButton *BtnFreeMem;
        TButton *Button2;
        TButton *BtnRndUid;
        TButton *BtnNewCard;
        TButton *BtnPort;
     TGroupBox *GroupBox3;
     TButton *btnGetSpeed;
     TButton *btnSetSpeed;
     TLabel *Label19;
     TComboBox *cbTxSpeed;
     TLabel *lbTxSpeed;
     TLabel *lbRxSpeed;
     TComboBox *cbRxSpeed;
     TRadioGroup *RGFileType;
     TEdit *EdtLowLim;
     TEdit *EdtUpLim;
     TEdit *EdtValue;
     TLabel *Label20;
     TLabel *Label21;
     TLabel *Label22;
     TCheckBox *BxLimCred;
     TGroupBox *GrBxValueFile;
     TComboBox *CmBxEncrType_3;
     TButton *BtnReadValue;
     TButton *BtnIncrease;
     TButton *BtnDecrease;
     TEdit *EdtFileValue;
     TLabel *Label23;
     TLabel *Label24;
     TCheckBox *BxFreeGet;
    void __fastcall BtnPortClick(TObject *Sender);
    void __fastcall BtnUidClick(TObject *Sender);
    void __fastcall BtnKeyClick(TObject *Sender);
    void __fastcall Timer1Timer(TObject *Sender);
    void __fastcall BtnAppClick(TObject *Sender);
    void __fastcall BtnFileClick(TObject *Sender);
    void __fastcall BtnCardKeyClick(TObject *Sender);
    void __fastcall BtnGetKeySetingsClick(TObject *Sender);
    void __fastcall BtnChangeKeySettingClick(TObject *Sender);
    void __fastcall BtnDelAppClick(TObject *Sender);
    void __fastcall BtnDelFileClick(TObject *Sender);
    void __fastcall BtnRndUidClick(TObject *Sender);
    void __fastcall BtnFileReadClick(TObject *Sender);
    void __fastcall BtnFileWriteClick(TObject *Sender);
    void __fastcall BtnFormatClick(TObject *Sender);
    void __fastcall BtnFreeMemClick(TObject *Sender);
    void __fastcall BtnNewCardClick(TObject *Sender);
    void __fastcall BtnKeyLockClick(TObject *Sender);
    void __fastcall BtnKeyUnlockClick(TObject *Sender);
     void __fastcall btnSetSpeedClick(TObject *Sender);
     void __fastcall btnGetSpeedClick(TObject *Sender);
     void __fastcall RGFileTypeClick(TObject *Sender);
     void __fastcall BtnReadValueClick(TObject *Sender);
     void __fastcall BtnIncreaseClick(TObject *Sender);
     void __fastcall BtnDecreaseClick(TObject *Sender);
private:	// User declarations
    AnsiString as;
    void PRN() { Memo1->Lines->Add(as); }

    bool prepare_key(unsigned char aes_key[16]);
    bool prepare_new_key(unsigned char aes_key[16]);
    bool prepare_old_key(unsigned char aes_key[16]);
    bool prepare_int_key(unsigned char aes_key[16]);

public:		// User declarations
    __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
