//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AddInvMas.h"
#include "DataMod.h"
#include "NewInvoice.h"
#include "ChoosePartner.h"
#include "Deliveries.h"
#include "ZooInfoSyst.h"
#include "ChooseStaff.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAddInvMasForm *AddInvMasForm;
//---------------------------------------------------------------------------
__fastcall TAddInvMasForm::TAddInvMasForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TAddInvMasForm::DelivererEditClick(TObject *Sender)
{
        if(RadioGroup1->ItemIndex==0)
        {
        if(ChoosePartnerForm->ShowModal() != mrOk)
                return;
        DelivererEdit->Text = DModule->QPartner->FieldByName("NAME")->AsString;
        DelivererID = DModule->QPartner->FieldByName("PARTNER_ID")->AsInteger;
        }
}
//---------------------------------------------------------------------------

void __fastcall TAddInvMasForm::RadioGroup1Click(TObject *Sender)
{
        TLocateOptions Opts;
        DModule->PartnerTbl->First();
        if(RadioGroup1->ItemIndex==0)
        {
                DelivererEdit->Text = "";
                RecipientEdit->Text = DModule->PartnerTbl->FieldByName("NAME")->AsString;
                RecipientID = DModule->PartnerTbl->FieldByName("PARTNER_ID")->AsInteger;
                RecipientEdit->ReadOnly=true;
        }
        else if(RadioGroup1->ItemIndex==1)
        {
                RecipientEdit->Text = "";
                DelivererEdit->Text = DModule->PartnerTbl->FieldByName("NAME")->AsString;
                DelivererID = DModule->PartnerTbl->FieldByName("PARTNER_ID")->AsInteger;
                DelivererEdit->ReadOnly=true;
        }
        else if(RadioGroup1->ItemIndex==2 &&
        NewInvoiceForm->ActiveControl == NewInvoiceForm->BitBtn4)
        {
                DeliveryForm->NewDeliveryButton->Visible=false;
                DeliveryForm->BitBtn1->Visible=true;

                if(DeliveryForm->ShowModal() != mrOk)
                        return;
                DelID = DeliveryForm->QDelMas->FieldByName("DELIVERY_MASTER_ID")->AsInteger;
                DelivererEdit->Text = DModule->PartnerTbl->FieldByName("NAME")->AsString;
                DelivererID = DModule->PartnerTbl->FieldByName("PARTNER_ID")->AsInteger;
                DelivererEdit->ReadOnly=true;
                DModule->OrdMasTbl->Locate("ORDER_MASTER_ID", DeliveryForm->QDelMas->FieldByName("ORDER_ID")->AsInteger, Opts);
                DModule->PartnerTbl->Locate("PARTNER_ID", DModule->OrdMasTbl->FieldByName("PARTNER_ID")->AsInteger, Opts);
                RecipientEdit->Text = DModule->PartnerTbl->FieldByName("NAME")->AsString;
                RecipientID = DModule->PartnerTbl->FieldByName("PARTNER_ID")->AsInteger;
                RecipientEdit->ReadOnly=true;
        }
}
//---------------------------------------------------------------------------

void __fastcall TAddInvMasForm::RecipientEditClick(TObject *Sender)
{
        if(RadioGroup1->ItemIndex==1)
        {
        if(ChoosePartnerForm->ShowModal() != mrOk)
                return;
        RecipientEdit->Text = DModule->QPartner->FieldByName("NAME")->AsString;
        RecipientID = DModule->QPartner->FieldByName("PARTNER_ID")->AsInteger;
        }
}
//---------------------------------------------------------------------------

void __fastcall TAddInvMasForm::OkBtnClick(TObject *Sender)
{
        if(StaffEdit->Text=="" || DelivererEdit->Text=="" || RecipientEdit->Text=="")
        {
                ShowMessage("Моля, попълнете всички полета!");
                return;
        }
        
        ModalResult = mrOk;
}
//---------------------------------------------------------------------------

void __fastcall TAddInvMasForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
        AddInvMasForm->RadioGroup1->Enabled=true;
        NewInvoiceForm->ActiveControl = alNone;
}
//---------------------------------------------------------------------------

