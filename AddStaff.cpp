//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AddStaff.h"
#include "ChooseCity.h"
#include "Staff.h"
#include "DataMod.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAddStaffForm *AddStaffForm;
//---------------------------------------------------------------------------
__fastcall TAddStaffForm::TAddStaffForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TAddStaffForm::FormShow(TObject *Sender)
{
        for(int i=0; i<PageControl1->PageCount; i++)
        {
                PageControl1->Pages[i]->TabVisible=false;
        }
        PageControl1->ActivePage = TabSheet1;
}
//---------------------------------------------------------------------------

void __fastcall TAddStaffForm::NextBtn1Click(TObject *Sender)
{
        if(FNameEdit->Text=="" || LNameEdit->Text=="")
                ShowMessage("Моля, попълнете всички полета със *!");
        else
                PageControl1->ActivePage=TabSheet2;
}
//---------------------------------------------------------------------------

void __fastcall TAddStaffForm::BackBtn1Click(TObject *Sender)
{
        PageControl1->ActivePage=TabSheet1;        
}
//---------------------------------------------------------------------------

void __fastcall TAddStaffForm::NextBtn2Click(TObject *Sender)
{
        TLocateOptions Opts;
        DModule->StaffTbl->Locate("STAFF_ID", DModule->CurrentStaffID, Opts);
        if(DModule->StaffTbl->FieldByName("IS_ADMIN")->AsInteger == 1)
                AdminCheck->Visible=true;
        if(TelEdit->Text=="" || CityEdit->Text=="" || StreetEdit->Text=="")
                ShowMessage("Моля, попълнете всички полета със *!");
        else
                PageControl1->ActivePage=TabSheet3;
}
//---------------------------------------------------------------------------

void __fastcall TAddStaffForm::BackBtn2Click(TObject *Sender)
{
        PageControl1->ActivePage=TabSheet2;
}
//---------------------------------------------------------------------------

void __fastcall TAddStaffForm::SaveBtnClick(TObject *Sender)
{
        DModule->Query->Close();
        DModule->Query->SQL->Text =
          "SELECT * FROM STAFF_TBL WHERE USERNAME = '" + UNameEdit->Text.Trim() + "'";
        DModule->Query->Open();
        if(DModule->StaffTbl->FieldByName("USERNAME")->AsString == UNameEdit->Text &&
        StaffForm->ActiveControl==StaffForm->NewStaffButton)
                ShowMessage("Има служител с такова потребителско име!");
        else if(UNameEdit->Text=="" || PassEdit->Text=="" || ConfPassEdit->Text=="")
                ShowMessage("Моля, попълнете всички полета!");
        else if(PassEdit->Text != ConfPassEdit->Text)
                ShowMessage("Паролите не съвпадат!");
        else
                ModalResult = mrOk;
}
//---------------------------------------------------------------------------

void __fastcall TAddStaffForm::CityEditClick(TObject *Sender)
{
        if(ChooseCityForm->ShowModal() != mrOk)
                return;
        CityEdit->Text=DModule->CityTbl->FieldByName("CITY_NAME")->AsString;
        SCityID = DModule->CityTbl->FieldByName("CITY_ID")->AsInteger;
}
//---------------------------------------------------------------------------

void __fastcall TAddStaffForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
        StaffForm->ActiveControl = alNone;        
}
//---------------------------------------------------------------------------

void __fastcall TAddStaffForm::TelEditKeyPress(TObject *Sender, char &Key)
{
   if(!(Key == '0' || Key == '1' || Key == '2' ||
       Key == '3' || Key == '4' || Key == '5' ||
       Key == '6' || Key == '7' || Key == '8' ||
       Key == '9' || Key == '\n' ||
       Key == '\b' || Key == '\t'))
   {
    Key = 0;
   }
}
//---------------------------------------------------------------------------

