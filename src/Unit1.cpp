//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Unit1.h"
//---------------------------------------------------------------------------
//#include <uFCoder.h>
#include "uFCoder.h"
//---------------------------------------------------------------------------
//#include "PICCCmdConst.h"
#define PICC_GET_VERSION   0x60			//!< get card version bytes
#define BUFFER_SIZE 192

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) :
		TForm(Owner)
{
}
//---------------------------------------------------------------------------

/***************************************************************************/

PCCH get_result_str(unsigned short card_status, unsigned short exec_time)
{
	static char retstr[4096] = "";
	const char eol[] = "\r\n";
	const char line_separtor[] = "=============";
	char tmpstr[4096];
	bool prn_time;

//	retstr[0] = 0;
	strcpy(retstr, line_separtor);
	strcat(retstr, eol);

	switch (card_status)
	{
	case READER_ERROR:
		strcat(retstr, "Reader error");
		prn_time = false;
		break;

	case NO_CARD_DETECTED:
		strcat(retstr, "Card did not detected");
		prn_time = false;
		break;

	case CARD_OPERATION_OK:
		strcat(retstr, "OK");
		prn_time = true;
		break;

	case DESFIRE_CARD_APPLICATION_NOT_FOUND:
		strcat(retstr, "AID not found");
		prn_time = true;
		break;

	case WRONG_KEY_TYPE:
		strcat(retstr, "Wrong type of key (is not AES)");
		prn_time = true;
		break;

	case KEY_AUTH_ERROR:
		strcat(retstr, "Wrong key");
		prn_time = true;
		break;

	case DESFIRE_CARD_NO_SUCH_KEY:
		strcat(retstr, "Invalid key number");
		prn_time = true;
		break;

	case DESFIRE_CARD_DUPLICATE_ERROR:
		strcat(retstr, "This AID or File ID already exist");
		prn_time = true;
		break;

	case DESFIRE_CARD_PERMISSION_DENIED:
	case DESFIRE_CARD_AUTHENTICATION_ERROR:
		strcat(retstr, "Permission denied");
		prn_time = true;
		break;

	case DESFIRE_CARD_BOUNDARY_ERROR:
		strcat(retstr, "File boundary error");
		prn_time = false;
		break;

	case DESFIRE_CARD_OUT_OF_EEPROM_ERROR:
		strcat(retstr, "Insuficient of card memory");
		prn_time = false;
		break;

	case DESFIRE_CARD_NO_CHANGES:
		strcat(retstr, "No changes");
		prn_time = false;
		break;

	case DESFIRE_CARD_ILLEGAL_COMMAND_CODE:
		strcat(retstr, "Not supported command");
		prn_time = false;
		break;

	case DESFIRE_CARD_INTEGRITY_ERROR:
		strcat(retstr, "Not valid crypto data");
		prn_time = false;
		break;

	case DESFIRE_CARD_LENGTH_ERROR:
		strcat(retstr, "Length of command error");
		prn_time = false;
		break;

	case DESFIRE_CARD_PARAMETER_ERROR:
		strcat(retstr, "Command parameter error");
		prn_time = false;
		break;

	case DESFIRE_CARD_APPL_INTEGRITY_ERROR:
		strcat(retstr, "Application structure is not valid");
		prn_time = false;
		break;

	case DESFIRE_CARD_ADDITIONAL_FRAME:
		strcat(retstr, "Additional frame expected");
		prn_time = false;
		break;

	case DESFIRE_CARD_PICC_INTEGRITY_ERROR:
		strcat(retstr, "Card error");
		prn_time = false;
		break;

	case DESFIRE_CARD_COMMAND_ABORTED:
		strcat(retstr, "Command not fully completed");
		prn_time = false;
		break;

	case DESFIRE_CARD_PICC_DISABLED_ERROR:
		strcat(retstr, "Card disabled");
		prn_time = false;
		break;

	case DESFIRE_CARD_COUNT_ERROR:
		strcat(retstr, "Maximal number of application is reached");
		prn_time = false;
		break;

	case DESFIRE_CARD_EEPROM_ERROR_DES:
		strcat(retstr, "Card internal EEPROM error");
		prn_time = false;
		break;

	case DESFIRE_CARD_FILE_NOT_FOUND:
		strcat(retstr, "File ID not found");
		prn_time = false;
		break;

	case DESFIRE_CARD_FILE_INTEGRITY_ERROR:
		strcat(retstr, "File integrity error");
		prn_time = false;
		break;

     case COMMIT_TRANSACTION_NO_REPLY:
          strcat(retstr, "Response to the commit transaction was not received");
		prn_time = false;
		break;

     case COMMIT_TRANSACTION_ERROR:
          strcat(retstr, "Error occured during the commit transaction");
		prn_time = false;
		break;

	default:
		strcat(retstr, "Unknown status");

		prn_time = false;

		break;
	}

	strcat(retstr, eol);

	// patch
	prn_time = true;
	if (prn_time)
	{
		sprintf(tmpstr, "Execution time of operation = %d ms", (int) exec_time);
		strcat(retstr, tmpstr);
		strcat(retstr, eol);
	}

	return retstr;
}

