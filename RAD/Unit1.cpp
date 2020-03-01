//---------------------------------------------------------------------------

#include <vcl.h>

#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VirtualTrees"
#pragma resource "*.dfm"
TForm1 *Form1;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent *Owner)
        : TForm(Owner) {
    UserStringTree->NodeDataSize = sizeof(UserNode);
    ShowButton->Enabled = false;
    ClearButton->Enabled = false;
    PopulateButton->Enabled = false;
    RemoveButton->Enabled = false;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TForm1::ShowButtonClick(TObject *Sender) {
    TStringList *names;
    TField *currentField;
    String currentLine;
    String query;

    query = "SELECT * FROM PERSON;";
    try {
        // Assign the query to the object SQLQuery1.
        SQLQuery1->SQL->Text = query;
        SQLQuery1->Active = true;
    }
    catch (Exception &E) {
        Label1->Caption = "Exception raised with message" + E.Message;
    }


    if (!SQLQuery1->IsEmpty()) {
        SQLQuery1->First();
        names = new TStringList;
        try {
            SQLQuery1->GetFieldNames(names);
            UserStringTree->Clear();
            while (!SQLQuery1->Eof) {
                PVirtualNode newNode = UserStringTree->AddChild(UserStringTree->RootNode);
                UserNode *nodeData = (UserNode *) UserStringTree->GetNodeData(newNode);
                nodeData->Id = SQLQuery1->FieldByName(L"ID")->AsInteger;
                nodeData->Name = SQLQuery1->FieldByName(L"NAME")->AsString;
                nodeData->Surname = SQLQuery1->FieldByName(L"SURNAME")->AsString;
                nodeData->Age = SQLQuery1->FieldByName(L"AGE")->AsInteger;

                SQLQuery1->Next();
            }
        }
        catch (Exception &E) {
            Label1->Caption = "Exception raised with message" + E.Message;
        }
    }

    names->Free();
    Label1->Caption = "Got all the data for you";
}

//---------------------------------------------------------------------------
void __fastcall TForm1::UserStringTreeGetText(TBaseVirtualTree *Sender, PVirtualNode Node,
                                              TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText) {
    if (!Node) return;
    UserNode *nodeData = (UserNode *) UserStringTree->GetNodeData(Node);
    switch (Column) {
        case 0:
            CellText = nodeData->Name;
            break;

        case 1:
            CellText = nodeData->Surname;
            break;

    }
}

void __fastcall TForm1::PopulateButtonClick(TObject *Sender) {

    String query = ("INSERT INTO PERSON VALUES (1, 'STEVE', 'GATES', 30, 'PALO ALTO', 1000.0),"
                    "(2, 'BILL', 'ALLEN', 20, 'SEATTLE', 300.22),"
                    "(3, 'PAUL', 'JOBS', 24, 'SEATTLE', 9900.0);");
    try {
        // Assign the query to the object SQLQuery1.
        SQLQuery1->SQL->Text = query;
        SQLQuery1->ExecSQL(true);
    }
    catch (Exception &E) {
        Label1->Caption = "Exception raised with message" + E.Message;
        return;
    }

    Label1->Caption = "Users added to the table";
    PopulateButton->Enabled = false;
    ClearButton->Enabled = true;
    ShowButton->Enabled = true;


}

void __fastcall TForm1::ConnectionButtonClick(TObject *Sender) {
    SQLConnection1->Params->Add("Database=./example.db");
    try {
        SQLConnection1->Connected = true;
        Label1->Caption = "Connection established!";
    }
    catch (EDatabaseError &E) {
        Label1->Caption = "Exception raised with message" + E.Message;
        return;
	}

	if (TableIsEmpty(Sender)) {
		PopulateButton->Enabled = true;
        ClearButton->Enabled = false;
    } else {
        PopulateButton->Enabled = false;
        ClearButton->Enabled = true;
        ShowButton->Enabled = true;
    }

}
//---------------------------------------------------------------------------


void __fastcall TForm1::UserStringTreeAddToSelection(TBaseVirtualTree *Sender, PVirtualNode Node) {
    RemoveButton->Enabled = true;
    UserNode *nodeData = (UserNode *) UserStringTree->GetNodeData(Node);
	InfoLabel->Caption = L"User Id is: " + UnicodeString(nodeData->Id);
	InfoLabel2->Caption = L"User Age is: " + UnicodeString(nodeData->Age);

}
//---------------------------------------------------------------------------


void __fastcall TForm1::ClearButtonClick(TObject *Sender) {
    String query = "DELETE FROM PERSON;";
    try {
        // Assign the query to the object SQLQuery1.
        SQLQuery1->SQL->Text = query;
        SQLQuery1->ExecSQL(true);
    }
    catch (Exception &E) {
        Label1->Caption = "Exception raised with message" + E.Message;
        return;
    }
    UserStringTree->Clear();
    ClearButton->Enabled = false;
    PopulateButton->Enabled = true;
    ShowButton->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RemoveButtonClick(TObject *Sender) {
    PVirtualNode focusedNode = UserStringTree->FocusedNode;
    UserNode *nodeData = (UserNode *) UserStringTree->GetNodeData(focusedNode);
    String query = "DELETE FROM PERSON WHERE ID = " + (String) nodeData->Id;
    try {
        // Assign the query to the object SQLQuery1.
        SQLQuery1->SQL->Text = query;
        SQLQuery1->ExecSQL(true);
    }
    catch (Exception &E) {
        Label1->Caption = "Exception raised with message" + E.Message;
        return;
    }
    if (TableIsEmpty(Sender)) {
        UserStringTree->Clear();
        ClearButton->Enabled = false;
        PopulateButton->Enabled = true;
        ShowButton->Enabled = false;
        RemoveButton->Enabled = false;
        return;
    }
    UserStringTree->Clear();
    ShowButtonClick(Sender);
}

//---------------------------------------------------------------------------
bool __fastcall TForm1::TableIsEmpty(TObject *Sender) {
    String query = "SELECT * FROM PERSON;";
    try {
        // Assign the query to the object SQLQuery1.
        SQLQuery1->SQL->Text = query;
        SQLQuery1->Active = true;
    }
    catch (Exception &E) {
        Label1->Caption = "Exception raised with message" + E.Message;
        return 0;
    }

    return SQLQuery1->IsEmpty();
}

void __fastcall TForm1::UserStringTreeRemoveFromSelection(TBaseVirtualTree *Sender,
                                                          PVirtualNode Node) {
    RemoveButton->Enabled = false;
    InfoLabel->Caption = "";
}
//---------------------------------------------------------------------------


