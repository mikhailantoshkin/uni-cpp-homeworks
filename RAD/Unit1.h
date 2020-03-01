//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "VirtualTrees.hpp"
#include <Data.DB.hpp>
#include <Data.DbxSqlite.hpp>
#include <Data.FMTBcd.hpp>
#include <Data.SqlExpr.hpp>
#include <string>
using namespace std;
//---------------------------------------------------------------------------
typedef struct
{
	int Id;
    UnicodeString Name;
    UnicodeString Surname;
	int Age;
}   UserNode;

//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TVirtualStringTree *UserStringTree;
	TButton *ShowButton;
	TButton *PopulateButton;
	TLabel *Label1;
	TSQLConnection *SQLConnection1;
	TSQLQuery *SQLQuery1;
	TButton *ConnectionButton;
	TLabel *InfoLabel;
	TButton *ClearButton;
	TButton *RemoveButton;
	TLabel *InfoLabel2;
	void __fastcall ShowButtonClick(TObject *Sender);
	void __fastcall UserStringTreeGetText(TBaseVirtualTree *Sender, PVirtualNode Node,
          TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText);
	void __fastcall PopulateButtonClick(TObject *Sender);
	void __fastcall ConnectionButtonClick(TObject *Sender);
	void __fastcall UserStringTreeAddToSelection(TBaseVirtualTree *Sender, PVirtualNode Node);
	void __fastcall ClearButtonClick(TObject *Sender);
	void __fastcall RemoveButtonClick(TObject *Sender);
	void __fastcall UserStringTreeRemoveFromSelection(TBaseVirtualTree *Sender, PVirtualNode Node);
private:
	bool __fastcall TableIsEmpty(TObject *Sender);
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