void __fastcall TForm1::BtnPortClick(TObject *Sender)
{
	UFR_STATUS status;
     unsigned char tx_speed, rx_speed;

	StatusBar1->SimpleText = "Searching for reader ...";
	Update();

	status = ReaderOpen();
	if (status)
	{
		StatusBar1->SimpleText = "Communication port is not open";
		return;
	}

	as = GetReaderDescription();
	PRN();

	StatusBar1->SimpleText = "Communication port is open";

	BtnKey->Enabled = true;
	BtnUid->Enabled = true;

	Timer1->Enabled = false;

     status = GetSpeedParameters(&tx_speed, &rx_speed);
     if (!status) {
          cbTxSpeed->ItemIndex = tx_speed;
          cbRxSpeed->ItemIndex = rx_speed;
     }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BtnUidClick(TObject *Sender)
{
	UFR_STATUS status;
	unsigned short card_status;
	unsigned short exec_time;

	unsigned char data[BUFFER_SIZE];
	unsigned char data_length;

	AnsiString memory_size;

	unsigned long aid;
	unsigned char aid_key_nr;
	unsigned char aes_key_ext[16];
	unsigned char internal_key, aes_key_nr;

	Memo1->Clear();
	StatusBar1->SimpleText = "Checking card ...";
	Update();

	aid = strtol(EdtAID->Text.c_str(), NULL, 16);

	aid_key_nr = StrToInt(CmBxKeyNo->Text);

	if (ChBxInterKey->Checked)
		internal_key = 1;
	else
		internal_key = 0;

	if (internal_key == 0)
	{
		if (!prepare_key(aes_key_ext))
			return;
	}
	else
	{
		aes_key_nr = StrToInt(CmBxInterKeyNr->Text);
	}

	if (internal_key)
	{
		status = uFR_int_GetDesfireUid(aes_key_nr, aid, aid_key_nr, data, &data_length, &card_status, &exec_time);
	}
	else
	{
		status = uFR_int_GetDesfireUid_PK(aes_key_ext, aid, aid_key_nr, data, &data_length, &card_status, &exec_time);
	}

	if (status)
	{
		StatusBar1->SimpleText = "Communication error";

		as.printf("uFR_int_GetDesfireUid(): %s", UFR_Status2String(status));
		PRN();

		return;
	}

	StatusBar1->SimpleText = "Operation completed";

	Memo1->Clear();

	if (data_length == 11)
	{
		Memo1->Lines->Add("FACTORY CARD UID = " + IntToHex(data[0], 2) + IntToHex(data[1], 2) + IntToHex(data[2], 2)
				+ IntToHex(data[3], 2) + IntToHex(data[4], 2) + IntToHex(data[5], 2) + IntToHex(data[6], 2));
	}

	as = get_result_str(card_status, exec_time);
	PRN();
}
//---------------------------------------------------------------------------

void convert_str_to_key(AnsiString key_str, unsigned char *aes_key)
{
        char aes_key_part[8];
	unsigned long key_nr;
	unsigned char temp[4];
	unsigned char i;

       	char *aes_str = key_str.c_str();

	memset(aes_key_part, 0, 8);
	memcpy(aes_key_part, aes_str, 6);
	key_nr = strtol(aes_key_part, NULL, 16);
	memcpy(temp, (void *) &key_nr, 3);
	for (i = 0; i < 3; i++)
		aes_key[i] = temp[2 - i];

	memset(aes_key_part, 0, 8);
	memcpy(aes_key_part, &aes_str[6], 6);
	key_nr = strtol(aes_key_part, NULL, 16);
	memcpy(temp, (void *) &key_nr, 3);
	for (i = 0; i < 3; i++)
		aes_key[3 + i] = temp[2 - i];

	memset(aes_key_part, 0, 8);
	memcpy(aes_key_part, &aes_str[12], 6);
	key_nr = strtol(aes_key_part, NULL, 16);
	memcpy(temp, (void *) &key_nr, 3);
	for (i = 0; i < 3; i++)
		aes_key[6 + i] = temp[2 - i];

	memset(aes_key_part, 0, 8);
	memcpy(aes_key_part, &aes_str[18], 6);
	key_nr = strtol(aes_key_part, NULL, 16);
	memcpy(temp, (void *) &key_nr, 3);
	for (i = 0; i < 3; i++)
		aes_key[9 + i] = temp[2 - i];

	memcpy(aes_key_part, &aes_str[24], 6);
	key_nr = strtol(aes_key_part, NULL, 16);
	memcpy(temp, (void *) &key_nr, 3);
	for (i = 0; i < 3; i++)
		aes_key[12 + i] = temp[2 - i];

	memset(aes_key_part, 0, 8);
	memcpy(aes_key_part, &aes_str[30], 2);
	key_nr = strtol(aes_key_part, NULL, 16);
	aes_key[15] = key_nr;

}
//---------------------------------------------------------------------------

bool TForm1::prepare_key(unsigned char *aes_key)
{
	int aes_key_length;
	AnsiString key_text;

	EdtKey->Refresh();
	key_text = EdtKey->Text;
	aes_key_length = key_text.Length();
	if (aes_key_length != 32)
	{
		StatusBar1->SimpleText = "Key length must be 16 bytes";
		return false;
	}

        convert_str_to_key(key_text, aes_key);

	return true;
}

bool TForm1::prepare_new_key(unsigned char *aes_key)
{
	int aes_key_length;
	AnsiString key_text;

	EdtNewKey->Refresh();
	key_text = EdtNewKey->Text;
	aes_key_length = key_text.Length();
	if (aes_key_length != 32)
	{
		StatusBar1->SimpleText = "Key length must be 16 bytes";
		return false;
	}

        convert_str_to_key(key_text, aes_key);

	return true;
}

bool TForm1::prepare_old_key(unsigned char *aes_key)
{
	int aes_key_length;
	AnsiString key_text;

	EdtOldKey->Refresh();
	key_text = EdtOldKey->Text;
	aes_key_length = key_text.Length();
	if (aes_key_length != 32)
	{
		StatusBar1->SimpleText = "Key length must be 16 bytes";
		return false;
	}

        convert_str_to_key(key_text, aes_key);

	return true;
}

bool TForm1::prepare_int_key(unsigned char *aes_key)
{
	int aes_key_length;
	AnsiString key_text;

	EdtIntKey->Refresh();
	key_text = EdtIntKey->Text;
	aes_key_length = key_text.Length();
	if (aes_key_length != 32)
	{
		StatusBar1->SimpleText = "Key length must be 16 bytes";
		return false;
	}

	convert_str_to_key(key_text, aes_key);

	return true;
}

//----------------------------------------------------------------------------

void __fastcall TForm1::BtnKeyClick(TObject *Sender)
{
	UFR_STATUS status;

	unsigned char key_no;
	unsigned char aes_key[16];

	Memo1->Clear();

	key_no = StrToInt(CmBxEnterInterKey->Text);

	if (!prepare_int_key(aes_key))
		return;

	status = uFR_int_DesfireWriteAesKey(key_no, aes_key);

	if (status)
	{
		if (status == UFR_KEYS_LOCKED)
			Memo1->Lines->Add("Internal keys are locked");
		StatusBar1->SimpleText = "AES key did not store into reader";
	}
	else
	{
		Memo1->Lines->Add("OK");
		StatusBar1->SimpleText = "AES key stored into reader";
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
	BtnPortClick(Sender);
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

void __fastcall TForm1::BtnAppClick(TObject *Sender)
{
	UFR_STATUS status;
	unsigned short card_status;
	unsigned short exec_time;

	unsigned char setting, set_temp;
	unsigned long aid;
	unsigned char max_key_no;
	unsigned char authent_req;

	unsigned char aes_key_ext[16];
	unsigned char internal_key, aes_key_nr;

	set_temp = 0;
	if (ChBxSett_2->Checked)
		set_temp |= 0x04;
	if (ChBxCreate_2->Checked)
		set_temp |= 0x02;
	if (ChBxMaster_2->Checked)
		set_temp |= 0x01;

	switch (set_temp)
	{
	case 0:
		setting = DESFIRE_KEY_SET_CREATE_WITHOUT_AUTH_SET_CHANGE_KEY_CHANGE;
		break;
	case 1:
		setting = DESFIRE_KEY_SET_CREATE_WITHOUT_AUTH_SET_CHANGE_KEY_NOT_CHANGE;
		break;
	case 2:
		setting = DESFIRE_KEY_SET_CREATE_WITH_AUTH_SET_CHANGE_KEY_CHANGE;
		break;
	case 3:
		setting = DESFIRE_KEY_SET_CREATE_WITH_AUTH_SET_CHANGE_KEY_NOT_CHANGE;
		break;
	case 4:
		setting = DESFIRE_KEY_SET_CREATE_WITHOUT_AUTH_SET_NOT_CHANGE_KEY_CHANGE;
		break;
	case 5:
		setting = DESFIRE_KEY_SET_CREATE_WITHOUT_AUTH_SET_NOT_CHANGE_KEY_NOT_CHANGE;
		break;
	case 6:
		setting = DESFIRE_KEY_SET_CREATE_WITH_AUTH_SET_NOT_CHANGE_KEY_CHANGE;
		break;
	case 7:
		setting = DESFIRE_KEY_SET_CREATE_WITH_AUTH_SET_NOT_CHANGE_KEY_NOT_CHANGE;
		break;
	}

	aid = strtol(EdtAID_2->Text.c_str(), NULL, 16);

	max_key_no = StrToInt(CmBxAppMaxKeyNo->Text);

	if (ChBxAuth->Checked)
		authent_req = 1;
	else
		authent_req = 0;

	if (ChBxInterKey->Checked)
		internal_key = 1;
	else
		internal_key = 0;

	if (internal_key == 0)
	{
		if (!prepare_key(aes_key_ext))
			return;
	}
	else
	{
		aes_key_nr = StrToInt(CmBxInterKeyNr->Text);
	}

	Memo1->Clear();
	StatusBar1->SimpleText = "Operation in progress...";
	Update();

	if (authent_req)
	{
		if (internal_key)
		{
			status =
					uFR_int_DesfireCreateAesApplication(aes_key_nr, aid, setting, max_key_no, &card_status, &exec_time);
		}
		else
		{
			status =
					uFR_int_DesfireCreateAesApplication_PK(aes_key_ext, aid, setting, max_key_no, &card_status, &exec_time);
		}
	}
	else
	{
		status = uFR_int_DesfireCreateAesApplication_no_auth(aid, setting, max_key_no, &card_status, &exec_time);
	}

	if (status)
	{

		StatusBar1->SimpleText = "Communication error";

		as.printf("uFR_int_DesfireCreateApplication(): %s", UFR_Status2String(status));
		PRN();

		return;
	}

	StatusBar1->SimpleText = "Operation completed";

	as = get_result_str(card_status, exec_time);
	PRN();

	if (card_status == 3001)
	{
		Memo1->Lines->Add("Application created");
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BtnFileClick(TObject *Sender)
{
	UFR_STATUS status;
	unsigned short card_status;
	unsigned short exec_time;

	unsigned long aid;
	unsigned long file_size;
	unsigned char auth_req;
	int temp_int;
	unsigned char communication_settings;
	unsigned char file_id;
	unsigned char read_key_nr, write_key_nr, read_write_key_nr, change_key_nr;

	unsigned char aes_key_ext[16];
	unsigned char internal_key, aes_key_nr;
     long lower_limit, upper_limit, value;
     unsigned char limited_credit_enabled;

	aid = strtol(EdtAID->Text.c_str(), NULL, 16);

	read_key_nr = StrToInt(CmBxReadKey->Text);
	write_key_nr = StrToInt(CmBxWriteKey->Text);
	read_write_key_nr = StrToInt(CmBxRWKey->Text);
	change_key_nr = StrToInt(CmBxChangeKey->Text);

	file_id = StrToInt(CmBxFileId_2->Text);

	file_size = StrToInt(EdtFileSize->Text);

     lower_limit = StrToInt(EdtLowLim->Text);
     upper_limit = StrToInt(EdtUpLim->Text);
     value = StrToInt(EdtValue->Text);
     if(BxLimCred->Checked)
          limited_credit_enabled = 1;
     else
          limited_credit_enabled = 0;
     if(BxFreeGet->Checked)
          limited_credit_enabled |= 0x02;


	if (ChBxAuth->Checked)
		auth_req = 1;
	else
		auth_req = 0;

	temp_int = CmBxEncrType->ItemIndex;
	switch (temp_int)
	{
	case 0:
		communication_settings = 0;
		break;
	case 1:
		communication_settings = 1;
		break;
	case 2:
		communication_settings = 3;
		break;
	default:
		communication_settings = 0;
		break;
	}

	if (ChBxInterKey->Checked)
		internal_key = 1;
	else
		internal_key = 0;

	if (internal_key == 0)
	{
		if (!prepare_key(aes_key_ext))
			return;
	}
	else
	{
		aes_key_nr = StrToInt(CmBxInterKeyNr->Text);
	}

	Memo1->Clear();
	StatusBar1->SimpleText = "Operation in progress...";
	Update();

	if (auth_req)
	{
		if (internal_key)
		{
               if(RGFileType->ItemIndex == 0)
			     status = uFR_int_DesfireCreateStdDataFile(aes_key_nr, aid, file_id, file_size, read_key_nr, write_key_nr, read_write_key_nr, change_key_nr, communication_settings, &card_status, &exec_time);
               else
                    status = uFR_int_DesfireCreateValueFile(aes_key_nr, aid, file_id,
                         lower_limit, upper_limit, value, limited_credit_enabled,
                         read_key_nr, write_key_nr, read_write_key_nr, change_key_nr,
                         communication_settings, &card_status, &exec_time);
		}
		else
		{
               if(RGFileType->ItemIndex == 0)
			     status = uFR_int_DesfireCreateStdDataFile_PK(aes_key_ext, aid, file_id, file_size, read_key_nr, write_key_nr, read_write_key_nr, change_key_nr, communication_settings, &card_status, &exec_time);
               else
                    status = uFR_int_DesfireCreateValueFile_PK(aes_key_ext, aid, file_id,
                         lower_limit, upper_limit, value, limited_credit_enabled,
                         read_key_nr, write_key_nr, read_write_key_nr, change_key_nr,
                         communication_settings, &card_status, &exec_time);
		}
	}
	else
	{
          if(RGFileType->ItemIndex == 0)
		     status = uFR_int_DesfireCreateStdDataFile_no_auth(aid, file_id, file_size, read_key_nr, write_key_nr, read_write_key_nr, change_key_nr, communication_settings, &card_status, &exec_time);
          else
               status = uFR_int_DesfireCreateValueFile_no_auth(aid, file_id,
                    lower_limit, upper_limit, value, limited_credit_enabled,
                    read_key_nr, write_key_nr, read_write_key_nr, change_key_nr,
                    communication_settings, &card_status, &exec_time);
	}

	if (status)
	{

		StatusBar1->SimpleText = "Communication error";

		as.printf("uFR_int_DesfireCreateFile(): %s", UFR_Status2String(status));
		PRN();

		return;
	}

	StatusBar1->SimpleText = "Operation completed";

	as = get_result_str(card_status, exec_time);
	PRN();

	if (card_status == 3001)
	{
		Memo1->Lines->Add("File created");
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BtnCardKeyClick(TObject *Sender)
{
	UFR_STATUS status;
	unsigned short card_status;
	unsigned short exec_time;

	unsigned char aes_key_ext[16];
	unsigned char internal_key, aes_key_nr;
	unsigned long aid;
	unsigned char aid_key_nr_auth, aid_key_nr;
	unsigned char new_aes_key[16];
	unsigned char old_aes_key[16];

	Memo1->Clear();
	StatusBar1->SimpleText = "Operation in progress...";
	Update();

	aid = strtol(EdtAID->Text.c_str(), NULL, 16);

	aid_key_nr_auth = StrToInt(CmBxKeyNo->Text);

	aid_key_nr = StrToInt(CmBxAidKeyNr->Text);

	if (ChBxInterKey->Checked)
		internal_key = 1;
	else
		internal_key = 0;

	if (internal_key == 0)
	{
		if (!prepare_key(aes_key_ext))
			return;
	}
	else
	{
		aes_key_nr = StrToInt(CmBxInterKeyNr->Text);
	}

	if (!prepare_new_key(new_aes_key))
		return;

	if (aid_key_nr_auth != aid_key_nr)
	{
		if (!prepare_old_key(old_aes_key))
			return;
	}

	if (internal_key)
	{
		status =
				uFR_int_DesfireChangeAesKey(aes_key_nr, aid, aid_key_nr_auth, new_aes_key, aid_key_nr, old_aes_key, &card_status, &exec_time);
	}
	else
	{
		status =
				uFR_int_DesfireChangeAesKey_PK(aes_key_ext, aid, aid_key_nr_auth, new_aes_key, aid_key_nr, old_aes_key, &card_status, &exec_time);
	}

	if (status)
	{

		StatusBar1->SimpleText = "Communication error";

		as.printf("uFR_int_DesfireCreateAesKey(): %s", UFR_Status2String(status));
		PRN();

		return;
	}

	StatusBar1->SimpleText = "Operation completed";

	as = get_result_str(card_status, exec_time);
	PRN();

	if (card_status == 3001)
	{
		Memo1->Lines->Add("Key stored into card");
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BtnGetKeySetingsClick(TObject *Sender)
{
	UFR_STATUS status;
	unsigned short card_status;
	unsigned short exec_time;

	unsigned char setting, set_temp;
	unsigned char max_key_no;

	unsigned char aes_key_ext[16];
	unsigned char internal_key, aes_key_nr;
	unsigned long aid;

	Memo1->Clear();
	StatusBar1->SimpleText = "Operation in progress...";
	Update();

	aid = strtol(EdtAID->Text.c_str(), NULL, 16);

	if (ChBxInterKey->Checked)
		internal_key = 1;
	else
		internal_key = 0;

	if (internal_key == 0)
	{
		if (!prepare_key(aes_key_ext))
			return;
	}
	else
	{
		aes_key_nr = StrToInt(CmBxInterKeyNr->Text);
	}

	if (internal_key)
	{
		status = uFR_int_DesfireGetKeySettings(aes_key_nr, aid, &setting, &max_key_no, &card_status, &exec_time);
	}
	else
	{
		status = uFR_int_DesfireGetKeySettings_PK(aes_key_ext, aid, &setting, &max_key_no, &card_status, &exec_time);
	}

	if (status)
	{
		StatusBar1->SimpleText = "Communication error";

		as.printf("uFR_int_DesfireGetKeySettings(): %s", UFR_Status2String(status));
		PRN();

		return;
	}

	StatusBar1->SimpleText = "Operation completed";

	as = get_result_str(card_status, exec_time);
	PRN();

	if (card_status == 3001)
	{
		Memo1->Lines->Add("Read out key settings");
		Memo1->Lines->Add("Maximal number of keys into application:" + AnsiString(max_key_no));

		setting &= 0x0F;

		switch (setting)
		{
		case DESFIRE_KEY_SET_CREATE_WITHOUT_AUTH_SET_CHANGE_KEY_CHANGE:
			set_temp = 0;
			break;
		case DESFIRE_KEY_SET_CREATE_WITHOUT_AUTH_SET_CHANGE_KEY_NOT_CHANGE:
			set_temp = 1;
			break;
		case DESFIRE_KEY_SET_CREATE_WITH_AUTH_SET_CHANGE_KEY_CHANGE:
			set_temp = 2;
			break;
		case DESFIRE_KEY_SET_CREATE_WITH_AUTH_SET_CHANGE_KEY_NOT_CHANGE:
			set_temp = 3;
			break;
		case DESFIRE_KEY_SET_CREATE_WITHOUT_AUTH_SET_NOT_CHANGE_KEY_CHANGE:
			set_temp = 4;
			break;
		case DESFIRE_KEY_SET_CREATE_WITHOUT_AUTH_SET_NOT_CHANGE_KEY_NOT_CHANGE:
			set_temp = 5;
			break;
		case DESFIRE_KEY_SET_CREATE_WITH_AUTH_SET_NOT_CHANGE_KEY_CHANGE:
			set_temp = 6;
			break;
		case DESFIRE_KEY_SET_CREATE_WITH_AUTH_SET_NOT_CHANGE_KEY_NOT_CHANGE:
			set_temp = 7;
			break;
		}

		if (set_temp & 0x04)
			ChBxSett_1->Checked = TRUE;
		else
			ChBxSett_1->Checked = FALSE;
		if (set_temp & 0x02)
			ChBxCreate_1->Checked = TRUE;
		else
			ChBxCreate_1->Checked = FALSE;
		if (set_temp & 0x01)
			ChBxMaster_1->Checked = TRUE;
		else
			ChBxMaster_1->Checked = FALSE;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BtnChangeKeySettingClick(TObject *Sender)
{
	UFR_STATUS status;
	unsigned short card_status;
	unsigned short exec_time;

	unsigned char setting;

	unsigned char aes_key_ext[16];
	unsigned char internal_key, aes_key_nr, set_temp;
	unsigned long aid;

	Memo1->Clear();
	StatusBar1->SimpleText = "Operation in progress...";
	Update();

	set_temp = 0;
	if (ChBxSett_1->Checked)
		set_temp |= 0x04;
	if (ChBxCreate_1->Checked)
		set_temp |= 0x02;
	if (ChBxMaster_1->Checked)
		set_temp |= 0x01;

	switch (set_temp)
	{
	case 0:
		setting = DESFIRE_KEY_SET_CREATE_WITHOUT_AUTH_SET_CHANGE_KEY_CHANGE;
		break;
	case 1:
		setting = DESFIRE_KEY_SET_CREATE_WITHOUT_AUTH_SET_CHANGE_KEY_NOT_CHANGE;
		break;
	case 2:
		setting = DESFIRE_KEY_SET_CREATE_WITH_AUTH_SET_CHANGE_KEY_CHANGE;
		break;
	case 3:
		setting = DESFIRE_KEY_SET_CREATE_WITH_AUTH_SET_CHANGE_KEY_NOT_CHANGE;
		break;
	case 4:
		setting = DESFIRE_KEY_SET_CREATE_WITHOUT_AUTH_SET_NOT_CHANGE_KEY_CHANGE;
		break;
	case 5:
		setting = DESFIRE_KEY_SET_CREATE_WITHOUT_AUTH_SET_NOT_CHANGE_KEY_NOT_CHANGE;
		break;
	case 6:
		setting = DESFIRE_KEY_SET_CREATE_WITH_AUTH_SET_NOT_CHANGE_KEY_CHANGE;
		break;
	case 7:
		setting = DESFIRE_KEY_SET_CREATE_WITH_AUTH_SET_NOT_CHANGE_KEY_NOT_CHANGE;
		break;
	}

	aid = strtol(EdtAID->Text.c_str(), NULL, 16);

	if (ChBxInterKey->Checked)
		internal_key = 1;
	else
		internal_key = 0;

	if (internal_key == 0)
	{
		if (!prepare_key(aes_key_ext))
			return;
	}
	else
	{
		aes_key_nr = StrToInt(CmBxInterKeyNr->Text);
	}

	if (internal_key)
	{
		status = uFR_int_DesfireChangeKeySettings(aes_key_nr, aid, setting, &card_status, &exec_time);
	}
	else
	{
		status = uFR_int_DesfireChangeKeySettings_PK(aes_key_ext, aid, setting, &card_status, &exec_time);
	}

	if (status)
	{
		StatusBar1->SimpleText = "Communication error";

		as.printf("uFR_int_DesfireChangeKeySettings(): %s", UFR_Status2String(status));
		PRN();

		return;
	}

	StatusBar1->SimpleText = "Operation completed";

	as = get_result_str(card_status, exec_time);
	PRN();

	if (card_status == 3001)
	{
		Memo1->Lines->Add("Key settings stored into card");
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BtnDelAppClick(TObject *Sender)
{
	UFR_STATUS status;
	unsigned short card_status;
	unsigned short exec_time;

	unsigned long aid;

	unsigned char aes_key_ext[16];
	unsigned char internal_key, aes_key_nr;

	aid = strtol(EdtAID_2->Text.c_str(), NULL, 16);

	if (ChBxInterKey->Checked)
		internal_key = 1;
	else
		internal_key = 0;

	if (internal_key == 0)
	{
		if (!prepare_key(aes_key_ext))
			return;
	}
	else
	{
		aes_key_nr = StrToInt(CmBxInterKeyNr->Text);
	}

	Memo1->Clear();
	StatusBar1->SimpleText = "Operation in progress...";
	Update();

	if (internal_key)
	{
		status = uFR_int_DesfireDeleteApplication(aes_key_nr, aid, &card_status, &exec_time);
	}
	else
	{
		status = uFR_int_DesfireDeleteApplication_PK(aes_key_ext, aid, &card_status, &exec_time);
	}

	if (status)
	{
		StatusBar1->SimpleText = "Communication error";

		as.printf("uFR_int_DesfireDeleteApplication(): %s", UFR_Status2String(status));
		PRN();

		return;
	}

	StatusBar1->SimpleText = "Operation completed";
	Update();

	as = get_result_str(card_status, exec_time);
	PRN();

	if (card_status == 3001)
	{
		Memo1->Lines->Add("Application deleted");
		PRN();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BtnDelFileClick(TObject *Sender)
{
	UFR_STATUS status;
	unsigned short card_status;
	unsigned short exec_time;

	unsigned char auth_req, file_no;

	unsigned char aes_key_ext[16];
	unsigned char internal_key, aes_key_nr;
	unsigned long aid;

	file_no = StrToInt(CmBxFileId_2->Text);
	if (ChBxAuth->Checked)
		auth_req = 1;
	else
		auth_req = 0;

	if (ChBxInterKey->Checked)
		internal_key = 1;
	else
		internal_key = 0;

	if (internal_key == 0)
	{
		if (!prepare_key(aes_key_ext))
			return;
	}
	else
	{
		aes_key_nr = StrToInt(CmBxInterKeyNr->Text);
	}

	aid = strtol(EdtAID->Text.c_str(), NULL, 16);

	Memo1->Clear();
	StatusBar1->SimpleText = "Operation in progress...";
	Update();

	if (auth_req)
	{
		if (internal_key)
		{
			status = uFR_int_DesfireDeleteFile(aes_key_nr, aid, file_no, &card_status, &exec_time);
		}
		else
		{
			status = uFR_int_DesfireDeleteFile_PK(aes_key_ext, aid, file_no, &card_status, &exec_time);
		}
	}
	else
	{
		status = uFR_int_DesfireDeleteFile_no_auth(aid, file_no, &card_status, &exec_time);
	}

	if (status)
	{
		StatusBar1->SimpleText = "Communication error";

		as.printf("uFR_int_DesfireDeleteFile(): %s", UFR_Status2String(status));
		PRN();

		return;
	}

	StatusBar1->SimpleText = "Operation completed";
	Update();

	as = get_result_str(card_status, exec_time);
	PRN();

	if (card_status == 3001)
	{
		Memo1->Lines->Add("File deleted");
		PRN();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BtnRndUidClick(TObject *Sender)
{
	UFR_STATUS status;
	unsigned short card_status;
	unsigned short exec_time;

	unsigned char internal_key, aes_key_nr;
	unsigned char aes_key_ext[16];

	if (ChBxInterKey->Checked)
		internal_key = 1;
	else
		internal_key = 0;

	if (internal_key == 0)
	{
		if (!prepare_key(aes_key_ext))
			return;
	}
	else
	{
		aes_key_nr = StrToInt(CmBxInterKeyNr->Text);
	}

	Memo1->Clear();
	StatusBar1->SimpleText = "Operation in progress...";
	Update();

	if (internal_key)
	{
		status = uFR_int_DesfireSetConfiguration(aes_key_nr, 1, 0, &card_status, &exec_time);
	}
	else
	{
		status = uFR_int_DesfireSetConfiguration_PK(aes_key_ext, 1, 0, &card_status, &exec_time);
	}

	if (status)
	{
		StatusBar1->SimpleText = "Communication error";

		as.printf("uFR_int_DesfireSetConfiguration(): %s", UFR_Status2String(status));
		PRN();

		return;
	}

	StatusBar1->SimpleText = "Operation completed";

	as = get_result_str(card_status, exec_time);
	PRN();

	if (card_status == 3001)
	{
		Memo1->Lines->Add("Ranom ID is set");
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BtnFileReadClick(TObject *Sender)
{
	UFR_STATUS status;
	unsigned short card_status = 0;
	unsigned short exec_time;

	unsigned short file_length;
	unsigned char communication_settings;
	FILE *stream;
	unsigned char file_data[10000];

	unsigned char aes_key_ext[16];
	unsigned char internal_key, aes_key_nr;
	unsigned long aid;
	unsigned char file_id, auth_req, aid_key_nr;

	if (!SaveDialog1->Execute())
	{
		StatusBar1->SimpleText = "File is not selected";
		return;
	}

	stream = fopen(SaveDialog1->FileName.c_str(), "wb");

	Memo1->Clear();
	StatusBar1->SimpleText = "Operation in progress...";
	Update();

	file_length = StrToInt(EdtFileSize_2->Text);

	switch (CmBxEncrType_2->ItemIndex)
	{
	case 0:
		communication_settings = 0;
		break;
	case 1:
		communication_settings = 1;
		break;
	case 2:
		communication_settings = 3;
		break;
	default:
		communication_settings = 0;
		break;
	}

	aid = strtol(EdtAID->Text.c_str(), NULL, 16);

	aid_key_nr = StrToInt(CmBxKeyNo->Text);

	file_id = StrToInt(CmBxFileNr->Text);

	if (ChBxInterKey->Checked)
		internal_key = 1;
	else
		internal_key = 0;

	if (internal_key == 0)
	{
		if (!prepare_key(aes_key_ext))
			return;
	}
	else
	{
		aes_key_nr = StrToInt(CmBxInterKeyNr->Text);
	}

	if (ChBxAuth->Checked)
		auth_req = 1;
	else
		auth_req = 0;

	if (auth_req)
	{
		if (internal_key)
		{
			status =
					uFR_int_DesfireReadStdDataFile(aes_key_nr, aid, aid_key_nr, file_id, 0, file_length, communication_settings, file_data, &card_status, &exec_time);
		}
		else
		{
			status =
					uFR_int_DesfireReadStdDataFile_PK(aes_key_ext, aid, aid_key_nr, file_id, 0, file_length, communication_settings, file_data, &card_status, &exec_time);
		}
	}
	else
	{
		status =
				uFR_int_DesfireReadStdDataFile_no_auth(aid, aid_key_nr, file_id, 0, file_length, communication_settings, file_data, &card_status, &exec_time);
	}

	if (status)
	{
		StatusBar1->SimpleText = "Communication error";

		as.printf("uFR_int_DesfireReadData(): %s", UFR_Status2String(status));
		PRN();

		return;
	}

	fwrite(file_data, file_length, 1, stream);
	fclose(stream);

	StatusBar1->SimpleText = "Operation completed";

	as = get_result_str(card_status, exec_time);
	PRN();

	if (card_status == 3001)
		Memo1->Lines->Add("File was read");
	else
		Memo1->Lines->Add("File did not read");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BtnFileWriteClick(TObject *Sender)
{
	UFR_STATUS status;
	unsigned short card_status = 0;
	unsigned short exec_time;

	unsigned char file_data[10000];
	unsigned short file_length;
	unsigned char communication_settings;
	int temp;

	unsigned char aes_key_ext[16];
	unsigned char internal_key, aes_key_nr;
	unsigned long aid;
	unsigned char file_id, auth_req, aid_key_nr;

	FILE *stream;

	if (!OpenDialog1->Execute())
	{
		StatusBar1->SimpleText = "File did not load";
		return;
	}

	stream = fopen(OpenDialog1->FileName.c_str(), "rb");

	long curpos, length;

	curpos = ftell(stream);
	fseek(stream, 0L, SEEK_END);
	length = ftell(stream);
	fseek(stream, curpos, SEEK_SET);
	EdtFileSize_2->Text = AnsiString(length);

	Memo1->Clear();
	StatusBar1->SimpleText = "Operation in progress...";
	Update();

	file_length = StrToInt(EdtFileSize_2->Text);

	temp = CmBxEncrType_2->ItemIndex;
	switch (temp)
	{
	case 0:
		communication_settings = 0;
		break;
	case 1:
		communication_settings = 1;
		break;
	case 2:
		communication_settings = 3;
		break;
	default:
		communication_settings = 0;
		break;
	}

	aid = strtol(EdtAID->Text.c_str(), NULL, 16);

	aid_key_nr = StrToInt(CmBxKeyNo->Text);

	file_id = StrToInt(CmBxFileNr->Text);

	if (ChBxInterKey->Checked)
		internal_key = 1;
	else
		internal_key = 0;

	if (internal_key == 0)
	{
		if (!prepare_key(aes_key_ext))
			return;
	}
	else
	{
		aes_key_nr = StrToInt(CmBxInterKeyNr->Text);
	}

	if (ChBxAuth->Checked)
		auth_req = 1;
	else
		auth_req = 0;

	fread(file_data, file_length, 1, stream);

	fclose(stream);

	if (auth_req)
	{
		if (internal_key)
		{
			status =
					uFR_int_DesfireWriteStdDataFile(aes_key_nr, aid, aid_key_nr, file_id, 0, file_length, communication_settings, file_data, &card_status, &exec_time);
		}
		else
		{
			status =
					uFR_int_DesfireWriteStdDataFile_PK(aes_key_ext, aid, aid_key_nr, file_id, 0, file_length, communication_settings, file_data, &card_status, &exec_time);
		}
	}
	else
	{
		status =
				uFR_int_DesfireWriteStdDataFile_no_auth(aid, aid_key_nr, file_id, 0, file_length, communication_settings, file_data, &card_status, &exec_time);
	}

	if (status)
	{
		StatusBar1->SimpleText = "Communication error";

		as.printf("uFR_int_DesfireWriteData(): %s", UFR_Status2String(status));
		PRN();

		return;
	}

	StatusBar1->SimpleText = "Operation completed";

	as = get_result_str(card_status, exec_time);
	PRN();

	if (card_status == 3001)
	{
		Memo1->Lines->Add("File stored into card");
	}
	else
	{
		Memo1->Lines->Add("File did not store");
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BtnFormatClick(TObject *Sender)
{
	UFR_STATUS status;
	unsigned short card_status;
	unsigned short exec_time;

	unsigned char internal_key, aes_key_nr;
	unsigned char aes_key_ext[16];

	if (ChBxInterKey->Checked)
		internal_key = 1;
	else
		internal_key = 0;

	if (internal_key == 0)
	{
		if (!prepare_key(aes_key_ext))
			return;
	}
	else
	{
		aes_key_nr = StrToInt(CmBxInterKeyNr->Text);
	}

	Memo1->Clear();
	StatusBar1->SimpleText = "Operation in progress...";
	Update();

	if (internal_key)
	{
		status = uFR_int_DesfireFormatCard(aes_key_nr, &card_status, &exec_time);
	}
	else
	{
		status = uFR_int_DesfireFormatCard_PK(aes_key_ext, &card_status, &exec_time);
	}

	if (status)
	{
		StatusBar1->SimpleText = "Komanda nije poslana || "
				"Potvrda nije primljena";

		as.printf("uFR_int_DesfireFormatCard(): %s", UFR_Status2String(status));
		PRN();

		return;
	}

	StatusBar1->SimpleText = "Operation is completed";

	as = get_result_str(card_status, exec_time);
	PRN();

	if (card_status == 3001)
	{
		Memo1->Lines->Add("Card is formatted");
	}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::BtnFreeMemClick(TObject *Sender)
{
	UFR_STATUS status;
	unsigned short card_status;
	unsigned short exec_time;

	uint32_t mem_size;

	Memo1->Clear();
	StatusBar1->SimpleText = "Operation in progress...";
	Update();

	status = uFR_int_DesfireFreeMem(&mem_size, &card_status, &exec_time);

	if (status)
	{
		StatusBar1->SimpleText = "Communication error";

		as.printf("uFR_int_DesfireFreeMem(): %s", UFR_Status2String(status));
		PRN();

		return;
	}

	StatusBar1->SimpleText = "Operation is completed";
	Update();

	as = get_result_str(card_status, exec_time);
	PRN();

	if (card_status == 3001)
	{
		as.printf("Free memory into card is %d bytes", mem_size);
		PRN();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BtnNewCardClick(TObject *Sender)
{
 	unsigned long status;
	unsigned char i, res;

	Memo1->Clear();
	StatusBar1->SimpleText = "Card operation is in progress ...";
	Update();

	res = 0;
	for (i = 0; i < 10; i++)
	{
		status = DES_to_AES_key_type();
		if (!status)
		{
			StatusBar1->SimpleText = "Operation successful";
			Memo1->Lines->Add("Key type is changed to AES");
			Memo1->Lines->Add("New AES key is 00000000000000000000000000000000");
			res = 1;
			ReaderUISignal(3, 3);
			break;
		}
	}

	if (res == 0)
	{
		StatusBar1->SimpleText = "Operation failed";
		Memo1->Lines->Add("Key type is not changed");
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BtnKeyLockClick(TObject *Sender)
{
	unsigned long status;
	AnsiString pass_text;

	Memo1->Clear();

	pass_text = EdtKeyPass->Text;
	if (pass_text.Length() != 8)
	{
		StatusBar1->SimpleText = "Pasword mus be 8 character length";
		return;
	}

	char *pass_array = pass_text.c_str();

	status = ReaderKeysLock(pass_array);

	if (status == 0)
	{
		Memo1->Lines->Add("Internal keys are locked");
		StatusBar1->SimpleText = "Operation success";
	}
	else
	{
		if (status == UFR_KEYS_LOCKED)
			Memo1->Lines->Add("Internal keys already locked");
		else if (status == UFR_CAN_NOT_LOCK_DEVICE || status == UFR_DEVICE_EEPROM_BUSY)
			Memo1->Lines->Add("Internal keys did not lock");
		StatusBar1->SimpleText = "Operation failed";
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BtnKeyUnlockClick(TObject *Sender)
{
	unsigned long status;
	AnsiString pass_text;

	Memo1->Clear();

	pass_text = EdtKeyPass->Text;
	if (pass_text.Length() != 8)
	{
		StatusBar1->SimpleText = "Pasword mus be 8 character length";
		return;
	}

	char *pass_array = pass_text.c_str();

	status = ReaderKeysUnlock(pass_array);

	if (status == 0)
	{
		Memo1->Lines->Add("Internal keys are unlocked");
		StatusBar1->SimpleText = "Operation success";
	}
	else
	{
		if (status == UFR_KEYS_UNLOCKED)
			Memo1->Lines->Add("Internal keys already unlocked");
		else if (status == UFR_WRONG_PASSWORD)
			Memo1->Lines->Add("Wrong password");
		else if (status == UFR_CAN_NOT_UNLOCK_DEVICE || status == UFR_DEVICE_EEPROM_BUSY)
			Memo1->Lines->Add("Internal keys did not unlock");

		StatusBar1->SimpleText = "Operation failed";
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnSetSpeedClick(TObject *Sender)
{
     SetSpeedPermanently(cbTxSpeed->ItemIndex, cbRxSpeed->ItemIndex);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnGetSpeedClick(TObject *Sender)
{
     unsigned char tx_speed, rx_speed;

     GetSpeedParameters(&tx_speed, &rx_speed);
     cbTxSpeed->ItemIndex = tx_speed;
     cbRxSpeed->ItemIndex = rx_speed;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RGFileTypeClick(TObject *Sender)
{
    if(RGFileType->ItemIndex == 0)
    {
          EdtFileSize->Enabled = true;
          EdtLowLim->Enabled = false;
          EdtUpLim->Enabled = false;
          EdtValue->Enabled = false;
          BxLimCred->Enabled = false;
          BxFreeGet->Enabled = false;
    }
    else
    {
          EdtFileSize->Enabled = false;
          EdtLowLim->Enabled = true;
          EdtUpLim->Enabled = true;
          EdtValue->Enabled = true;
          BxLimCred->Enabled = true;
          BxFreeGet->Enabled = true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BtnReadValueClick(TObject *Sender)
{
	UFR_STATUS status;
	unsigned short card_status = 0;
	unsigned short exec_time;

	unsigned char communication_settings;
	unsigned char aes_key_ext[16];
	unsigned char internal_key, aes_key_nr;
	unsigned long aid;
	unsigned char file_id, auth_req, aid_key_nr;
     int file_value;

	Memo1->Clear();
	StatusBar1->SimpleText = "Operation in progress...";
	Update();

	switch (CmBxEncrType_3->ItemIndex)
	{
	case 0:
		communication_settings = 0;
		break;
	case 1:
		communication_settings = 1;
		break;
	case 2:
		communication_settings = 3;
		break;
	default:
		communication_settings = 0;
		break;
	}

	aid = strtol(EdtAID->Text.c_str(), NULL, 16);

	aid_key_nr = StrToInt(CmBxKeyNo->Text);

	file_id = StrToInt(CmBxFileNr->Text);

	if (ChBxInterKey->Checked)
		internal_key = 1;
	else
		internal_key = 0;

	if (internal_key == 0)
	{
		if (!prepare_key(aes_key_ext))
			return;
	}
	else
	{
		aes_key_nr = StrToInt(CmBxInterKeyNr->Text);
	}

	if (ChBxAuth->Checked)
		auth_req = 1;
	else
		auth_req = 0;

	if (auth_req)
	{
		if (internal_key)
		{
			status =  uFR_int_DesfireReadValueFile(aes_key_nr, aid, aid_key_nr, file_id,
                              communication_settings, &file_value, &card_status, &exec_time);
		}
		else
		{
			status = 	uFR_int_DesfireReadValueFile_PK(aes_key_ext, aid, aid_key_nr, file_id,
                              communication_settings, &file_value, &card_status, &exec_time);
		}
	}
	else
	{
		status =  uFR_int_DesfireReadValueFile_no_auth(aid, aid_key_nr, file_id,
                              communication_settings, &file_value, &card_status, &exec_time);
	}

     EdtFileValue->Text = "";
	if (status)
	{
		StatusBar1->SimpleText = "Communication error";

		as.printf("uFR_int_DesfireReadValue(): %s", UFR_Status2String(status));
		PRN();

		return;
	}

	StatusBar1->SimpleText = "Operation completed";

	as = get_result_str(card_status, exec_time);
	PRN();

	if (card_status == 3001)
     {
		Memo1->Lines->Add("File value was read");
          EdtFileValue->Text = AnsiString(file_value);
     }
	else
		Memo1->Lines->Add("File value did not read");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BtnIncreaseClick(TObject *Sender)
{
    	UFR_STATUS status;
	unsigned short card_status = 0;
	unsigned short exec_time;

	unsigned char communication_settings;
	unsigned char aes_key_ext[16];
	unsigned char internal_key, aes_key_nr;
	unsigned long aid;
	unsigned char file_id, auth_req, aid_key_nr;
     unsigned int file_value;

	Memo1->Clear();
	StatusBar1->SimpleText = "Operation in progress...";
	Update();

	switch (CmBxEncrType_3->ItemIndex)
	{
	case 0:
		communication_settings = 0;
		break;
	case 1:
		communication_settings = 1;
		break;
	case 2:
		communication_settings = 3;
		break;
	default:
		communication_settings = 0;
		break;
	}

	aid = strtol(EdtAID->Text.c_str(), NULL, 16);

	aid_key_nr = StrToInt(CmBxKeyNo->Text);

	file_id = StrToInt(CmBxFileNr->Text);

     file_value = StrToInt(EdtFileValue->Text);

	if (ChBxInterKey->Checked)
		internal_key = 1;
	else
		internal_key = 0;

	if (internal_key == 0)
	{
		if (!prepare_key(aes_key_ext))
			return;
	}
	else
	{
		aes_key_nr = StrToInt(CmBxInterKeyNr->Text);
	}

	if (ChBxAuth->Checked)
		auth_req = 1;
	else
		auth_req = 0;

	if (auth_req)
	{
		if (internal_key)
		{
			status =  uFR_int_DesfireIncreaseValueFile(aes_key_nr, aid, aid_key_nr, file_id,
                              communication_settings, file_value, &card_status, &exec_time);
		}
		else
		{
			status = 	uFR_int_DesfireIncreaseValueFile_PK(aes_key_ext, aid, aid_key_nr, file_id,
                              communication_settings, file_value, &card_status, &exec_time);
		}
	}
	else
	{
		status =  uFR_int_DesfireIncreaseValueFile_no_auth(aid, aid_key_nr, file_id,
                              communication_settings, file_value, &card_status, &exec_time);
	}

     if (status)
	{
		StatusBar1->SimpleText = "Communication error";

		as.printf("uFR_int_DesfireIncreaseValue(): %s", UFR_Status2String(status));
		PRN();

		return;
	}

	StatusBar1->SimpleText = "Operation completed";

	as = get_result_str(card_status, exec_time);
	PRN();

	if (card_status == 3001)
          Memo1->Lines->Add("File value was increased");
     else
		Memo1->Lines->Add("File value did not increase");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BtnDecreaseClick(TObject *Sender)
{
        	UFR_STATUS status;
	unsigned short card_status = 0;
	unsigned short exec_time;

	unsigned char communication_settings;
	unsigned char aes_key_ext[16];
	unsigned char internal_key, aes_key_nr;
	unsigned long aid;
	unsigned char file_id, auth_req, aid_key_nr;
     unsigned int file_value;

	Memo1->Clear();
	StatusBar1->SimpleText = "Operation in progress...";
	Update();

	switch (CmBxEncrType_3->ItemIndex)
	{
	case 0:
		communication_settings = 0;
		break;
	case 1:
		communication_settings = 1;
		break;
	case 2:
		communication_settings = 3;
		break;
	default:
		communication_settings = 0;
		break;
	}

	aid = strtol(EdtAID->Text.c_str(), NULL, 16);

	aid_key_nr = StrToInt(CmBxKeyNo->Text);

	file_id = StrToInt(CmBxFileNr->Text);

     file_value = StrToInt(EdtFileValue->Text);

	if (ChBxInterKey->Checked)
		internal_key = 1;
	else
		internal_key = 0;

	if (internal_key == 0)
	{
		if (!prepare_key(aes_key_ext))
			return;
	}
	else
	{
		aes_key_nr = StrToInt(CmBxInterKeyNr->Text);
	}

	if (ChBxAuth->Checked)
		auth_req = 1;
	else
		auth_req = 0;

	if (auth_req)
	{
		if (internal_key)
		{
			status =  uFR_int_DesfireDecreaseValueFile(aes_key_nr, aid, aid_key_nr, file_id,
                              communication_settings, file_value, &card_status, &exec_time);
		}
		else
		{
			status = 	uFR_int_DesfireDecreaseValueFile_PK(aes_key_ext, aid, aid_key_nr, file_id,
                              communication_settings, file_value, &card_status, &exec_time);
		}
	}
	else
	{
		status =  uFR_int_DesfireDecreaseValueFile_no_auth(aid, aid_key_nr, file_id,
                              communication_settings, file_value, &card_status, &exec_time);
	}

     if (status)
	{
		StatusBar1->SimpleText = "Communication error";

		as.printf("uFR_int_DesfireDecreaseValue(): %s", UFR_Status2String(status));
		PRN();

		return;
	}

	StatusBar1->SimpleText = "Operation completed";

	as = get_result_str(card_status, exec_time);
	PRN();

	if (card_status == 3001)
          Memo1->Lines->Add("File value was decreased");
     else
		Memo1->Lines->Add("File value did not decrease");
}
//---------------------------------------------------------------------------

